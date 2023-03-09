//
//  task1.cpp
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/13/23.
//  Edited by Bennett Brain on 2/14/23

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "task1.h"
#include "filter.h"

int thresholding(cv::Mat& src, cv::Mat& dst, int threshold){
    // allocate dst image
    cv::Mat greyScaleImage;
    greyScaleImage = cv::Mat::zeros(src.size(), CV_8UC3);
    // convert to grayscale using custom function in filter.cpp
    greyscale(src,greyScaleImage);
    cv::Mat blurredImage;
    blurredImage = cv::Mat::zeros(src.size(), CV_8UC3);
    blur5x5(greyScaleImage, blurredImage);
    // now we have a blurred image, we can threshold it manually
    // we will use a threshold of threshold
    // if the pixel value is greater than threshold, we will set it to 255
    // if the pixel value is less than threshold, we will set it to 0
    // this will create a binary image
    // we will use a for loop to iterate through the image
    dst = cv::Mat::zeros(src.size(), CV_8U);
    for(int i = 0; i < src.rows; i++){
        // get the row pointer
        uchar *rptr = blurredImage.ptr<uchar>(i);
        uchar *dptr = dst.ptr<uchar>(i);
        for(int j = 0; j < src.cols; j++){
            // get the pixel value
            int pixelValue = rptr[j];
           
            // check if the pixel value is greater than threshold
            if(pixelValue > threshold){
                // set the pixel value to 0 (background)
                dptr[j] = 0;
            }
            else{
                // set the pixel value to 255 (forground
                dptr[j] = 255;
            }
        }

    }
    return 0;
}
