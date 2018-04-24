//
//  image_morph.cpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include "image_morph.hpp"

void image_morph(const IplImage* I1, const IplImage* I2, const image_ptr M1, const image_ptr M2, int frame_num, const std::string basename) {
    
    if (I1->nChannels != 1) {
        std::cout << stderr << "Unexpected Dimension Received" << std::endl;
        exit(1);
    }
    
    double  w1, w2;
    std::string name;
    char *p1, *p2, *p3;
    float *x1, *y1, *x2, *y2, *x3, *y3;
    image_util img_utl = image_util("/Users/aUcid/Desktop/image_morphing/image/");
    image_io_processor img_pro = image_io_processor("/Users/aUcid/Desktop/image_morphing/image/");
    
    /* allocate space for tmp images and mesh */
    image_ptr M3 = img_utl.allo_image(M1->width, M1->height, MESH);
    IplImage *Iw1 = img_pro.init_image(cvGetSize(I1), IPL_DEPTH_8U, 1),
             *Iw2 = img_pro.init_image(cvGetSize(I1), IPL_DEPTH_8U, 1),
             *I3 = img_pro.init_image(cvGetSize(I1), IPL_DEPTH_8U, 1);
    
    /* eval total number of points in mesh (totalM) and image (totalI) */
    int totalM = M1->width * M1->height,
        totalI = I1->width * I1->height;
    
    /* copy first frame to basename_000.bw */
    name = basename + "_000.obj";
    img_pro.save_image_as_object(name, I1);
    std::cout << "Finished Frame 0" << std::endl;
    
    for (int i = 1; i < frame_num - 1; i ++) {
        /* M3 <- linearly interpolate between M1 and M2 */
        w2 = (double) i / (frame_num - 1);
        w1 = 1. - w2;
        
        /* linearly interpolate M3 grid */
        x1 = (float *) M1->ch[0]; y1 = (float *) M1->ch[1];
        x2 = (float *) M2->ch[0]; y2 = (float *) M2->ch[1];
        x3 = (float *) M3->ch[0]; y3 = (float *) M3->ch[1];
        for (int j = 0; j < totalM; j ++) {
            x3[j] = x1[j] * w1 + x2[j] * w2;
            y3[j] = y1[j] * w1 + y2[j] * w2;
        }
        
        /* warp I1 and I2 according to grid M3 */
        image_meshwarp(I1, M1, M3, Iw1);
        image_meshwarp(I2, M2, M3, Iw2);
        
        /* cross-dissolve warped images Iw1 and Iw2 */
        p1 = Iw1->imageData;
        p2 = Iw2->imageData;
        p3 = I3->imageData;
        for (int j = 0; j < totalI; j ++)
            p3[j] = p1[j] * w1 + p2[j] * w2;
        
        /* save frame into file */
        std::ostringstream oss;
        oss << basename << "_" << i << ".obj" << std::endl;
        name = oss.str();
        img_pro.save_image_as_object(name, I3);
        std::cout << "Finished Frame " << i << std::endl;
    }
    
    /* copy last frame to basename_xxx.bw */
    std::ostringstream oss;
    oss << basename << "_" << frame_num << ".obj" << std::endl;
    img_pro.save_image_as_object(name, I2);
    std::cout << "Finished Frame " << frame_num << std::endl;
}

