#ifndef LAB3_ENCLAVE_U_H__
#define LAB3_ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


sgx_status_t foo(sgx_enclave_id_t eid, char* buf, size_t len, size_t idx);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
