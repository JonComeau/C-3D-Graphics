//
// Created by vylly on 12/6/2018.
//

#include <windows.h>
#include <stdio.h>
#include <time.h>

#define BUF_SIZE 255

char construct_console(int width, int height, int fontw, int fonth);
DWORD WINAPI graphics_thread();
static BOOL CloseHandler(DWORD evt);

int main(int argc, char** argv) {
    DWORD dwThreadId;
    HANDLE hThread;

    if (construct_console(256, 240, 4, 4)) {
        hThread = CreateThread(
                NULL,
                0,
                graphics_thread,
                NULL,
                0,
                &dwThreadId);

        WaitForSingleObject(hThread, INFINITE);
    }
    return 0;
}

DWORD WINAPI graphics_thread() {
    fprintf(stderr, "Threading works");
}

char construct_console(int width, int height, int fontw, int fonth) {
    int screen_width = width, screen_height = height;
    SMALL_RECT m_rectWindow = {0, 0, 1, 1};
    HANDLE m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    COORD coord = {(short)screen_width, (short)screen_height};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    CHAR_INFO *m_bufScreen;

    char buf[256];

    fprintf(stderr, "Setup Console\n");
    if (m_hConsole == NULL) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    m_rectWindow = (SMALL_RECT){0, 0, (short)screen_width, (short)screen_height};
    fprintf(stderr, "Change Visual Size\n");
    // Change console visual size to a minimum so ScreenBuffer can shrink
    // below the actual visual size
    if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow)) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    fprintf(stderr, "Set console buffer size\n");
    if (!SetConsoleScreenBufferSize(m_hConsole, coord)) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    fprintf(stderr, "Set Active buffer\n");
    if (!SetConsoleActiveScreenBuffer(m_hConsole)) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    fprintf(stderr, "Get buffer info\n");
    // Get screen buffer info and check the maximum allowed window size.
    // Return error if exceeded, so user know their dimensions are too large.
    if (!GetConsoleScreenBufferInfo(m_hConsole, &csbi)){
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    fprintf(stderr, "     X = %i; Y = %i\n", screen_width, screen_height);
    fprintf(stderr, "csbi.X = %i; Y = %i\n", csbi.dwMaximumWindowSize.X, csbi.dwMaximumWindowSize.Y);

    if (screen_height > csbi.dwMaximumWindowSize.Y) {
        fprintf(stderr, "Screen height too big\n");
        return ERROR;
    }
    if (screen_width > csbi.dwMaximumWindowSize.X) {
        fprintf(stderr, "Screen width too big\n");
        return ERROR;
    }

    fprintf(stderr, "Set Console Window size\n");
    // Set Physical Console Window Size
    m_rectWindow = (SMALL_RECT){0, 0, (short)screen_width - 1, (short)screen_height - 1};
    if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow)) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    fprintf(stderr, "Set Mouse flags\n");
    // Set flags to allow for mouse input
    if (!SetConsoleMode(m_hConsoleIn,
            ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT)) {
        FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      buf, (sizeof(buf) / sizeof(char)), NULL);

        fprintf(stderr, "ERROR: %s\n", buf);
        return ERROR;
    }

    // Allocate memory for screen buffer
    m_bufScreen = calloc(screen_width * screen_height, sizeof(CHAR_INFO));

    return 1;
}