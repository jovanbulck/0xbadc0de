// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <openenclave/host.h>
#include <stdio.h>
#include "remoteattestation_u.h"

#include <openenclave/edger8r/host.h>

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

OE_EXTERNC_BEGIN
oe_result_t my_get_remote_report_with_pubkey(
    oe_enclave_t* enclave,
    int* _retval,
    uint8_t** pem_key,
    size_t* key_size,
    uint8_t** remote_report,
    size_t* remote_report_size)
{
    oe_result_t _result = OE_FAILURE;

    /* Marshalling struct. */
    get_remote_report_with_pubkey_args_t _args, *_pargs_in = NULL, *_pargs_out = NULL;

    /* Marshalling buffer and sizes. */
    size_t _input_buffer_size = 0;
    size_t _output_buffer_size = 0;
    size_t _total_buffer_size = 0;
    uint8_t* _buffer = NULL;
    uint8_t* _input_buffer = NULL;
    uint8_t* _output_buffer = NULL;
    size_t _input_buffer_offset = 0;
    size_t _output_buffer_offset = 0;
    size_t _output_bytes_written = 0;

    /* Fill marshalling struct. */
    memset(&_args, 0, sizeof(_args));
    _args.pem_key = (uint8_t**)pem_key;
    _args.key_size = (size_t*)key_size;
    _args.remote_report = (uint8_t**)remote_report;
    _args.remote_report_size = (size_t*)remote_report_size;

    /* Compute input buffer size. Include in and in-out parameters. */
    OE_ADD_SIZE(_input_buffer_size, sizeof(get_remote_report_with_pubkey_args_t));
    /* There were no corresponding parameters. */
    
    /* Compute output buffer size. Include out and in-out parameters. */
    OE_ADD_SIZE(_output_buffer_size, sizeof(get_remote_report_with_pubkey_args_t));
    if (pem_key)
        OE_ADD_SIZE(_output_buffer_size, sizeof(uint8_t*));
    if (key_size)
        OE_ADD_SIZE(_output_buffer_size, sizeof(size_t));
    if (remote_report)
        OE_ADD_SIZE(_output_buffer_size, sizeof(uint8_t*));
    if (remote_report_size)
        OE_ADD_SIZE(_output_buffer_size, sizeof(size_t));
    
    /* Allocate marshalling buffer. */
    _total_buffer_size = _input_buffer_size;
    OE_ADD_SIZE(_total_buffer_size, _output_buffer_size);
    _buffer = (uint8_t*)malloc(_total_buffer_size);
    _input_buffer = _buffer;
    _output_buffer = _buffer + _input_buffer_size;
    if (_buffer == NULL)
    {
        _result = OE_OUT_OF_MEMORY;
        goto done;
    }
    
    /* Serialize buffer inputs (in and in-out parameters). */
    _pargs_in = (get_remote_report_with_pubkey_args_t*)_input_buffer;
    OE_ADD_SIZE(_input_buffer_offset, sizeof(*_pargs_in));
    /* There were no in nor in-out parameters. */
    
    /* Copy args structure (now filled) to input buffer. */
    memcpy(_pargs_in, &_args, sizeof(*_pargs_in));

    /* Call enclave function. */
    if ((_result = oe_call_enclave_function(
             enclave,
             remoteattestation_fcn_id_get_remote_report_with_pubkey,
             _input_buffer,
             _input_buffer_size,
             _output_buffer,
             _output_buffer_size,
             &_output_bytes_written)) != OE_OK)
        goto done;

    /* Setup output arg struct pointer. */
    _pargs_out = (get_remote_report_with_pubkey_args_t*)_output_buffer;
    OE_ADD_SIZE(_output_buffer_offset, sizeof(*_pargs_out));
    

    
    /* Currently exactly _output_buffer_size bytes must be written. */
    if (_output_bytes_written != _output_buffer_size)
    {
        _result = OE_FAILURE;
        goto done;
    }
    
    /* Unmarshal return value and out, in-out parameters. */
    *_retval = _pargs_out->_retval;
    OE_READ_OUT_PARAM(pem_key, (size_t)(sizeof(uint8_t*)));
    OE_READ_OUT_PARAM(key_size, (size_t)(sizeof(size_t)));
    OE_READ_OUT_PARAM(remote_report, (size_t)(sizeof(uint8_t*)));
    OE_READ_OUT_PARAM(remote_report_size, (size_t)(sizeof(size_t)));

    _result = OE_OK;

    /* Check if the call succeeded. */
    if ((_result = _pargs_out->_result) != OE_OK)
        goto done;

done:
    if (_buffer)
        free(_buffer);
    return _result;
}
OE_EXTERNC_END

oe_enclave_t* create_enclave(const char* enclave_path)
{
    oe_enclave_t* enclave = NULL;

    printf("Host: Enclave library %s\n", enclave_path);
    oe_result_t result = oe_create_remoteattestation_enclave(
        enclave_path,
        OE_ENCLAVE_TYPE_SGX,
        OE_ENCLAVE_FLAG_DEBUG,
        NULL,
        0,
        &enclave);

    if (result != OE_OK)
    {
        printf(
            "Host: oe_create_remoteattestation_enclave failed. %s",
            oe_result_str(result));
    }
    else
    {
        printf("Host: Enclave successfully created.\n");
    }
    return enclave;
}

void terminate_enclave(oe_enclave_t* enclave)
{
    oe_terminate_enclave(enclave);
    printf("Host: Enclave successfully terminated.\n");
}

int main(int argc, const char* argv[])
{
    oe_enclave_t* enclave_a = NULL;
    oe_enclave_t* enclave_b = NULL;
    uint8_t* encrypted_msg = NULL;
    size_t encrypted_msg_size = 0;
    oe_result_t result = OE_OK;
    int ret = 1;
    uint8_t* pem_key = NULL;
    size_t pem_key_size = 0;
    uint8_t* remote_report = NULL;
    size_t remote_report_size = 0;

    /* Check argument count */
    if (argc != 3)
    {
        printf("Usage: %s ENCLAVE_PATH\n", argv[0]);
        return 1;
    }

    printf("Host: Creating two enclaves\n");
    enclave_a = create_enclave(argv[1]);
    if (enclave_a == NULL)
    {
        goto exit;
    }

    printf("Host: requesting a remote report and the encryption key from 1st "
           "enclave\n");
    result = my_get_remote_report_with_pubkey(
        enclave_a,
        &ret,
        &pem_key,
        &pem_key_size,
        &remote_report,
        &remote_report_size);
    
    printf("Remote report at %p, size %d\n", &remote_report, remote_report_size);

    if ((result != OE_OK) || (ret != 0))
    {
        printf(
            "Host: verify_report_and_set_pubkey failed. %s",
            oe_result_str(result));
        if (ret == 0)
            ret = 1;
        goto exit;
    }
    printf("Host: 1st enclave's public key: \n%s", pem_key);

exit:
    if (pem_key)
        free(pem_key);

    if (remote_report)
        free(remote_report);

    if (encrypted_msg != NULL)
        free(encrypted_msg);

    printf("Host: Terminating enclaves\n");
    if (enclave_a)
        terminate_enclave(enclave_a);

    if (enclave_b)
        terminate_enclave(enclave_b);

    printf("Host:  %s \n", (ret == 0) ? "succeeded" : "failed");
    return ret;
}
