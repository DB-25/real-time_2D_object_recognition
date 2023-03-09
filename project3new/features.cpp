#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include "filter.h"

int center9x9(cv::Mat& src, float *ft) {

    // calculate center location, then subtract 5 for the first index for the 9x9 square
    // 5 is subtracted instead of 4 to account for arrays being indexed at 0
    int startIndRows = (src.size().height / 2) - 5;
    int startIndCols = (src.size().width / 2) - 5;

    int ftInd = 0;

    // loop over src and copy to features array
    for (int i = startIndRows; i < startIndRows+9; i++) {
        // src pointer
        cv::Vec3b* rptr = src.ptr<cv::Vec3b>(i);
        // for each column
        for (int j = startIndCols; j < startIndCols + 9; j++) {
            // copy into features array
            for (int c = 0; c < 3; c++) {
                ft[ftInd] = rptr[j][c];
                ftInd = ftInd + 1;
            }
        }
    }

    // return
    return(0);

}
