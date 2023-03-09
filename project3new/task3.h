//
//  task3.h
//  Project3
//
//  Created by Bennett Brain on 2/14/23.
//


// assign the largest non-background region bright red, the second largest bright blue, and the third largest bright green.  Assign the rest shades of grey
int connectedComponentsDisplay(cv::Mat& labeledIm, cv::Mat& dst, cv::Mat& stats, int nlabels);

// find the id of the largest area in the center of the image, as defined by the centroid being within the given ratio of the image(i.e. .8 means middle 80 % of the image)
int largestCenterID(cv::Mat& labeledIm, cv::Mat& stats, cv::Mat& centroids, int nlabels, float centerRatio);
