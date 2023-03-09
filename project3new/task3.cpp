//
//  task3.cpp
//  Project3
//
//  Created by Bennett Brain on 2/14/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "task3.h"

// assign the largest non-background region bright red, the second largest bright blue, and the third largest bright green.  Assign the rest shades of grey
int connectedComponentsDisplay(cv::Mat& labeledIm, cv::Mat& dst, cv::Mat& stats, int nlabels) {
    // allocate dst image
    dst = cv::Mat::zeros(labeledIm.size(), CV_8UC3);

    int statArea = 4; //needed to reference area from stats
    int largestID = -1; //note: true largest will be background, which will always be the 0th label
    int largestArea = -1; //initialized to negative so the code works.  Will be negative if there are less than the req # of areas to have a nth largest
    int secLargestID = -1;
    int secLargestArea = -1;
    int thirdLargestID = -1;
    int thirdLargestArea = -1;
    int numRemaining = nlabels - 4;
    int gsclStep;

    int currArea;

    for (int i = 1; i < nlabels; i++) { //ignore background (i = 0), get largest area index
        currArea = stats.at<int>(i, statArea);
        if (currArea > largestArea) {
            largestArea = currArea;
            largestID = i;
        }
    }
    for (int j = 1; j < nlabels; j++) { //ignore background, get second largest area index
        if (j != largestID) {
            currArea = stats.at<int>(j, statArea);
            if (currArea > secLargestArea) {
                secLargestArea = currArea;
                secLargestID = j;
            }
        }
    }
    for (int k = 1; k < nlabels; k++) { //ignore background, third largest area index
        if (k != largestID && k != secLargestID){
            currArea = stats.at<int>(k, statArea);
            if (currArea > thirdLargestArea) {
                thirdLargestArea = currArea;
                thirdLargestID = k;
            }
        }
    }

    if (numRemaining > 0) {
        gsclStep = 255 / nlabels;
    }

    for (int i = 0; i < labeledIm.rows; i++) {
        // get the row pointer
        int* rptr = labeledIm.ptr<int>(i);
        cv::Vec3b* dptr = dst.ptr<cv::Vec3b>(i);
        for (int j = 0; j < labeledIm.cols; j++) {
            // get the label id
            int labelID = rptr[j];

            
            if (labelID == 0) {//if it's background, set it to black
                dptr[j][0] = 0;
                dptr[j][1] = 0;
                dptr[j][2] = 0;
            }
            else if (labelID == largestID) {//if it's the largest area, set it to red
                dptr[j][0] = 0;
                dptr[j][1] = 0;
                dptr[j][2] = 255;
            }
            else if (labelID == secLargestID) {//second largest => blue
                dptr[j][0] = 255;
                dptr[j][1] = 0;
                dptr[j][2] = 0;
            }
            else if (labelID == thirdLargestID) {//third largest => green
                dptr[j][0] = 0;
                dptr[j][1] = 255;
                dptr[j][2] = 0;
            }
            else { //otherwise => one of the greys
                int greyval = gsclStep * labelID;
                dptr[j][0] = greyval;
                dptr[j][1] = greyval;
                dptr[j][2] = greyval;

            }

        }

    }

    return 0;
}

//find the id of the largest area in the center of the image, as defined by the centroid being within the given ratio of the image (i.e. .8 means middle 80% of the image)
int largestCenterID(cv::Mat& labeledIm, cv::Mat& stats, cv::Mat& centroids, int nlabels, float centerRatio) {
    float edgeRatio = ((float) 1 - centerRatio) / (float) 2; //ratio of how many pixels to exclude- i.e. if center ratio is middle 80% of image, we want 10% off each side; (1-.8)/2 = .1

    int minRow = labeledIm.rows * edgeRatio;
    int maxRow = labeledIm.rows - minRow;

    int minCol = labeledIm.cols * edgeRatio;
    int maxCol = labeledIm.cols - minCol;

    int statArea = 4; //needed to reference area from stats
    int largestID = -1;
    int largestArea = -1;
    int currArea;

    for (int i = 1; i < nlabels; i++) {
        
        double xcent = centroids.at<double>(i, 0);
        double ycent = centroids.at<double>(i, 1);
        if (xcent < maxCol && xcent > minCol && ycent < maxRow && ycent > minRow ) { //if the region is "central" enough
            currArea = stats.at<int>(i, statArea);

            if (currArea > largestArea) { //and if the current area is greater than the last largest
                largestArea = currArea; //update the largest area
                largestID = i;
            }

        }
    }

    return largestID;
}
