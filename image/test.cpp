//
//  test.cpp
//  image
//
//  Created by 王崴 on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include "meshwarp.h"
#include <iostream>
#include "image_io_processor.hpp"
using namespace std;

int main(){
    string path = "/Users/wangwai/Downloads";
    string name = "ts1989_res.jpg";
    string absPath = path + name;
    image_io_processor imPro = image_io_processor();
    imPro.load_image(absPath);
    
    return 0;
}
