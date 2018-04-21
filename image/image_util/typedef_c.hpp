//
//  typedef_c.cpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include <iostream>

#define BW 0
#define MESH 1

typedef unsigned char uchar;

typedef struct {    /* image data structure  */
    int width;      /* image width  (# cols) */
    int height;     /* image height (# rows) */
    void *ch[2];    /* pointers to channels  */
} image_struct, *image_ptr;
