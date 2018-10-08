#ifdef WIN32
#include <windows.h>

const char g_szClassName[] = "myWindowClass";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, // Handle to the program's exe module
		HINSTANCE hPrevInstance, // Always NULL for Win32
		LPSTR lpCmdLine, // Command line arguments as single string (Not program name)
		int nCmdShow) { // Integer passed to ShowWindow()
	WNDCLASSEX wc;
	HWND hwnd;
	MSG msg;

	// Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX); // The size of the structure
	wc.style = 0; // Class Styles (CS_*)
	wc.lpfnWndProc = WndProc; // Pointer to the window procedure
	wc.cbClsExtra = 0; // Amount of extra data allocated for this class
	wc.cbWndExtra = 0; // Amount of extra data in memory
	wc.hInstance = hInstance; // Handle to application instance
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor that will be displayed
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Background Brush to set the color of the window
	wc.lpszMenuName = NULL; // Name of a menu resource to use for the windows with this class
	wc.lpszClassName = g_szClassName; // Name to identify the class with
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Icon (usually 32x32) when Alt+Tab pressed
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Small (usually 16x16) icon to show in the taskbar and
												  // top left corner of the window

	if (!RegisterClassEx(&wc)) { // This checks for failure
		MessageBox(NULL, // A handle to the owner window
				   "Windows Registration Failed!", // Message to be displayed
				   "Error!", // The title
				   MB_ICONEXCLAMATION | MB_OK); // Window flags
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE, // Extended windows style
			g_szClassName, // What class of window to create
			"The title of my window", // Window title
			WS_OVERLAPPEDWINDOW, // Window style parameter
			CW_USEDEFAULT, CW_USEDEFAULT, 240 * 3, 120 * 3, // (startX, startY, width, height)
			NULL, // Parent window handle
			NULL, // Menu handle
			hInstance, // Application instance handle
			NULL);// Pointer to Window creation data

	if (hwnd == NULL) { // Checking return value
		MessageBox(NULL, // A handle to the owner window
				   "Windows Registration Failed!", // Message to be displayed
				   "Error!", // The title
				   MB_ICONEXCLAMATION | MB_OK); // Window flags
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// The window procedure is called for each message
// This is where all messages are handled
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		case WM_CLOSE: // Used when Close button or "Alt+F4"-like action received
			DestroyWindow(hwnd);
		    break;
		case WM_DESTROY: // Used when DestroyWindow() is used
			PostQuitMessage(0);
		    break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
#endif