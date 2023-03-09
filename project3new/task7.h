//
//  task7.h
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/19/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>

// This method will classify new images based on the previously learnt data(stored in csv file)
// by using knn approach to find the classification of new image
// It takes in input of target feature vector and database and k value
// It will return the label based on its calculations.
std::string knnClassify(double vector[7],std::vector<std::vector<std::string>> database, int k);
