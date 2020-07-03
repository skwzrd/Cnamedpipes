#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

#include "vars.h"

int main(void)
{
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD dwRead;

    hPipe = CreateNamedPipe(
        TEXT(myPipe),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        1,
        BUFFER_SIZE,
        BUFFER_SIZE,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL
    );

    while (hPipe != INVALID_HANDLE_VALUE)
    {
        // wait for connection
        if (ConnectNamedPipe(hPipe, NULL) != FALSE)
        {
            while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
            {
                // add terminating zero
                buffer[dwRead] = '\0';

                printf("%s\n", buffer);
            }
        }
        DisconnectNamedPipe(hPipe);
    }
    return 0;
}
