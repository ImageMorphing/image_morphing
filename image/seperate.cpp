///********************************************************************/
///*Seperate SGI color image to BW image files                                                                 */
///*File name: seperate.c                                                                                                    */
///*Author:    Yurong Sun, Joseph Pan                                                                                                 */
///*Description:                                                                                                                  */
///*            Read color SGI format image file                                                                      */
///*            Create three grayscale BW format images relative to r, g, b channels                  */
///********************************************************************/
//
//#include <iostream>
//
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/core/utility.hpp>
//
//#include "image_io_processor.hpp"
//
//using namespace std;
//
//#define IXSIZE 400
////#define IYSIZE 400
//#define IZSIZE 3
//
//int main(int argc, char **argv) {
//    auto img_pro = image_io_processor();
//    
//    /* Read the input RGB file*/
//    string path = "/Users/aUcid/Desktop/image/image/";
//    
//    IplImage *pSrcImage = img_pro.load_image(path + "ts1989.jpg"),
//             *pR_Plane = img_pro.init_image(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1),
//             *pG_Plane = cvCloneImage(pR_Plane),
//             *pB_Plane = cvCloneImage(pR_Plane);
//
//    IplImage *pR_Channel = img_pro.init_image(cvGetSize(pSrcImage), IPL_DEPTH_8U, 3),
//             *pG_Channel = cvCloneImage(pR_Channel),
//             *pB_Channel = cvCloneImage(pR_Channel);
//
//    cvSplit(pSrcImage, pB_Plane, pG_Plane, pR_Plane, NULL);
//
//    // Begin to write output files
//    // output the red channel jpg file
//    cvMerge(0, 0, pR_Plane, 0, pR_Channel);
//    img_pro.save_image(path + "r.bw", pR_Channel);
//
//    // output the green channel BW file
//    cvMerge(0, pG_Plane, 0, 0, pG_Channel);
//    img_pro.save_image(path + "g.bw", pG_Channel);
//
//    // output the blue channel BW file
//    cvMerge(pB_Plane, 0, 0, 0, pB_Channel);
//    img_pro.save_image(path + "b.bw", pB_Channel);
//
//}
//
