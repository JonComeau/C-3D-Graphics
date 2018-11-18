#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "threedee/bitmap.h"
#include "threedee/draw.h"
#include "threedee/types.h"

/*
 * v  0.0  0.0  0.0
 * v  0.0  0.0  1.0
 * v  0.0  1.0  0.0
 * v  0.0  1.0  1.0
 * v  1.0  0.0  0.0
 * v  1.0  0.0  1.0
 * v  1.0  1.0  0.0
 * v  1.0  1.0  1.0
 *
 * g cube
 *
 * f  1  7  5
 * f  1  3  7
 * f  1  4  3
 * f  1  2  4
 * f  3  8  7
 * f  3  4  8
 * f  5  7  8
 * f  5  8  6
 * f  1  5  6
 * f  1  6  2
 * f  2  6  8
 * f  2  8  4
 */

const char g_szClassName[] = "myWindowClass";
const int width = 1280, height = 720;

color white = {255, 255, 255, 255};
color red = {255, 0, 0, 255};

vec3f LIGHT_DIR = {1, 1, 1};
vec3f EYE =       {1, 1, 3};
vec3f CENTER =    {0, 0, 0};
vec3f UP =        {0, 1, 0};

void set_object(object_ptr obj) {
    int index;

    printf("Allocate space for verts\n");
    obj->vert_count = 8;
    obj->verts = malloc(obj->vert_count * sizeof(vec3f));
    if (!obj->verts) {
        fprintf(stderr, "Verts could not be allocated\n");
        return;
    }

    printf("\nStart setting vertices\n");
    obj->verts[0].x = 0.0f; obj->verts[0].y = 0.0f; obj->verts[0].z = 0.0f;
    obj->verts[1].x = 0.0f; obj->verts[1].y = 0.0f; obj->verts[1].z = 1.0f;
    obj->verts[2].x = 0.0f; obj->verts[2].y = 1.0f; obj->verts[2].z = 0.0f;
    obj->verts[3].x = 0.0f; obj->verts[3].y = 1.0f; obj->verts[3].z = 1.0f;
    obj->verts[4].x = 1.0f; obj->verts[4].y = 0.0f; obj->verts[4].z = 0.0f;
    obj->verts[5].x = 1.0f; obj->verts[5].y = 0.0f; obj->verts[5].z = 1.0f;
    obj->verts[6].x = 1.0f; obj->verts[6].y = 1.0f; obj->verts[6].z = 0.0f;
    obj->verts[7].x = 1.0f; obj->verts[7].y = 1.0f; obj->verts[7].z = 1.0f;

    for (index = 0; index < obj->vert_count; index++) {
        printf("\tv %4.2f %4.2f %4.2f\n",
               obj->verts[index].x,
               obj->verts[index].y,
               obj->verts[index].z);

        obj->verts[index].x *= .2;
        obj->verts[index].y *= .2;
        obj->verts[index].z *= .2;
    }

    printf("\nAllocate space for faces\n");
    obj->face_count = 12;
    obj->faces = malloc(obj->face_count * sizeof(face));
    if (!obj->faces) {
        fprintf(stderr, "Faces could not be allocated\n");
        return;
    }

    printf("Start setting faces\n");
    obj->faces[0].ind1 =  1; obj->faces[0].ind2 =  7; obj->faces[0].ind3 =  5;
    obj->faces[1].ind1 =  1; obj->faces[1].ind2 =  3; obj->faces[1].ind3 =  7;
    obj->faces[2].ind1 =  1; obj->faces[2].ind2 =  4; obj->faces[2].ind3 =  3;
    obj->faces[3].ind1 =  1; obj->faces[3].ind2 =  2; obj->faces[3].ind3 =  4;
    obj->faces[4].ind1 =  3; obj->faces[4].ind2 =  8; obj->faces[4].ind3 =  7;
    obj->faces[5].ind1 =  3; obj->faces[5].ind2 =  4; obj->faces[5].ind3 =  8;
    obj->faces[6].ind1 =  5; obj->faces[6].ind2 =  7; obj->faces[6].ind3 =  8;
    obj->faces[7].ind1 =  5; obj->faces[7].ind2 =  8; obj->faces[7].ind3 =  6;
    obj->faces[8].ind1 =  1; obj->faces[8].ind2 =  5; obj->faces[8].ind3 =  6;
    obj->faces[9].ind1 =  1; obj->faces[9].ind2 =  6; obj->faces[9].ind3 =  2;
    obj->faces[10].ind1 = 2; obj->faces[10].ind2 = 6; obj->faces[10].ind3 = 8;
    obj->faces[11].ind1 = 2; obj->faces[11].ind2 = 8; obj->faces[11].ind3 = 4;

    for (index = 0; index < obj->face_count; index++) {
        printf("\tf %i %i %i\n",
               obj->faces[index].ind1,
               obj->faces[index].ind2,
               obj->faces[index].ind3);
    }

    printf("\nTest vertex from face\n");
    for (index = 0; index < obj->face_count; index++) {
        printf("index: %i\n", index);
        printf("\t%i:\tv %.2f %.2f %.2f\n",
               obj->faces[index].ind1,
               obj->verts[obj->faces[index].ind1-1].x,
               obj->verts[obj->faces[index].ind1-1].y,
               obj->verts[obj->faces[index].ind1-1].z);
        printf("\t%i:\tv %.2f %.2f %.2f\n",
               obj->faces[index].ind2,
               obj->verts[obj->faces[index].ind2-1].x,
               obj->verts[obj->faces[index].ind2-1].y,
               obj->verts[obj->faces[index].ind2-1].z);
        printf("\t%i:\tv %.2f %.2f %.2f\n",
               obj->faces[index].ind3,
               obj->verts[obj->faces[index].ind3-1].x,
               obj->verts[obj->faces[index].ind3-1].y,
               obj->verts[obj->faces[index].ind3-1].z);
    }
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, // Handle to the program's exe module
                   HINSTANCE hPrevInstance, // Always NULL for Win32
                   LPSTR lpCmdLine, // Command line arguments as single string (Not program name)
                   int nCmdShow) { // Integer passed to ShowWindow()
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    // Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX); // The size of the structure
    wc.style = CS_HREDRAW | CS_VREDRAW; // Class Styles (CS_*)
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
            CW_USEDEFAULT, CW_USEDEFAULT, width, height, // (startX, startY, width, height)
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
    static HBITMAP hBitmap;
    static HDC hdcMem;
    static int cxBitmap, cyBitmap, cxClient, cyClient;
    HDC hdc;
    PAINTSTRUCT ps;

    int index, jndex, x0, x1, y0, y1;
    face_ptr face;
    vec3f_ptr v0, v1;
    object obj;
    static bitmap bitmap;

    switch (msg) {
        case WM_CREATE: {
            printf("Set up cube\n");
            set_object(&obj);

            create_bitmap(&bitmap, width, height, 4);

            for (index = 0; index < obj.face_count; index++) {
                face = &obj.faces[index];
                for (jndex = 0; jndex < 3; jndex++) {
                    v0 = &obj.verts[face->array[jndex]];
                    v1 = &obj.verts[face->array[(jndex + 1) % 3]];
                    x0 = (int) ((v0->x + 1.f) * width / 2.f);
                    y0 = (int) ((v0->y + 1.f) * height / 2.f);
                    x1 = (int) ((v1->x + 1.f) * width / 2.f);
                    y1 = (int) ((v1->y + 1.f) * height / 2.f);
                    line(&bitmap, x0, y0, x1, y1, &white);
                }
            }

            break;
        }
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        case WM_PAINT:
            hdc = GetDC(hwnd);
            hdcMem = CreateCompatibleDC(hdc);
            hdc = BeginPaint(hwnd, &ps);

            // (Bitmap type, Width in pixels, Scan lines/Height in Pixels, Byte width, Color Plane Count, Bits per pixel)
            BITMAP bm = {0, bitmap.width, bitmap.height, bitmap.width * 4, 1, (WORD) (bitmap.bytes_pp * 8)};

            bm.bmBits = bitmap.data;
            hBitmap = CreateBitmapIndirect(&bm);
            cxBitmap = bm.bmWidth;
            cyBitmap = bm.bmHeight;
            SelectObject(hdcMem, hBitmap);

            StretchBlt(hdc, 0, 0, cxClient, cyClient,
                       hdcMem, 0, 0, cxBitmap, cyBitmap, SRCCOPY);

            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY: // Used when DestroyWindow() is used
            DeleteDC(hdcMem);
            ReleaseDC(hwnd, hdc);
            DeleteObject(hBitmap);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
#endif