//
//  task3.h
//  Project3
//
//  Created by Bennett Brain on 2/16/23.

int reThresholdID(cv::Mat& labeledIm, cv::Mat& dst, int labelID);

int drawBB(cv::Mat& rethresh, cv::Mat& stats, int labelID);
