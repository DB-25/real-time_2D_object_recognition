//
//  filter.cpp
//  Project1
//  Copied to project 3 for use of greyscale filter
//
//  Created by Bennett Brain.
//

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "filter.h"


// src: input image
// dst: output image, allocated by this function, data type is CV_8U
int greyscale(cv::Mat& src, cv::Mat& dst) {
    // initialize zeros
       dst = cv::Mat::zeros(src.rows,src.cols, CV_8U);
       // we will use the approach of computing the avg of bgr colors to form the greyscale img
       if(!src.data){
           std::printf("No data from Video Source!\n");
           return -1;
       }
       // apply filter
       for(int i = 0; i < src.rows; i++){
          // iterate over rows
          cv::Vec3b *rptr = src.ptr<cv::Vec3b>(i);
          uchar *dptr = dst.ptr<uchar>(i);
          // for each col
          for(int j = 0 ; j < src.cols; j++){
              // calculate the avg
              dptr[j] = (rptr[j][0]*0.114+rptr[j][1]*0.587+rptr[j][2]*0.299);
          }
       }
       return 0;
}

// src: input image
// dst: output image, allocated by this function, data type is CV_8UC3
int blur5x5(cv::Mat& src, cv::Mat& dst) {
    // allocate dst image
    dst = cv::Mat::zeros(src.size(), CV_8UC3); // unsigned short data type
    int numEdgeCases = 2;
    src.copyTo(dst);
    
    
    // loop over src and apply filter in x direction
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // src pointer
        cv::Vec3b* rptr = src.ptr<cv::Vec3b>(i);
        // destination pointer
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = numEdgeCases; j < src.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (rptr[j-2][c] + 2*rptr[j - 1][c] + 4*rptr[j][c] + 2*rptr[j + 1][c] + rptr[j + 2][c]) / 10;
            }
        }
    }

    cv::Mat dstCopy;
    dst.copyTo(dstCopy);

    // loop over src and apply filter in y direction
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // src pointer
        cv::Vec3b* rptrm2 = dstCopy.ptr<cv::Vec3b>(i - 2);
        cv::Vec3b* rptrm1 = dstCopy.ptr<cv::Vec3b>(i - 1);
        cv::Vec3b* rptr = dstCopy.ptr<cv::Vec3b>(i);
        cv::Vec3b* rptrp1 = dstCopy.ptr<cv::Vec3b>(i + 1);
        cv::Vec3b* rptrp2 = dstCopy.ptr<cv::Vec3b>(i + 2);
        // destination pointer
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = 2; j < src.cols - 2; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (rptrm2[j][c] + 2 * rptrm1[j][c] + 4 * rptr[j][c] + 2 * rptrp1[j][c] + rptrp2[j][c]) / 10;
            }
        }
    }

    // return
    return(0);
}

// src: input image, data is CV_8UC3
// dst: output image, allocated by this function, data type is CV_16SC3
int sobelX3x3(cv::Mat& src, cv::Mat& dst) {
    // allocate dst image
    dst = cv::Mat::zeros(src.size(), CV_16SC3); // signed short data type
    int numEdgeCases = 1;


    // loop over src and apply filter in x direction
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // src pointer
        cv::Vec3b* rptr = src.ptr<cv::Vec3b>(i);
        // destination pointer
        cv::Vec3s* dptr = dst.ptr<cv::Vec3s>(i);
        // for each column
        for (int j = numEdgeCases; j < src.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (1 * rptr[j - 1][c] - 1 * rptr[j + 1][c]);
            }
        }
    }

    cv::Mat dstCopy;
    dstCopy = cv::Mat::zeros(src.size(), CV_16SC3); // signed short data type
    dst.copyTo(dstCopy);

    // loop over src and apply filter in y direction
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // src pointer
        cv::Vec3s* rptrm1 = dstCopy.ptr<cv::Vec3s>(i - 1);
        cv::Vec3s* rptr = dstCopy.ptr<cv::Vec3s>(i);
        cv::Vec3s* rptrp1 = dstCopy.ptr<cv::Vec3s>(i + 1);
        // destination pointer
        cv::Vec3s* dptr = dst.ptr<cv::Vec3s>(i);
        // for each column
        for (int j = numEdgeCases; j < src.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (1 * rptrm1[j][c] + 2 * rptr[j][c] + 1 * rptrp1[j][c]) / 4;
            }
        }
    }

    //return
    return 0;
}


