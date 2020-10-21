#include <windows.h>
#include <stdio.h>
#include "fun.h"
#define DEFAULT_BUFLEN 1024
CHAR otBuf[DEFAULT_BUFLEN] = { 0 };
CHAR inBuf[DEFAULT_BUFLEN] = { 0 };
CHAR filepath[MAX_PATH] = { 0 };
CHAR cmdLine[MAX_PATH] = { 0 };
INT iResult = 0;
DWORD inBufLen = 0;
DWORD otBufLen = 0;
DWORD timeout = TRUE, count = 0, tmpbuflen = 0, BufLen = 0;
CHAR Buf[DEFAULT_BUFLEN << 4] = { 0 };
HANDLE hReadPipe1, hWritePipe1, hReadPipe2, hWritePipe2;
INT main() {
    // Security attributes
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;
    // Create pipes
    iResult = CreatePipe(&hReadPipe1, &hWritePipe1, &sa, 0);
    if (iResult == 0)
        return 0;
    iResult = CreatePipe(&hReadPipe2, &hWritePipe2, &sa, 0);
    if (iResult == 0) {
        CloseHandle(hReadPipe1);
        CloseHandle(hWritePipe1);
        return 0;
    }
    // Startup info
    STARTUPINFOA si;
    z_ZeroMemory(&si, sizeof(si));
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = hReadPipe2;
    si.hStdOutput = hWritePipe1;
    si.hStdError = hWritePipe1;
    // Create process
    iResult = GetSystemDirectoryA(cmdLine, sizeof(cmdLine));
    if (iResult == 0)
        goto END2;
    z_strcpy(cmdLine + z_strlen(cmdLine), "\\cmd.exe");
    PROCESS_INFORMATION pi;
    iResult = CreateProcessA(cmdLine, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
    if (iResult == 0)
        goto END2;
    while (TRUE) { // Init info
        Sleep(50);
        z_ZeroMemory(otBuf, DEFAULT_BUFLEN);
        iResult = PeekNamedPipe(hReadPipe1, otBuf, DEFAULT_BUFLEN, &otBufLen, 0, 0);
        if (iResult == 0)
            goto END;
        if (otBufLen) {
            iResult = ReadFile(hReadPipe1, otBuf, DEFAULT_BUFLEN, &otBufLen, 0);
            if (iResult == 0)
                goto END;
            printf(otBuf);
        }
        else
            break;
    }

    while (TRUE) {
        z_ZeroMemory(inBuf, DEFAULT_BUFLEN);
        gets_s(inBuf);
        if (z_strncmp(inBuf, "exit", 4) == 0)
            goto END;
        inBufLen = z_strlen(inBuf);
        inBuf[inBufLen++] = '\n';
        iResult = WriteFile(hWritePipe2, inBuf, inBufLen, &inBufLen, 0);
        if (iResult == 0)
            goto END;
        timeout = TRUE, count = 0, BufLen = 0;
        z_ZeroMemory(Buf, DEFAULT_BUFLEN << 4);
        while (TRUE) {
            z_ZeroMemory(otBuf, DEFAULT_BUFLEN);
            otBufLen = 0;
            iResult = PeekNamedPipe(hReadPipe1, otBuf, DEFAULT_BUFLEN, &otBufLen, 0, 0);
            if (iResult == 0)
                goto END;
            if (otBufLen) {
                iResult = ReadFile(hReadPipe1, otBuf, DEFAULT_BUFLEN, &otBufLen, 0);
                if (iResult == 0)
                    goto END;
                if (strncmp(otBuf, inBuf, inBufLen) == 0) {
                    otBufLen -= inBufLen;
                    z_memcpy(otBuf, otBuf + inBufLen, otBufLen);
                    if (otBufLen == 0)
                        continue;
                }
                z_memcpy(Buf + BufLen, otBuf, otBufLen);
                BufLen += otBufLen;
                Sleep(100);
                timeout = FALSE;
            }
            else {
                if (timeout && count++ <= 300) { // Wait for 15 Second.
                    Sleep(50);
                    continue;
                }
                printf(Buf);
                break;
            }
        }
    }
END:
    TerminateProcess(pi.hProcess, 0);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
END2:
    CloseHandle(hReadPipe1);
    CloseHandle(hWritePipe1);
    CloseHandle(hReadPipe2);
    CloseHandle(hWritePipe2);
    return 0;
}