#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include "vars.h"

char* getMessage(){
    char str[BUFFER_SIZE];
    printf("Enter message: ");
    gets(str);

    char* p = &str[0];
    return p;
}

int main(void)
{
    HANDLE hPipe;
    DWORD dwWritten;

    hPipe = CreateFile(
        TEXT(myPipe), 
        GENERIC_READ | GENERIC_WRITE, 
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    // send a single message
    if (hPipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(
            hPipe,
            getMessage(),
            BUFFER_SIZE,
            &dwWritten,
            NULL
        );
        CloseHandle(hPipe);
    }
    return (0);
}
