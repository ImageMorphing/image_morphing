//
//  image_meshwrap.hpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#ifndef image_meshwrap_hpp
#define image_meshwrap_hpp

#define BW 0
#define MESH 1

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "image_util.hpp"
#include "catmullrom.h"
#include "typedef_c.hpp"

void image_meshwarp(const IplImage* I1, const image_ptr M1, const image_ptr M2, const IplImage* I2);

void resample(char *src, int len, int offst, float *xmap, char *dst);

#endif
