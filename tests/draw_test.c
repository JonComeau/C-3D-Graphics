#ifdef WIN32
#include <float.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <threedee/matrix.h>
#include <math.h>
#include <threedee/s_t_r.h>
#include <threedee/tga.h>
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
const int width = 1280 / 2, height = 720;

color white = {255, 255, 255, 255};
color red = {255, 0, 0, 255};

vec3f LIGHT_DIR, EYE, CENTER, UP;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char read_obj(object_ptr obj, const char *filename);
void errhandler(LPTSTR error_str, HWND hwnd);
void render(HWND hwnd, HDC hdc, HDC hdcMem, bitmap* bitmp,
            HBITMAP* hBitmp, object obj, float* zbuffer, int cxClient, int cyClient);

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
    static HBITMAP hBitmp;
    static HDC hdcMem;
    static int cxBitmp, cyBitmp, cxClient, cyClient;
    HDC hdc;
    PAINTSTRUCT ps;

    float* zbuffer;
    int index;

    static object obj;
    static bitmap bitmp;

    static mat4x4 projection;
    static float f_near, f_far, f_fov, f_aspect, f_fov_rad;

    switch (msg) {
        case WM_CREATE: {
            // Initalizing Projection Matrix
            projection.m[0][0] = projection.m[0][1] = projection.m[0][2] = projection.m[0][3] = 0;
            projection.m[1][0] = projection.m[1][1] = projection.m[1][2] = projection.m[1][3] = 0;
            projection.m[2][0] = projection.m[2][1] = projection.m[2][2] = projection.m[2][3] = 0;
            projection.m[3][0] = projection.m[3][1] = projection.m[3][2] = projection.m[3][3] = 0;

            // Initializing FOV values
            f_near = 0.1f;
            f_far = 1000.0f;
            f_fov = 90.0f;
            f_aspect = (float)width / (float)height;
            f_fov_rad = 1.0f / tanf(f_fov * 0.5f / 180.0f * 3.14159f);

            // Projection matrix values
            projection.m[0][0] = f_aspect * f_fov_rad;
            projection.m[1][1] = f_fov_rad;
            projection.m[2][2] = f_far / (f_far - f_near);
            projection.m[3][2] = (-f_far * f_near) / (f_far - f_near);
            projection.m[2][3] = 1.0f;

            read_obj(&obj, "..\\res\\african_head.obj");

            //SetTimer(hwnd, 1, 20, NULL);
            break;
        }
        case WM_TIMER:
            //InvalidateRect(hwnd, NULL, FALSE);
            break;
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        case WM_PAINT:
            hdc = GetDC(hwnd);

            // This initializes the Bitmap
            create_bitmap(&bitmp, width, height, 4);

            zbuffer = (float*) malloc(width * height * sizeof(float));

            for (index = width * height; index--; zbuffer[index] = -FLT_MAX);

            hdcMem = CreateCompatibleDC(hdc);
            hdc = BeginPaint(hwnd, &ps);

            render(hwnd, hdc, hdcMem, &bitmp, &hBitmp, obj, zbuffer, cxClient, cyClient);

            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY: // Used when DestroyWindow() is used

            // Save the bitmap
            write_file(&bitmp, "C:\\threedee\\teapot.tga");

            DeleteDC(hdcMem);
            ReleaseDC(hwnd, hdc);

            DeleteObject(hBitmp);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void render(HWND hwnd, HDC hdc, HDC hdcMem, bitmap* bitmp,
        HBITMAP* hBitmp, object obj, float* zbuffer, int cxClient, int cyClient) {
    int index, jndex, cxBitmp, cyBitmp;
    face_ptr face;
    vec3f_ptr vec;
    vec3f n, world_coords[3], screen_coords[3];
    float intensity;

    LIGHT_DIR = (vec3f){0, 0, 1};

//    rotate_obj(&obj, 1, 0, 0);
//    trans_obj(&obj, 1, 0, 0);
//    scale_obj(&obj, .95f, .95f, .95f);

    for (index = 0; index < obj.face_count; index++) {
        face = &obj.faces[index];
        for (jndex = 0; jndex < 3; jndex++) {
            vec = &obj.verts[face->v[jndex]];
            screen_coords[jndex] = (vec3f) {
                    (int) ((vec->x + 1.f) * width / 2 + .5),
                    (int) ((vec->y + 1.f) * height / 2 + .5),
                    vec->z};
            world_coords[jndex] = *vec;
        }
        n = vec3f_vec3f_cross(
                vec3f_vec3f_sub(world_coords[2], world_coords[0]),
                vec3f_vec3f_sub(world_coords[1], world_coords[0]));
        n = vec3f_normalize(n);
        intensity = fabsf(vec3f_vec3f_mult(n, LIGHT_DIR));
        if (intensity > 0.f) {
            draw_tri(bitmp, zbuffer, screen_coords[0], screen_coords[1], screen_coords[2],
                     &(color) {(unsigned char) (intensity * 255),
                               (unsigned char) (intensity * 255),
                               (unsigned char) (intensity * 255), 255});
        }
        if (intensity <= 0.f) printf("intensity: %f, face: %i\n", intensity, index);
    }

    // (Bitmap type, Width in pixels, Scan lines/Height in Pixels, Byte width, Color Plane Count, Bits per pixel)
    BITMAP bm = {
            0,
            bitmp->width,
            bitmp->height,
            bitmp->width * 4,
            1,
            (WORD) (bitmp->bytes_pp * 8)};

    bm.bmBits = bitmp->data;
    *hBitmp = CreateBitmapIndirect(&bm);
    cxBitmp = bm.bmWidth;
    cyBitmp = bm.bmHeight;
    SelectObject(hdcMem, *hBitmp);

    StretchBlt(hdc, 0, 0, cxClient, cyClient,
               hdcMem, 0, 0, cxBitmp, cyBitmp, SRCCOPY);
}

char read_obj(object_ptr obj, const char *filename) {
    FILE *fp;
    int index;
    int v_count, vn_count, vt_count, f_count;
    int v_index, vn_index, vt_index, f_index;
    char buffer[1000], *temp, *v_search, *vn_search, *vt_search, *f_search;
    fp = fopen(filename, "r");
    if (!fp) {
        printf("There was no file\n");
        return -1;
    }
    float max = 0;

    printf("Read Obj\n");

    v_count = vn_count = vt_count = f_count = 0;
    v_index = vn_index = vt_index = f_index = 0;

    // The first loop
    while (fgets(buffer, sizeof(buffer), fp)) {
        v_search = strstr(buffer, "v");
        if (v_search != NULL) {
            v_count++;
            continue;
        }
        vn_search = strstr(buffer, "vn");
        if (vn_search != NULL) {
            vn_count++;
            continue;
        }
        vt_search = strstr(buffer, "vt");
        if (vt_search != NULL) {
            vt_count++;
            continue;
        }
        f_search = strstr(buffer, "f");
        if (f_search != NULL) {
            f_count++;
            continue;
        }
    }

    printf("vert_count: %i\n", v_count);
    printf("face_count: %i\n", f_count);

    obj->vert_count = v_count;
    obj->verts = calloc(obj->vert_count, sizeof(vec3f));
    if (!obj->verts) {
        fprintf(stderr, "Verts could not be allocated\n");
        return 0;
    }

    obj->face_count = f_count;
    obj->faces = calloc(obj->face_count, sizeof(vec3f));
    if (!obj->faces) {
        fprintf(stderr, "Faces could not be allocated\n");
        return 0;
    }

    fseek(fp, 0, SEEK_SET);

    while (fgets(buffer, sizeof(buffer), fp)) {
        v_search = strstr(buffer, "v ");
        if (v_search != NULL) {

            temp = strtok(buffer, " ");
            temp = strtok(NULL, " ");
            obj->verts[v_index].x = atof(temp);
            if (fabsf(obj->verts[v_index].x) > fabsf(max))
                max = obj->verts[v_index].x;
            temp = strtok(NULL, " ");
            obj->verts[v_index].y = atof(temp);
            if (fabsf(obj->verts[v_index].y) > fabsf(max))
                max = obj->verts[v_index].y;
            temp = strtok(NULL, " ");
            obj->verts[v_index].z = atof(temp);
            if (fabsf(obj->verts[v_index].z) > fabsf(max))
                max = obj->verts[v_index].z;
            v_index++;
            continue;
        }
        // TODO: Finish Vector Normals
        vn_search = strstr(buffer, "vn");
        if (vn_search != NULL) {
            continue;
        }
        // TODO: Finish Vector Templates
        vt_search = strstr(buffer, "vt");
        if (vt_search != NULL) {
            continue;
        }
        // TODO: Work on v/vn/vt format
        f_search = strstr(buffer, "f ");
        if (f_search != NULL) {
            temp = strtok(buffer, " ");
            temp = strtok(NULL, " ");
            obj->faces[f_index].v[0] = atoi(temp) - 1;
            temp = strtok(NULL, " ");
            obj->faces[f_index].v[1] = atoi(temp) - 1;
            temp = strtok(NULL, " ");
            obj->faces[f_index].v[2] = atoi(temp) - 1;
            f_index++;
            continue;
        }
    }

    for (int i = 0; i < obj->vert_count; i++) {
        obj->verts[i].x /= fabsf(max);
        obj->verts[i].y /= -fabsf(max);
        obj->verts[i].z /= fabsf(max);
    }

//    print_obj(*obj);

    fclose(fp);

    return 1;
}

void errhandler(LPTSTR error_str, HWND hwnd) {
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
                                      (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)error_str) + 40) * sizeof(TCHAR));
//    StringCchPrintf((LPTSTR)lpDisplayBuf,
//                    LocalSize(lpDisplayBuf) / sizeof(TCHAR),
//                    TEXT("%s failed with error %d: %s"),
//                    error_str, dw, lpMsgBuf);
    sprintf(lpDisplayBuf, "%s failed with error %d: %s", error_str, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}
#endif