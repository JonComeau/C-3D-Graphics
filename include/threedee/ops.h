//
// Created by vylly on 6/12/2020.
//

#ifndef THREEDEE_OPS_H
#define THREEDEE_OPS_H

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b;})

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b;})

#endif //THREEDEE_OPS_H
