/* ====================================================================== 
 * meshwarp.h -  Mesh warping header file.
 * Copyright (C) 1993 by George Wolberg
 *
 * Written by: George Wolberg, 1993
 * ======================================================================
 */

#ifndef MESHWARP_H
#define MESHWARP_H

#define BW  0 
#define MESH  1

#include "typedef_c.hpp"

//#define MAX(A,B) ((A) > (B) ? (A) : (B))
//#define MIN(A,B) ((A) < (B) ? (A) : (B))

inline int MAX(const int A, const int B)
{
    return ((A) > (B) ? (A) : (B));
}

inline int MIN(const int A, const int B)
{
    return ((A) < (B) ? (A) : (B));
}

/* extern declarations for functions in meshwarp.c */ 
extern void meshWarp(image_ptr I1, image_ptr M1, image_ptr M2, image_ptr I2); 
extern void resample(uchar *src, int len, int offst, float *xmap, uchar *dst);

/* extern declarations for functions in util.c */ 
extern image_ptr readImage(char *file, int type); 
extern int saveImage(image_ptr I, char *file, int type); 
extern image_ptr allocImage(int w, int h, int type); 
extern void freeImage(image_ptr I); 

#endif
