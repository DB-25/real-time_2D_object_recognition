//
//  task2.cpp
//  Project3
//
//  Created by Bennett Brain on 2/14/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "task2.h"
#include "filter.h"

//Distance algorithm, 4-connected
int binaryDistance4c(cv::Mat& src, cv::Mat& dst, bool fgnd) {
    int targVal;
    if (fgnd) {
        targVal = 255; //the value of the foreground pixels
    }
    else {
        targVal = 0; //the value of the background pixels
    }

    // allocate dst image
    dst = cv::Mat::zeros(src.size(), CV_8U);
    // Now we need to do the first pass, looping through the imaging and labeling each point according to the min of the
    // upper value and leftmost value, plus one.
    for (int i = 0; i < src.rows; i++) {
        // get the row pointer
        uchar* rptr = src.ptr<uchar>(i);
        uchar* dptr = dst.ptr<uchar>(i);
        uchar* dptrm1;
        if (i != 0) {
            dptrm1 = dst.ptr<uchar>(i - 1);
        }
        else {
            dptrm1 = dst.ptr<uchar>(i); //this should never be used but it makes the code compile
        }

        for (int j = 0; j < src.cols; j++) {

            if (rptr[j] != targVal) {
                dptr[j] = 0; //not foreground (or bkg if target val is off)
            }
            else {
                int up;
                int left;
                if (i == 0) { //off the image
                    up = 0;
                }
                else {
                    up = dptrm1[j];
                }
                if (j == 0) { //off the image
                    left = 0;
                }
                else {
                    left = dptr[j - 1];
                }

                dptr[j] = std::min(up, left) + 1;


            }
        }

    }

    //Now we need to do the second pass, going from bottom right to top left and taking the min
    //of the previously-calculated value and the potential new distance
    for (int i = src.rows-1; i >= 0; i--) {
        // get the row pointer
        uchar* dptr = dst.ptr<uchar>(i);
        uchar* dptrp1;
        if (i != src.rows-1) {
            dptrp1 = dst.ptr<uchar>(i + 1);
        }
        else {
            dptrp1 = dst.ptr<uchar>(i); //this should never be used but it makes the code compile
        }
        for (int j = src.cols-1; j >= 0; j--) {
            int down;
            int right;
            if (i == src.rows-1) { //off the image
                down = 0;
            }
            else {
                down = dptrp1[j];
            }
            if (j == src.cols - 1) { //off the image
                right = 0;
            }
            else {
                right = dptr[j + 1];
            }
            int self = dptr[j];
            dptr[j] = std::min(self, std::min(down,right)+1);
        }

    }


    return 0;
}

//Distance algorithm, 8-connected
int binaryDistance8c(cv::Mat& src, cv::Mat& dst, bool fgnd) {
    int targVal;
    if (fgnd) {
        targVal = 255; //the value of the foreground pixels
    }
    else {
        targVal = 0; //the value of the background pixels
    }

    // allocate dst image
    dst = cv::Mat::zeros(src.size(), CV_8U);
    // Now we need to do the first pass, looping through the imaging and labeling each point according to the min of the
    // upper values and leftmost value, plus one.
    for (int i = 0; i < src.rows; i++) {
        // get the row pointer
        uchar* rptr = src.ptr<uchar>(i);
        uchar* dptr = dst.ptr<uchar>(i);
        uchar* dptrm1;
        if (i != 0) {
            dptrm1 = dst.ptr<uchar>(i - 1);
        }
        else {
            dptrm1 = dst.ptr<uchar>(i); //this should never be used but it makes the code compile
        }

        for (int j = 0; j < src.cols; j++) {

            if (rptr[j] != targVal) {
                dptr[j] = 0; //not foreground (or bkg if target val is off)
            }
            else {
                int up;
                int upright;
                int upleft;
                int left;
                if (i == 0) { //top entirely off the image
                    up = 0;
                    upright = 0;
                    upleft = 0;
                }
                else if (j == 0){ //top left is off the image
                    upright = dptrm1[j + 1];
                    up = dptrm1[j];
                    upleft = 0;
                }
                else if (j == src.cols-1) { //top right is off the image
                    upright = 0;
                    up = dptrm1[j];
                    upleft = dptrm1[j - 1];
                }
                else { //all top-row are on the image
                    upright = dptrm1[j + 1];
                    up = dptrm1[j];
                    upleft = dptrm1[j - 1];
                }
                if (j == 0) { //left is off the image
                    left = 0;
                }
                else {
                    left = dptr[j - 1];
                }

                dptr[j] = std::min(std::min(up, left), std::min(upright, upleft)) + 1;


            }
        }

    }

    //Now we need to do the second pass, going from bottom right to top left and taking the min
    //of the previously-calculated value and the potential new distance
    for (int i = src.rows - 1; i >= 0; i--) {
        // get the row pointer
        uchar* dptr = dst.ptr<uchar>(i);
        uchar* dptrp1;
        if (i != src.rows - 1) {
            dptrp1 = dst.ptr<uchar>(i + 1);
        }
        else {
            dptrp1 = dst.ptr<uchar>(i); //this should never be used but it makes the code compile
        }
        for (int j = src.cols - 1; j >= 0; j--) {
            int down;
            int right;
            int downright;
            int downleft;
            if (i == src.rows - 1) { //bottom entirely off the image
                down = 0;
                downright = 0;
                downleft = 0;
            }
            else if (j == 0) { //bottom left is off the image
                downright = dptrp1[j + 1];
                down = dptrp1[j];
                downleft = 0;
            }
            else if (j == src.cols - 1) { //bottom right is off the image
                downright = 0;
                down = dptrp1[j];
                downleft = dptrp1[j - 1];
            }
            else { //all bottom-row pixels are on the image
                downright = dptrp1[j + 1];
                down = dptrp1[j];
                downleft = dptrp1[j - 1];
            }
            if (j == src.cols - 1) { //right is off the image
                right = 0;
            }
            else {
                right = dptr[j + 1];
            }
            int self = dptr[j];
            int dist = std::min(std::min(down, right), std::min(downleft, downright)) + 1;
            dptr[j] = std::min(self, dist);
        }

    }


    return 0;
}

//expansion using result from binary distance algorithm.  dst mat passed in should be distance from foreground
//within the background
int expandFromDist(cv::Mat distMat, cv::Mat dst, int numExp) {
    for (int i = 0; i < distMat.rows; i++) {
        // get the row pointer
        uchar* rptr = distMat.ptr<uchar>(i);
        uchar* dptr = dst.ptr<uchar>(i);

        for (int j = 0; j < distMat.cols; j++) {
            if (rptr[j] <= numExp) { // 0 (foreground) or close enough to the foreground
                dptr[j] = 255; // become or stay foreground
            }
            else { //far enough in the background
                dptr[j] = 0; // remain background
            }
            
        }

    }
    return 0;
}

//contraction using result from binary distance algorithm.  dst mat passed in should be distance from background
//within foreground
int shrinkFromDist(cv::Mat distMat, cv::Mat dst, int numShr) {
    for (int i = 0; i < distMat.rows; i++) {
        // get the row pointer
        uchar* rptr = distMat.ptr<uchar>(i);
        uchar* dptr = dst.ptr<uchar>(i);

        for (int j = 0; j < distMat.cols; j++) {
            if (rptr[j] <= numShr) { // 0 (background) or close enough to the background
                dptr[j] = 0; // become or stay background
            }
            else { //far enough in the foreground
                dptr[j] = 255; // remain foreground
            }

        }

    }
    return 0;
}
