/******************************************************************/
/*Merging three channel's BW format images into one RGB color image                       */
/*File name: merge.c                                                                                                    */
/*Author:    Yurong Sun, Joseph Pan                                                                                               */
/*Description:                                                                                                              */
/*            Read greyscale BW format image file                                                            */
/*            Create color SGI format image file                                                                */
/******************************************************************/
#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "image_io_processor.hpp"

using namespace std;

#define IXSIZE  400
#define IYSIZE  400
#define IZSIZE  3


int main(int argc, char **argv) {
    image_io_processor img_pro = image_io_processor();

    string path = "/Users/aUcid/Desktop/image/image/";
    
    
    IplImage *pR = img_pro.load_image_as_object(path + "r.bw"),
             *pG = img_pro.load_image_as_object(path + "g.bw"),
             *pB = img_pro.load_image_as_object(path + "b.bw");
    
    IplImage *pResImage = img_pro.init_image(cvGetSize(pR), IPL_DEPTH_8U, 3);
    
    /* Read the input BW files*/

    // red channel
    img_pro.show_image(pR);

    // green channel
    img_pro.show_image(pG);

    // blue channel
    img_pro.show_image(pB);

    /*Begin to write output files */
    img_pro.gene_image(pR, pG, pB, pResImage);
    img_pro.save_image(path + "ts1989_res.jpg", pResImage);
    img_pro.show_image(pResImage);
}
