#include <math.h>
#include "threedee/types.h"
#include "threedee/matrix.h"
#include "threedee/s_t_r.h"

/// This function builds the sin/cos angle lookups for quick access
void build_lookup_tables() {
    int angle;
    float rad;

    // Generate the tables
    for (angle = 0; angle <= 360; angle++) {
        // convert deg to rad
        rad = (float)(3.14159 * (float)angle/(float)180);

        cos_look[angle] = cosf(rad);
        sin_look[angle] = sinf(rad);
    }
}