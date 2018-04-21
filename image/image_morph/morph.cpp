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
    image_util img_utl = image_util("/Users/aUcid/Desktop/image/image/");
    image_io_processor img_pro = image_io_processor("/Users/aUcid/Desktop/image/image/");
    
    IplImage* i1 = img_pro.load_image("ts1989.jpg"),
            * i2 = img_pro.load_image("ts1989.jpg");
    
    
    image_ptr I1 = img_utl.read_image_as_bw(i1),
              I2 = img_utl.read_image_as_bw(i2);    // source and target images
    image_ptr M1 = img_utl.read_mesh("1.mesh"),
              M2 = img_utl.read_mesh("2.mesh");    // source and target mesh
    
    morph(I1, I2, M1, M2, frame_num, name);
    
    return 0;
}



