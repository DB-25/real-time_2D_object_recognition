//
//  task4.cpp
//  Project3
//
//  Created by Bennett Brain on 2/16/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "task4.h"

//Re-threshold the image so that just the image id is foreground, given a label id

int reThresholdID(cv::Mat& labeledIm, cv::Mat& dst, int labelID) {
    // allocate dst image
    dst = cv::Mat::zeros(labeledIm.size(), CV_8U);

    for (int i = 0; i < labeledIm.rows; i++) {
        // get the row pointer
        int* rptr = labeledIm.ptr<int>(i);
        uchar* dptr = dst.ptr<uchar>(i);
        for (int j = 0; j < labeledIm.cols; j++) {
            // get the label id
            int currlabelID = rptr[j];


            if (currlabelID != labelID) {//if it's background, set it to background (0)
                dptr[j] = 0;
            }
            else {//else, set to foreground (255)
                dptr[j] = 255;
            }
        }

    }

    return 0;
}

int drawBB(cv::Mat& rethresh, cv::Mat& stats, int labelID){

    // get the locations of the bounding box
    int left = stats.at<int>(labelID, 0);
    int top = stats.at<int>(labelID, 1);
    int right = stats.at<int>(labelID, 2) + left;
    int bottom = stats.at<int>(labelID, 3) + top;

    // draw the top and bottom lines
    for (int i = left; i < right; i++) {
        rethresh.at<uchar>(top, i) = 255;
        rethresh.at<uchar>(bottom, i) = 255;

    }

    // draw the left and right lines
    for (int i = top; i < bottom; i++) {
        rethresh.at<uchar>(i, left) = 255;
        rethresh.at<uchar>(i, right) = 255;

    }


    return 0;
}
