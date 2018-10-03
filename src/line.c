#ifdef _WIN32
#include <windows.h>
#include <d2d1.h>
#endif
#include "threedee/line.h"

// This function draws a line from (x0, y0) to (x1, y1) using differential error
// terms (based on Bresenham's work)
void draw_line(int x0, int y0, int x1, int y1, unsigned char color) {
    int dx, // Difference in x's
        dy, // Difference in y's
        x_inc, // Amount in pixel space to move during drawing
        y_inc, // Amount in pixel space to move during drawing
        error = 0, // The Discriminant
        index;


}