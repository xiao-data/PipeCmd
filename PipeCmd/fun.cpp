#include "fun.h"

int z_strncmp(const char* str1, const char* str2, DWORD n) {
	for (DWORD i = 0; i < n; i++) {
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}

int z_strcmp(const char* str1, const char* str2) {
	for (DWORD i = 0; i < z_strlen(str2) + 1; i++) {
		if (str1[i] > str2[i])
			return 1;
		else if (str1[i] < str2[i])
			return -1;
	}
	return 0;
}

void z_memset(void* _Dst, int Val, DWORD n) {
	LPBYTE Dst = (LPBYTE)_Dst;
	for (DWORD i = 0; i < n; i++)
		Dst[i] = Val;
}

void z_memcpy(void* _Dst, void const* _Src, DWORD n) {
	LPBYTE Dst = (LPBYTE)_Dst;
	LPCBYTE Src = (LPCBYTE)_Src;
	for (DWORD i = 0; i < n; i++)
		Dst[i] = Src[i];
}

DWORD z_strlen(const char* str) {
	DWORD len = 0;
	for (;; len++)
		if (str[len] == '\0')
			break;
	return len;
}

void z_strcpy(char* Dst, char const* Src) {
	DWORD len = z_strlen(Src);
	for (DWORD i = 0; i < len + 1; i++)
		Dst[i] = Src[i];
}
