/*
 *  This file is part of the SGX-Step enclave execution control framework.
 *
 *  Copyright (C) 2017 Jo Van Bulck <jo.vanbulck@cs.kuleuven.be>,
 *                     Raoul Strackx <raoul.strackx@cs.kuleuven.be>
 *
 *  SGX-Step is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SGX-Step is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with SGX-Step. If not, see <http://www.gnu.org/licenses/>.
 */

#include <wmmintrin.h>  // for intrinsics for AES-NI
#include "sgx_trts.h"
#include "sgx_tcrypto.h"
#include "stdlib.h"
#include <string.h>
#include <stdint.h>     // for uint8_t
#include <stdio.h>
#include "encl_t.h"	// for ocall

// The in-enclave secret key
static uint8_t key[16] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };

// Dummy page that serves as a breakpoint - the PF handler will be invoked on 
// accessing this page in the DO_ENC_BLOCK() macro, allowing us to easily break
// at the right point to leak the SSA frame
volatile __attribute__((aligned(4096))) int array[4096] = { 0xaa };

// Return address of dummy page for revoking the page permissions to "install" the breakpoint
uint64_t getArrayAddress()
{
	return (uint64_t)array;
}
void *getEncryptStringAdrs()
{
	return encryptString;
}
// All AES-NI functions are largely based on https://gist.github.com/acapola/d5b940da024080dfaf5f
// which does not state its license terms

#define AES_128_key_exp(k, rcon) aes_128_key_expansion(k, _mm_aeskeygenassist_si128(k, rcon))
  
// The write access to array[] causes a page fault. The inline asm before and after prevents compile-time reordering,
// otherwise GCC would move the array write before the _mm_aesenc_si128 calls		
#define DO_ENC_BLOCK(m, k) \
	do{\
        m = _mm_xor_si128       (m, k[ 0]); \
        m = _mm_aesenc_si128    (m, k[ 1]); \
        m = _mm_aesenc_si128    (m, k[ 2]); \
        m = _mm_aesenc_si128    (m, k[ 3]); \
        m = _mm_aesenc_si128    (m, k[ 4]); \
        m = _mm_aesenc_si128    (m, k[ 5]); \
        m = _mm_aesenc_si128    (m, k[ 6]); \
        m = _mm_aesenc_si128    (m, k[ 7]); \
        m = _mm_aesenc_si128    (m, k[ 8]); \
        m = _mm_aesenc_si128    (m, k[ 9]); \
        /* NOTE: we use a #PF controlled-channel here to easily synchronize    \
         * encryption rounds, alternatively, we could also use single-stepping \
         * here (cf., as we do for the strlen thread). */ \
		asm volatile("" ::: "memory");      \
	    array[10] = 0;						\
		asm volatile("" ::: "memory");      \
		m = _mm_aesenclast_si128(m, k[10]); \
    }while(0)


static __m128i aes_128_key_expansion(__m128i key, __m128i keygened)
{
	keygened = _mm_shuffle_epi32(keygened, _MM_SHUFFLE(3,3,3,3));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	key = _mm_xor_si128(key, _mm_slli_si128(key, 4));
	return _mm_xor_si128(key, keygened);
}

static void aes128_load_key(uint8_t *enc_key, __m128i *key_schedule)
{
    key_schedule[0] = _mm_loadu_si128((const __m128i*) enc_key);
	key_schedule[1]  = AES_128_key_exp(key_schedule[0], 0x01);
	key_schedule[2]  = AES_128_key_exp(key_schedule[1], 0x02);
	key_schedule[3]  = AES_128_key_exp(key_schedule[2], 0x04);
	key_schedule[4]  = AES_128_key_exp(key_schedule[3], 0x08);
	key_schedule[5]  = AES_128_key_exp(key_schedule[4], 0x10);
	key_schedule[6]  = AES_128_key_exp(key_schedule[5], 0x20);
	key_schedule[7]  = AES_128_key_exp(key_schedule[6], 0x40);
	key_schedule[8]  = AES_128_key_exp(key_schedule[7], 0x80);
	key_schedule[9]  = AES_128_key_exp(key_schedule[8], 0x1B);
	key_schedule[10] = AES_128_key_exp(key_schedule[9], 0x36);

	// generate decryption keys in reverse order.
    // k[10] is shared by last encryption and first decryption rounds
    // k[0] is shared by first encryption round and last decryption round (and is the original user key)
    // For some implementation reasons, decryption key schedule is NOT the encryption key schedule in reverse order
	key_schedule[11] = _mm_aesimc_si128(key_schedule[9]);
	key_schedule[12] = _mm_aesimc_si128(key_schedule[8]);
	key_schedule[13] = _mm_aesimc_si128(key_schedule[7]);
	key_schedule[14] = _mm_aesimc_si128(key_schedule[6]);
	key_schedule[15] = _mm_aesimc_si128(key_schedule[5]);
	key_schedule[16] = _mm_aesimc_si128(key_schedule[4]);
	key_schedule[17] = _mm_aesimc_si128(key_schedule[3]);
	key_schedule[18] = _mm_aesimc_si128(key_schedule[2]);
	key_schedule[19] = _mm_aesimc_si128(key_schedule[1]);
}

static void aes128_enc(uint8_t *plainText, uint8_t *cipherText)
{
	uint8_t pt[16] = {0};
	uint8_t ct[16] = {0};
	static __m128i key_schedule[20]; // the expanded key (local for thread safety)
	
	aes128_load_key(key, key_schedule);
	
	memcpy(pt, plainText, 16);
	__m128i m = _mm_loadu_si128((__m128i *) pt);
	DO_ENC_BLOCK(m, key_schedule);
	
	_mm_storeu_si128((__m128i *) ct, m);
	
	memcpy(cipherText, ct, 16);
}

// To keep the example simple, this ecall will only encrypt the first 16 byte of the string
void encryptString(const char *str, uint8_t *ct)
{
	uint8_t pt[16] = { 0 };
	
	// Copy at most the first 16 chars into the pt buffer
	// Note: our PoC is not reliant on the timing leakage through strlen() here,
	//       the strlen() call we target is the one in the edger8r-generated code
	const size_t len = strlen(str);
	const size_t copy_len = len > 16 ? 16 : len;
	
	memcpy(pt, str, copy_len);
	
	aes128_enc(pt, ct);
}

#if 0
uint64_t strlenOracle(uint64_t p)
{
	return strlen((char*)p);
}
#endif

