//
//  image_meshwrap.cpp
//  image
//
//  Created by cid aU on 2018/4/21.
//  Copyright © 2018年 cid aU. All rights reserved.
//

#include "image_meshwrap.hpp"

void image_meshwarp(const IplImage* I1, const image_ptr M1, const image_ptr M2, const IplImage* I2) {
    
    if (I1 == 0 || I2 == 0) {
        std::cout << stderr << "Empty Ptr Received" << std::endl;
        exit(1);
    }
    
    image_util img_utl = image_util("/Users/aUcid/Desktop/image_morphing/image/");
    image_io_processor img_pro = image_io_processor("/Users/aUcid/Desktop/image_morphing/image/");
    
    int I_w = I1->width,
        I_h = I1->height,
        M_w = M1->width,
        M_h = M1->height;
    
    float *x1, *y1, *x2, *y2;
    float *xcol, *ycol, *coll;
    
    /* allocate enough memory for a scanline along the longest dimension */
    int n = MAX(I_w, I_h);
    float *indx = new float[n],
          *xrow = new float[n],
          *yrow = new float[n],
          *map  = new float[n];
    
    char *src, *dst;
    
    /* create table of x-intercepts for source mesh's vertical splines */
    image_ptr Mx = img_utl.allo_image(M_w, I_h, MESH);
    for (int y = 0; y < I_h; y ++)
        indx[y] = y;
    
    /* visit each vertical spline */
    for (int u = 0; u < M_w; u++) {
        /* store column as row for spline fct */
        xcol = (float *) M1->ch[0] + u;
        ycol = (float *) M1->ch[1] + u;
        coll = (float *) Mx->ch[0] + u;
        
        /* scan convert vertical splines */
        for (int v = 0; v < M_h; v ++, xcol += M_w)
            xrow[v] = *xcol;
        for (int v = 0; v < M_h; v ++, ycol += M_w)
            yrow[v] = *ycol;
        catmullRom(yrow, xrow, M_h, indx, map, I_h);
        
        /* store resampled row back into column */
        for (int y = 0; y < I_h; y ++, coll += M_w)
            *coll = map[y];
    }
    
    /* create table of x-intercepts for dst mesh's vertical splines */
    for (int u = 0; u < M_w; u ++) { /* visit each  vertical spline  */
        /* store column as row for spline fct */
        xcol = (float *) M2->ch[0] + u;
        ycol = (float *) M2->ch[1] + u;
        coll = (float *) Mx->ch[1] + u;
        
        /* scan convert vertical splines */
        for (int v = 0; v < M_h; v ++, xcol += M_w)
            xrow[v] = *xcol;
        for (int v = 0; v < M_h; v ++, ycol += M_w)
            yrow[v] = *ycol;
        catmullRom(yrow, xrow, M_h, indx, map, I_h);
        
        /* store resampled row back into column */
        for (int y = 0; y < I_h; y ++, coll += M_w)
            *coll = map[y];
    }
    
    /* first pass: warp x using tables in Mx */
    IplImage* I3 = img_pro.init_image(cvSize(I_w, I_h), IPL_DEPTH_8U, 1);
    x1  = (float *) Mx->ch[0];
    x2  = (float *) Mx->ch[1];
    src = I1->imageData;
    dst = I3->imageData;
    for (int x = 0; x < I_w; x ++)
        indx[x] = x;
    for (int y = 0; y < I_h; y ++) {
        /* fit spline to x-intercepts; resample over all cols */
        catmullRom(x1, x2, M_w, indx, map, I_w);
        
        /* resample source row based on map */
        resample(src, I_w, 1, map, dst);
        
        /* advance pointers to next row */
        src += I_w;
        dst += I_w;
        x1  += M_w;
        x2  += M_w;
    }
    img_utl.free_image(Mx);
    
    /* create table of y-intercepts for intermediate mesh's hor splines */
    image_ptr My = img_utl.allo_image(I_w, M_h, MESH);
    x1 = (float *) M2->ch[0];
    y1 = (float *) M1->ch[1];
    y2 = (float *) My->ch[0];
    for (int x = 0; x < I_w; x ++)
        indx[x] = x;
    
    /* visit each horizontal spline */
    for (int v = 0; v < M_h; v ++) {
        /* scan convert horizontal splines */
        catmullRom(x1, y1, M_w, indx, y2, I_w);
        
        /* advance pointers to next row */
        x1 += M_w;
        y1 += M_w;
        y2 += I_w;
    }
    
    /* create table of y-intercepts for dst mesh's horizontal splines */
    x1 = (float *) M2->ch[0];
    y1 = (float *) M2->ch[1];
    y2 = (float *) My->ch[1];
    
    /* visit each horizontal spline   */
    for (int v = 0; v < M_h; v ++) {
        /* scan convert horizontal splines */
        catmullRom(x1, y1, M_w, indx, y2, I_w);
        
        /* advance pointers to next row */
        x1 += M_w;
        y1 += M_w;
        y2 += I_w;
    }
    
    /* second pass: warp y */
    src = I3->imageData;
    dst = I2->imageData;
    for (int y = 0; y < I_h; y ++)
        indx[y] = y;
    for (int x = 0; x < I_w; x ++) {
        
        /* store column as row for spline fct */
        xcol = (float *) My->ch[0] + x;
        ycol = (float *) My->ch[1] + x;
        
        for (int v = 0; v < M_h; v ++, xcol += I_w)
            xrow[v] = *xcol;
        for (int v = 0; v < M_h; v ++, ycol += I_w)
            yrow[v] = *ycol;
        
        /* fit spline to y-intercepts; resample over all rows */
        catmullRom(xrow, yrow, M_h, indx, map, I_h);
        
        /* resample source column based on map */
        resample(src, I_h, I_w, map, dst);
        
        /* advance pointers to next column */
        src++;
        dst++;
    }
    img_utl.free_image(My);
    
    delete I3;
    delete [] indx;
    delete [] xrow;
    delete [] yrow;
    delete [] map;
}



/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * resample:
 *
 * Resample the len elements of src (with stride offst) into dst according
 * to the spatial mapping given in xmap.
 * Perform linear interpolation for magnification and box filtering
 * (unweighted averaging) for minification.
 * Based on Fant's algorithm (IEEE Computer Graphics & Applications, 1/86).
 */
void resample(char *src, int len, int offst, float *xmap, char *dst)
{
    int u, x, v0, v1;
    double val, sizfac, inseg, outseg, acc, inpos[1024];
    
    /* precompute input index for each output pixel */
    for(u=x=0; x<len; x++) {
        while(xmap[u+1]<x) u++;
        inpos[x] = u + (double) (x-xmap[u]) / (xmap[u+1]-xmap[u]);
    }
    
    inseg  = 1.0;
    outseg = inpos[1];
    sizfac = outseg;
    acc = 0.;
    v0 = *src; src += offst;
    v1 = *src; src += offst;
    for(u=1; u<len; ) {
        val = inseg*v0 + (1-inseg)*v1;
        if(inseg < outseg) {
            acc += (val * inseg);
            outseg -= inseg;
            inseg = 1.0;
            v0 = v1;
            v1 = *src;
            src += offst;
        } else {
            acc += (val * outseg);
            acc /= sizfac;
            *dst = (int) MIN(acc, 0xff);
            dst += offst;
            acc = 0.;
            inseg -= outseg;
            outseg = inpos[u + 1] - inpos[u];
            sizfac = outseg;
            u++;
        }
    }
}



