#ifndef FUN_H
#define FUN_H

#include <Windows.h>
#define z_ZeroMemory(Destination,Length) z_memset((Destination),0,(Length))

int z_strncmp(const char* str1, const char* str2, DWORD n);
void z_memset(void* Dst, int Val, DWORD n);
DWORD z_strlen(const char* str);
void z_strcpy(char* Des, char const* Src);
void z_memcpy(void* Dst, void const* Src, DWORD n);
#endif