// src: input image
// dst: output image, allocated by this function, data type is CV_8UC3
int sobelY3x3(cv::Mat& src, cv::Mat& dst) {
    // allocate dst image
    dst = cv::Mat::zeros(src.size(), CV_16SC3); // signed short data type
    int numEdgeCases = 1;


    // loop over src and apply filter in x direction
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // src pointer
        cv::Vec3b* rptr = src.ptr<cv::Vec3b>(i);
        // destination pointer
        cv::Vec3s* dptr = dst.ptr<cv::Vec3s>(i);
        // for each column
        for (int j = numEdgeCases; j < src.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (1 * rptr[j - 1][c] + 2 * rptr[j][c] + 1 * rptr[j + 1][c])/4;
            }
        }
    }

    cv::Mat dstCopy;
    dstCopy = cv::Mat::zeros(src.size(), CV_16SC3); // signed short data type
    dst.copyTo(dstCopy);

    // loop over src and apply filter in y direction
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // src pointer
        cv::Vec3s* rptrm1 = dstCopy.ptr<cv::Vec3s>(i - 1);
        cv::Vec3s* rptr = dstCopy.ptr<cv::Vec3s>(i);
        cv::Vec3s* rptrp1 = dstCopy.ptr<cv::Vec3s>(i + 1);
        // destination pointer
        cv::Vec3s* dptr = dst.ptr<cv::Vec3s>(i);
        // for each column
        for (int j = numEdgeCases; j < src.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = (1 * rptrm1[j][c] - 1 * rptrp1[j][c]);
            }
        }
    }

    //return
    return 0;


}


int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst) {

    dst = cv::Mat::zeros(sx.size(), CV_8UC3); // signed short data type
    int numEdgeCases = 0;


    // loop over dst and get result of sqrt(Sx*Sx + Sy*Sy)
    for (int i = numEdgeCases; i < sx.rows - numEdgeCases; i++) {
        // sx pointer
        cv::Vec3s* sxptr = sx.ptr<cv::Vec3s>(i);
        // sy pointer
        cv::Vec3s* syptr = sy.ptr<cv::Vec3s>(i);
        // destination pointer
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = numEdgeCases; j < sx.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = sqrt(sxptr[j][c] * sxptr[j][c] + syptr[j][c] * syptr[j][c]);
            }
        }
    }


    //return
    return 0;
}

int gradient(cv::Mat& src, cv::Mat& dst){
    cv::Mat3s sx;
    src.copyTo(sx);
    sobelX3x3(src, sx); //gets the sobel x

    cv::Mat3s sy;
    src.copyTo(sy);
    sobelY3x3(src, sy); //gets the sobel y

    dst = cv::Mat::zeros(src.size(), CV_8UC3);

    magnitude(sx, sy, dst);

    return 0;
}

int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels) {

    cv::Mat temp;
    blur5x5(src, temp);
    
    dst = cv::Mat::zeros(src.size(), CV_8UC3); // signed short data type
    int numEdgeCases = 0;


    // loop over dst and get result of quantization
    for (int i = numEdgeCases; i < temp.rows - numEdgeCases; i++) {
        // blurred source pointer
        cv::Vec3b* bptr = temp.ptr<cv::Vec3b>(i);
        // destination pointer
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = numEdgeCases; j < temp.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = quantHelper(bptr[j][c], levels);
            }
        }
    }
    return 0;
}

int quantHelper(int cval, int levels) {
    int bucketSize = 255 / levels;
    int bucketNo = cval / bucketSize;
    int finalVal = bucketNo * bucketSize;
    return finalVal;
}

int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold){

    cv::Mat bq;
    blurQuantize(src, bq, levels);

    cv::Mat grad;
    //gradient(src, grad);
    gradient(bq, grad); //Unsure if gradient should be calculated before/after the BQ.  Before tends to have more jagged edges while after tends to draw some excess lines

    dst = cv::Mat::zeros(src.size(), CV_8UC3); // signed short data type
    int numEdgeCases = 0;


    // loop over dst and get result of quantization
    for (int i = numEdgeCases; i < bq.rows - numEdgeCases; i++) {
        // blurred/quantized source pointer
        cv::Vec3b* bqptr = bq.ptr<cv::Vec3b>(i);
        // gradient source pointer
        cv::Vec3b* gptr = grad.ptr<cv::Vec3b>(i);
        // destination pointer
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = numEdgeCases; j < bq.cols - numEdgeCases; j++) {
            
            bool overThreshold = false;

            for (int c = 0; c < 3; c++) {
                if (gptr[j][c] > magThreshold) {
                    overThreshold = true;
                }
            }

            for (int c = 0; c < 3; c++) {
                if (overThreshold) {
                    dptr[j][c] = 0;
                }
                else {
                    dptr[j][c] = bqptr[j][c];
                }
                
            }
        }
    }
    return 0;
}

int imNeg(cv::Mat& src, cv::Mat& dst) {

    dst = cv::Mat::zeros(src.size(), CV_8UC3); // signed short data type
    int numEdgeCases = 0;


    // loop over dst and get result of quantization
    for (int i = numEdgeCases; i < src.rows - numEdgeCases; i++) {
        // blurred source pointer
        cv::Vec3b* sptr = src.ptr<cv::Vec3b>(i);
        // destination pointer
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = numEdgeCases; j < src.cols - numEdgeCases; j++) {
            for (int c = 0; c < 3; c++) {
                dptr[j][c] = 255 - sptr[j][c];
            }
        }
    }
    return 0;
}
