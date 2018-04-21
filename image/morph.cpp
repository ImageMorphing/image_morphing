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

using namespace std;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 * main:
 *
 * Main function to collect user parameters and pass them to morph().
 */


int main(int argc, char **argv) {
    int nframes;        // number of frames
    string name;        // basename
    image_ptr I1, I2;    // source and target images
    image_ptr M1, M2;    // source and target mesh
    
    // make sure the user invokes this program properly
    if(argc != 7) {
        cerr << "Usage: morph src.bw dst.bw src.XY dst.XY frames name\n";
        exit(1);
    }
    
    // read input image and meshes
    
    I1 = readImage(argv[1], BW);        // source image
    I2 = readImage(argv[2], BW);        // target image
    M1 = readImage(argv[3], MESH);    // source mesh
    M2 = readImage(argv[4], MESH);    // target mesh
    
    morph(I1, I2, M1, M2, nframes, name.c_str());
}



