#include <stdio.h>
#include <tchar.h>
#include <string.h>

#include "sgx_urts.h"
#include "sgx_tseal.h"
#include "Lab3_Enclave_u.h"
#define ENCLAVE_FILE _T ("Lab3_Enclave.signed.dll")
#define BUF_LEN 100 // Длина буфера обмена между анклавом и небезопасным приложением
/*
const char table[10][33] = {
	// Значения были сгенерированы случайным образом благодаря: https://www.browserling.com/tools/random-hex
	"2a0ee75516a60f9ffb7b2e96369183c7",
	"a24b21391687f3c5d7144dcaae5cdc3e",
	"190e71d2f4b5f946ec7674c7f4dfe64d",
	"0f29f838760a69112a67c50ef33a90cd",
	"10e9183b124d63c444710fd64f8efcfc",
	"8940806fea42a6523620e75ce2a8599e",
	"72bce6b67c70b75a4d06a539fee1744f",
	"71f14ed1224a6064dcff1d274f6f8fa8",
	"6a1404be970ebca7270d63f65b69719e",
	"53f5ab7e5a8b306c4a4fd39333a284b7"
};

void foo(char* buf, size_t len, size_t idx) {
	if (idx < 10) {
		const char* data_ptr = data_ptr = table[idx];
		memcpy(buf, data_ptr, strlen(data_ptr + 1));
	}
	else {
		memset(buf, 0, strlen(table[0]));
	}
	return;
}
*/
int main() {

	char buffer[BUF_LEN] = { 0 };

	sgx_enclave_id_t eid;
	sgx_status_t ret = SGX_SUCCESS;
	sgx_launch_token_t token = { 0 };
	int updated = 0;

	ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL);
	if (ret != SGX_SUCCESS) {
		printf("Application error %#x, failed to create enclave.\n", ret);
		return -1;
	}


	while (true) {
		printf("Enter a number of object to get information or enter -1 to exit a program: \t");
		int idx = -1;
		scanf_s("%d", &idx);
		if (idx < 0) {
			return 0;
		}
		foo(eid, buffer, BUF_LEN, idx);
		printf("%s \n******************************************\n\n", buffer);
	}
	if (SGX_SUCCESS != sgx_destroy_enclave(eid))
		return -1;
	return 0;
}