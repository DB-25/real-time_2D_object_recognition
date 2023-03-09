//
//  filter.h
//  Project1
//  Copied to project 3 for use of greyscale filter
//
//  Created by Bennett Brain.
//

// function computing greyscale equivalent
int greyscale(cv::Mat& src, cv::Mat& dst);
// function to blur image
int blur5x5(cv::Mat& src, cv::Mat& dst);
//sobel x filter
int sobelX3x3(cv::Mat& src, cv::Mat& dst);
//sobel y filter
int sobelY3x3(cv::Mat& src, cv::Mat& dst);
//gradient magnitude using sobel x and sobel y as inputs
int magnitude(cv::Mat& sx, cv::Mat& sy, cv::Mat& dst);

//gradient wrapper function
int gradient(cv::Mat& src, cv::Mat& dst);

//blurs and quantizes an image using blur5x5
int blurQuantize(cv::Mat& src, cv::Mat& dst, int levels);
//helper for the quantization function
int quantHelper(int cval, int levels);
//Cartoonization.  Calculates gradient magnitude, then blurs, then quantizes, then sets anything above a gradient threshold to black
int cartoon(cv::Mat& src, cv::Mat& dst, int levels, int magThreshold);

//Image Negative - negates all the colors in the image
int imNeg(cv::Mat& src, cv::Mat& dst);
