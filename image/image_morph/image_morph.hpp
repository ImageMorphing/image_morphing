//
//  image_morph.hpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#ifndef image_morph_hpp
#define image_morph_hpp

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "image_morph.hpp"
#include "image_util.hpp"
//#include "meshwarp.h"

void morph(const image_ptr I1, const image_ptr I2, const image_ptr M1, const image_ptr M2, int frame_num, const std::string basename);

#endif /* image_morph_hpp */
