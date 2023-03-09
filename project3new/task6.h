//
//  task6.h
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/16/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>


// This method will classify new images based on the previously learnt data(stored in csv file) by comparing the feature vector for target image and training data.
// It takes in input of target feature vector and database
// It will return the label based on its calculations.
std::string classifyNewImage(double vector[7],std::vector<std::vector<std::string>> database);

// Method to find the distance between two vectors
// It takes in input of two vectors and uses scaled Euclidean distance metric [ (x_1 - x_2) / stdev_x ].
// returns the distance between the two vectors
double findDistance(double vector1[7], double vector2[7], double stDev[7]);
