#ifndef FUN_H
#define FUN_H

#define z_ZeroMemory(Destination,Length) z_memset((Destination),0,(Length))

int z_strncmp(const char* str1, const char* str2, unsigned int n);
int z_strcmp(const char* str1, const char* str2);
void z_memset(void* Dst, int Val, unsigned int n);
unsigned int z_strlen(const char* str);
void z_strcpy(char* Des, char const* Src);
void z_memcpy(void* Dst, void const* Src, unsigned int n);
#endif