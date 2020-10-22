#include "fun.h"

int z_strncmp(const char* str1, const char* str2, unsigned int n) {
	for (unsigned int i = 0; i < n; i++) {
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}

int z_strcmp(const char* str1, const char* str2) {
	for (unsigned int i = 0; i < z_strlen(str2) + 1; i++) {
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}

void z_memset(void* _Dst, int Val, unsigned int n) {
	unsigned char* Dst = (unsigned char*)_Dst;
	for (unsigned int i = 0; i < n; i++)
		Dst[i] = Val;
}

void z_memcpy(void* _Dst, void const* _Src, unsigned int n) {
	unsigned char* Dst = (unsigned char*)_Dst;
	const unsigned char* Src = (const unsigned char*)_Src;
	for (unsigned int i = 0; i < n; i++)
		Dst[i] = Src[i];
}

unsigned int z_strlen(const char* str) {
	unsigned int len = 0;
	for (;; len++)
		if (str[len] == '\0')
			break;
	return len;
}

void z_strcpy(char* Dst, char const* Src) {
	unsigned int len = z_strlen(Src);
	for (unsigned int i = 0; i < len + 1; i++)
		Dst[i] = Src[i];
}
