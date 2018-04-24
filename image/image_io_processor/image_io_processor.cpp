//
//  image_matrix_processor.cpp
//  image
//
//  Created by cid aU on 2018/4/20.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include "image_io_processor.hpp"

image_io_processor::image_io_processor(std::string file_addr) {
    if (file_addr.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if (file_addr[file_addr.size() - 1] != '/') {
        file_addr += '/';
    }
    path = file_addr;
}

image_io_processor::~image_io_processor() {
    
}

 /*
  * image_io_processor
  * file I/O related
  */
void image_io_processor::save_image_as_object(std::string img_name, const cv::Mat mat) {
    std::string img_path = path + img_name;
    IplImage img = IplImage(mat);
    if (img.nChannels == 1) {
        std::cout << stderr << "This function only accept IplImage with 3 channels, please merge before call this function" << std::endl;
        exit(1);
    }
    cvSave(img_path.data(), &img);
}

void image_io_processor::save_image_as_object(std::string img_name, const IplImage* img) {
    std::string img_path = path + img_name;
    if (img_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if (img) {
        if (img->nChannels == 1) {
            std::cout << stderr << "This function only accept IplImage with 3 channels, please merge before call this function" << std::endl;
            exit(1);
        }
        cvSave(img_path.data(), img);
    } else {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
}

IplImage* image_io_processor::load_image_as_object(std::string img_name) {
    if (img_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    std::string img_path = path + img_name;
    return (IplImage *)cvLoad(img_path.data());
}

void image_io_processor::save_image(std::string img_name, cv::Mat mat) {
    if (img_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    std::string img_path = path + img_name;
    cv::imwrite(img_path, mat);
}

void image_io_processor::save_image(std::string img_name, IplImage *img) {
    if (img == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    if (img->nChannels != 3) {
        std::cout << stderr << "Unexpected Dimension Received" << std::endl;
    }
    if (img_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    std::string img_path = path + img_name;
    cv::imwrite(img_path, cv::cvarrToMat(img));
}

IplImage* image_io_processor::load_image(std::string img_name) {
    if (img_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    std::string img_path = path + img_name;
    return cvLoadImage(img_path.data());
}

/*
 * image_io_processor
 * image create related
 */
IplImage* image_io_processor::init_image(CvSize size, int depth, int channels) {
    auto img = cvCreateImage(size, depth, channels);
    cvZero(img);
    return img;
}


/*
 * image_io_processor
 * image check related
 */
void image_io_processor::show_image(IplImage *img, std::string img_name) {
    if (img == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    cvShowImage(img_name.data(), img);
    cvWaitKey();
}


/*
 * image_io_processor
 * image generate related
 */
IplImage* image_io_processor::gene_image(IplImage *r, IplImage *g, IplImage *b, IplImage *res) {
    if (r->nChannels == 1) {
        return this->gene_image_by_3x1(r, g, b, res);
    } else if (r->nChannels == 3) {
        return this->gene_image_by_3x3(r, g, b, res);
    } else {
        std::cout << stderr << "Unexpected Channel Received" << std::endl;
        exit(1);
    }
}

IplImage* image_io_processor::gene_image_by_3x3(IplImage *r_channel,
                                                IplImage *g_channel,
                                                IplImage *b_channel,
                                                IplImage *res_img) {
    // ptr check
    auto size_ptr = r_channel != 0 ? r_channel : g_channel;
    size_ptr = size_ptr != 0 ? size_ptr : b_channel;
    if (size_ptr == 0) {
        std::cout << stderr << "Empty Ptrs Received" << std::endl;
        exit(1);
    }
    
    IplImage *res = res_img;
    IplImage *r_plane = init_image(cvGetSize(size_ptr), IPL_DEPTH_8U, 1),
             *g_plane = cvCloneImage(r_plane),
             *b_plane = cvCloneImage(r_plane);
    
    if (res == 0)
        res = this->init_image(cvGetSize(size_ptr), IPL_DEPTH_8U, 3);
    
    cvSplit(b_channel, b_plane, 0, 0, 0);
    cvSplit(g_channel, 0, g_plane, 0, 0);
    cvSplit(r_channel, 0, 0, r_plane, 0);
    
    cvMerge(b_plane, g_plane, r_plane, NULL, res);
    
    return res;
}

IplImage* image_io_processor::gene_image_by_3x1(IplImage *r_plane,
                                                IplImage *g_plane,
                                                IplImage *b_plane,
                                                IplImage* res_img) {
    // ptr check
    auto size_ptr = r_plane != 0 ? r_plane : g_plane;
    size_ptr = size_ptr != 0 ? size_ptr : b_plane;
    if (size_ptr == 0) {
        std::cout << stderr << "Empty Ptrs Received" << std::endl;
        exit(1);
    }
    
    IplImage *res = res_img;
    
    if (res == 0)
        res = this->init_image(cvGetSize(size_ptr), IPL_DEPTH_8U, 3);
    
    cvMerge(b_plane, g_plane, r_plane, NULL, res);
    
    return res;
}


/*
 * image_io_processor
 * image convert related
 */
void image_io_processor::conv_image(IplImage *img, char** img_ptr, int index) {
    if (img == 0 || img_ptr == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    int width = img->width,
        height = img->height;
    auto data_ptr = img->imageData;
    if (img->nChannels == 1) {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                img_ptr[y][x] = *(data_ptr + y * width + x);
            }
        }
    } else if (img->nChannels == 3) {
        if (index < 0) {
            std::cout << stderr << "Index of Dimension 3 must have a positive value" << std::endl;
            exit(1);
        }
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                img_ptr[y][x] = *(data_ptr + y * width + x + (index + 1) * height * width);
            }
        }
    } else {
        std::cout << stderr << "Unexpected Dimension Received" << std::endl;
        exit(1);
    }
}

