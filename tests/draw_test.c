#ifdef WIN32
#include <float.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <threedee/matrix.h>
#include <math.h>
#include <threedee/s_t_r.h>
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

vec3f LIGHT_DIR, EYE, CENTER, UP;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char read_obj(object_ptr obj, const char *filename) ;

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

    static object obj;
    static bitmap bitmap;

    static mat4x4 projection;
    static float f_near, f_far, f_fov, f_aspect, f_fov_rad;

    int index, jndex;
    face_ptr face;
    vec3f_ptr vec;
    vec3f n, world_coords[3];
    vec2i screen_coords[3];
    float intensity;

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

            read_obj(&obj, "C:\\threedee\\african_head.obj");

            break;
        }
        case WM_SIZE:
            cxClient = LOWORD(lParam);
            cyClient = HIWORD(lParam);
            break;
        case WM_PAINT:
            // This initializes the Bitmap
            create_bitmap(&bitmap, width, height, 4);

            LIGHT_DIR = (vec3f){0, 0, -1};
            for (index = 0; index < obj.face_count; index++) {
                face = &obj.faces[index];
                for (jndex = 0; jndex < 3; jndex++) {
                    vec = &obj.verts[face->v[jndex] + 1];
                    screen_coords[jndex] = (vec2i){(vec->x + 1.) * width / 2., (vec->y + 1.) * height / 2.};
                    world_coords[jndex] = *vec;
                }
                n = vec3f_vec3f_cross(
                        vec3f_vec3f_sub(world_coords[2], world_coords[0]),
                        vec3f_vec3f_sub(world_coords[1], world_coords[0]));
                n = vec3f_normalize(n);
                intensity = vec3f_vec3f_mult(n, LIGHT_DIR);
                if (intensity > 0) {
                    draw_tri(&bitmap, &screen_coords[0], &screen_coords[1], &screen_coords[2],
                             &(color){(unsigned char) (intensity * 255),
                                      (unsigned char) (intensity * 255),
                                      (unsigned char) (intensity * 255), 255});
                }
            }

            flip_vert(&bitmap);

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

char read_obj(object_ptr obj, const char *filename) {
    FILE *fp;
    int index;
    int v_count, vn_count, vt_count, f_count;
    int v_index, vn_index, vt_index, f_index;
    char buffer[1000], *temp, *v_search, *vn_search, *vt_search, *f_search;
    fp = fopen(filename, "r");
    if (!fp) return -1;

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
        v_search = strstr(buffer, "v");
        if (v_search != NULL) {

            temp = strtok(buffer, " ");
            temp = strtok(NULL, " ");
            obj->verts[v_index].x = atof(temp);
            temp = strtok(NULL, " ");
            obj->verts[v_index].y = atof(temp);
            temp = strtok(NULL, " ");
            obj->verts[v_index].z = atof(temp);
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
        f_search = strstr(buffer, "f");
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

    fclose(fp);

    return 1;
}
#endif