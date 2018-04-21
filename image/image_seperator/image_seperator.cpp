//
//  image_seperator.cpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include "image_seperator.hpp"

image_seperator::image_seperator(std::string file_addr): img_pro(file_addr) {
    if (file_addr.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if (file_addr[file_addr.size() - 1] != '/') {
        file_addr += '/';
    }
    path = file_addr;
}

image_seperator::~image_seperator() {
    
}

void image_seperator::sepe_image(std::string img_name) {
    IplImage *src_img = img_pro.load_image(img_name),
             *r_plane = img_pro.init_image(cvGetSize(src_img), IPL_DEPTH_8U, 1),
             *g_plane = cvCloneImage(r_plane),
             *b_plane = cvCloneImage(r_plane);
    
    IplImage *r_channel = img_pro.init_image(cvGetSize(src_img), IPL_DEPTH_8U, 3),
             *g_channel = cvCloneImage(r_channel),
             *b_channel = cvCloneImage(r_channel);
    
    cvSplit(src_img, b_plane, g_plane, r_plane, NULL);

    // Begin to write output files
    // output the red channel jpg file
    cvMerge(0, 0, r_plane, 0, r_channel);
    img_pro.save_image(path + "r.obj", r_channel);
    
    // output the green channel BW file
    cvMerge(0, g_plane, 0, 0, g_channel);
    img_pro.save_image(path + "g.obj", g_channel);
    
    // output the blue channel BW file
    cvMerge(b_plane, 0, 0, 0, b_channel);
    img_pro.save_image(path + "b.obj", b_channel);
}

void image_seperator::__check_path__() {
    std::cout << stderr << "Path: " << path << std::endl;
    exit(9);
}
