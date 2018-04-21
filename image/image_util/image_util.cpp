//
//  image_util.cpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include "image_util.hpp"

#define BW  0
#define MESH  1

image_util::image_util(std::string file_addr):img_pro(file_addr) {
    if (file_addr.empty()) {
        std::cout << stderr << "Received Empty String" << std::endl;
        exit(1);
    }
    path = file_addr;
    if (file_addr[file_addr.size() - 1] != '/') {
        path += '/';
    }
}

image_util::~image_util() {}

image_ptr image_util::read_image_as_bw(IplImage *img) {
    auto img_ptr = tran_image(img);
    if (img == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    if (img->nChannels != 1) {
        std::cout << stderr << "Unexpected Dimension Received" << std::endl;
        exit(1);
    }
    memcpy(img_ptr->ch[0], img->imageData, img_ptr->height * img_ptr->width);
    return img_ptr;
}

image_ptr image_util::read_mesh(std::string file_name) {
    /*
     * This function is used to read mesh files
     */
    auto file_path = path + file_name;
    FILE* fin = 0;
    if (file_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if ((fin = fopen(file_path.data(), "r")) == NULL) {
        std::cout << stderr << "File doesn't exist: " << file_path << std::endl;
        exit(1);
    }
    auto img_ptr = tran_image(fin);
    fread(img_ptr->ch[0], img_ptr->width * img_ptr->height, 2*sizeof(float), fin);
    fclose(fin);
    return img_ptr;
}

void image_util::save_image_as_bw(image_ptr img, std::string file_name) {
    FILE* fout = 0;
    std::string file_path = path + file_name;
    if (img == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    if (file_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if ((fout = fopen(file_path.data(), "w")) == NULL) {
        std::cout << stderr << "File doesn't exist: " << file_path << std::endl;
        exit(1);
    }
    fwrite(&img->width, sizeof(int), 1, fout);
    fwrite(&img->height, sizeof(int), 1, fout);
    fwrite(img->ch[0], img->width * img->height, 1, fout);
    fclose(fout);
}

void image_util::save_mesh(image_ptr mes, std::string file_name) {
    FILE* fout = 0;
    std::string file_path = path + file_name;
    if (mes == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    if (file_name.empty()) {
        std::cout << stderr << "Empty Str Received" << std::endl;
        exit(1);
    }
    if ((fout = fopen(file_path.data(), "w")) == NULL) {
        std::cout << stderr << "File doesn't exist: " << file_path << std::endl;
        exit(1);
    }
    fwrite(&mes->width, sizeof(int), 1, fout);
    fwrite(&mes->height, sizeof(int), 1, fout);
    fwrite(mes->ch[0], mes->width * mes->height, 2 * sizeof(float), fout);
    fclose(fout);
}

void image_util::free_image(image_ptr ptr) {
    free((char *) ptr->ch[0]);
    free(ptr);
}

image_ptr image_util::tran_image(IplImage *img) {
    image_ptr ptr = new image_struct();
    if (ptr == 0) {
        std::cout << stderr << "Memory alloc failed" << std::endl;
        exit(1);
    }
    ptr->height = img->height;
    ptr->width = img->width;
    ptr->ch[0] = (uchar *) malloc (ptr->height * ptr->width);
    return ptr;
}

image_ptr image_util::tran_image(FILE* fin) {
    image_ptr ptr = new image_struct();
    if (ptr == 0) {
        std::cout << stderr << "Memory alloc failed" << std::endl;
        exit(1);
    }
    fread(&ptr->width, sizeof(int), 1, fin);
    fread(&ptr->height, sizeof(int), 1, fin);
    ptr->ch[0] = (float *) malloc (2 * ptr->width * ptr->height * sizeof(float));
    ptr->ch[1] = (float *) ptr->ch[0] + ptr->height * ptr->width;
    return ptr;
}
