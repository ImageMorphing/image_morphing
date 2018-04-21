//
//  image_seperator.hpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#ifndef image_seperator_hpp
#define image_seperator_hpp

#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "image_io_processor.hpp"

class image_seperator {
public:
    image_seperator(std::string);
    ~image_seperator();
    
    void sepe_image(std::string);
    
private:
    std::string path;
    
    image_io_processor img_pro;
};

#endif /* image_seperator_hpp */
