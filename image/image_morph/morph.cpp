/* ======================================================================
 * morph.c -  Generate a metamorphosis sequence.
 * Copyright (C) 1993 by George Wolberg
 *
 * Written by: George Wolberg, 1993
 * Edited by: Joseph Pan, 2013
 * ======================================================================
 */

//#include "meshwarp.h"
#include "morph.h"
#include "util.h"

#include <iostream>

#include "image_util.hpp"
#include "image_morph.hpp"

using namespace std;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * main:
 *
 * Main function to collect user parameters and pass them to morph().
 */


int main(int argc, char **argv) {
    int frame_num = 10;        // number of frames
    string name = "ts";        // basename
    image_util img_utl = image_util("/Users/aUcid/Desktop/image_morphing/image/");
    image_io_processor img_pro = image_io_processor("/Users/aUcid/Desktop/image_morphing/image/");
    
    IplImage* i1 = img_pro.load_image("ts1989.jpg"),
            * i2 = img_pro.load_image("tsrep.jpg");
    IplImage* r_channel_1 = img_pro.init_image(cvGetSize(i1), IPL_DEPTH_8U, 1),
            * g_channel_1 = img_pro.init_image(cvGetSize(i1), IPL_DEPTH_8U, 1),
            * b_channel_1 = img_pro.init_image(cvGetSize(i1), IPL_DEPTH_8U, 1);
    IplImage* r_channel_2 = img_pro.init_image(cvGetSize(i1), IPL_DEPTH_8U, 1),
            * g_channel_2 = img_pro.init_image(cvGetSize(i1), IPL_DEPTH_8U, 1),
            * b_channel_2 = img_pro.init_image(cvGetSize(i1), IPL_DEPTH_8U, 1);
    cvSplit(i1, b_channel_1, g_channel_1, r_channel_1, NULL);
    cvSplit(i2, b_channel_2, g_channel_2, r_channel_2, NULL);
    
    image_ptr I_r_1 = img_utl.read_image_as_bw(r_channel_1),
              I_g_1 = img_utl.read_image_as_bw(g_channel_1),
              I_b_1 = img_utl.read_image_as_bw(b_channel_1);
    image_ptr I_r_2 = img_utl.read_image_as_bw(r_channel_2),
              I_g_2 = img_utl.read_image_as_bw(g_channel_2),
              I_b_2 = img_utl.read_image_as_bw(b_channel_2);    // source and target images
    image_ptr M1 = img_utl.read_mesh("1.mesh"),
              M2 = img_utl.read_mesh("2.mesh");    // source and target mesh
    
    image_morph(r_channel_1, r_channel_2, M1, M2, frame_num, name);
    image_morph(g_channel_1, g_channel_2, M1, M2, frame_num, name);
    image_morph(b_channel_1, b_channel_2, M1, M2, frame_num, name);
    
    return 0;
}



