#ifndef LAB3_ENCLAVE_T_H__
#define LAB3_ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void foo(char* buf, size_t len, size_t idx);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
