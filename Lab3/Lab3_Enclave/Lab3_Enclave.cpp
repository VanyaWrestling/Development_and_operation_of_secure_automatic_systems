#include "Lab3_Enclave_t.h"
#include "sgx_trts.h"
#include <string.h>


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