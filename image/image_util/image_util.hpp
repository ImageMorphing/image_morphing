//
//  image_util.hpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#ifndef image_util_hpp
#define image_util_hpp

#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "image_io_processor.hpp"

#include "typedef_c.hpp"

class image_util {
public:
    image_util(std::string);
    ~image_util();
    
    image_ptr read_image_as_bw(IplImage* img);
    image_ptr read_mesh(std::string file_name);
    
    void save_image_as_bw(image_ptr img, std::string file_name);
    void save_mesh(image_ptr mes, std::string file_name);
    
    image_ptr allo_image(int width, int height, int type);
    void free_image(image_ptr ptr);
    
private:
    image_io_processor img_pro;
    
    std::string path;
    
    image_ptr tran_image(IplImage*);
    image_ptr tran_image(FILE*);
};

#endif /* image_util_hpp */
