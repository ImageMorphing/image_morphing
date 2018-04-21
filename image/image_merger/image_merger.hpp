//
//  image_merger.hpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#ifndef image_merger_hpp
#define image_merger_hpp

#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "image_io_processor.hpp"

class image_merger {
public:
    image_merger(std::string);
    ~image_merger();
    
    
    void merg_image(std::string);
    
    void __check_path__();
    
private:
    std::string path;
    
    IplImage* res_img;
    
    image_io_processor img_pro;
};

#endif /* image_merger_hpp */
