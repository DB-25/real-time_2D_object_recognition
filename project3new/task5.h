//
//  task5.h
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/16/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>


// This is a method to save the feature vector of object in the foreground with user inputted label to a csv file.
// It takes feature vector of image as a double array.
// It also takes in the database in which it can append data.
// In the file the data is stored in this fashion:
// currentDateTime, featurevector, label
// Method returns 0 for successfully saving, and something else otherwise.
int storeFeatureVectorInDB(double featureVector[7], std::ofstream &csvFile,std::vector<std::vector<std::string>> &database);
