//
//  main_component.hpp
//  image
//
//  Created by cid aU on 2018/4/28.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#ifndef main_component_hpp
#define main_component_hpp

#include <iostream>

#include "image_util.hpp"
#include "image_morph.hpp"
#include "image_io_processor.hpp"

class main_component {
public:
    main_component(std::string file_addr, std::string base_name, unsigned int frame_num);
    
    void execute(std::string scr_image_name, std::string tgt_image_name);
private:
    std::string file_addr;
    std::string frame_base_name;
    unsigned int frame_num;
    
    image_io_processor img_pro;
    image_util img_utl;
};

#endif /* main_component_hpp */
