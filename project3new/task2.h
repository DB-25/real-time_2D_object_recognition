//
//  task1.h
//  Project3
//
//  Created by Bennett Brain on 2/14/23.
//

#include <opencv2/opencv.hpp>

//Binary distance from bkg/fg algorithm - if the bool is true, we're measuring distance in the
//foreground from the background, if it's false we're measuring the reverse.  Using 4-connected distance
int binaryDistance4c(cv::Mat& src, cv::Mat& dst, bool fgnd);

//Binary distance from bkg/fg algorithm - if the bool is true, we're measuring distance in the
//foreground from the background, if it's false we're measuring the reverse.  Using 8-connected distance
int binaryDistance8c(cv::Mat& src, cv::Mat& dst, bool fgnd);

//Shrinking using the binary image from the foreground
int shrinkFromDist(cv::Mat distMat, cv::Mat dst, int numShr);

//Expanding using binary distance from the background
int expandFromDist(cv::Mat distMat, cv::Mat dst, int numExp);
