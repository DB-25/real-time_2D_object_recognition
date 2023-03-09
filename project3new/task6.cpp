//
//  task6.cpp
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/16/23.
//  Edited by Bennett Brain on 2/19/23

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "task6.h"

// we will use nearest neighbours approach to find the classification of new image
std::string classifyNewImage(double targetVector[7],std::vector<std::vector<std::string>> data){
    std::string predictedLabel = "";
    if(data.size() == 0){
        printf("No data in csv File\n");
        return "Unknown";
    }
    // now compare the feature vector of the new image with the feature vectors of the images in the database
    std::vector<std::pair<std::string,double>> distanceVector;
    distanceVector.clear();

    //initialize arrays for the mean and stdev of each feature to 0s
    double mean[7] = { 0 };
    double stDev[7] = { 0 };

    //need one pass for mean for each feature, then another pass for stdev
    for (int i = 0; i < data.size(); i++) {
        // sum up to the mean
        for (int j = 1; j < 8; j++) {
            mean[j-1] = mean[j-1] + std::stod(data[i][j]);

        }
    }
    //finish by dividing mean by # of values
    for (int j = 0; j < 7; j++) {
        mean[j] = mean[j]/data.size();
    }

    //calculate stdev
    for (int i = 0; i < data.size(); i++) {
        // sum up difference terms in stdev
        for (int j = 1; j < 8; j++) {
            stDev[j - 1] = stDev[j - 1] + (std::stod(data[i][j]) - mean[j - 1]) * (std::stod(data[i][j]) - mean[j - 1]);

        }
    }

    //finish by dividing stdev by # of values and square rooting
    for (int j = 0; j < 7; j++) {
        stDev[j] = std::sqrt(stDev[j] / data.size());
    }


    for(int i = 0; i < data.size(); i++){
        // get the feature vector of the image in the database
        double vectorArray[7];
        // get the vector Array from data such that the first element is the primary key
        // and the last element is the label
        // rest are the feature vector
        for(int j = 1; j < 8; j++){
            vectorArray[j-1] = 0.0;
            vectorArray[j-1] = std::stod(data[i][j]);
            
        }
        
        // find the distance between the two vectors
        double distance = findDistance(targetVector, vectorArray, stDev);
        std::pair<std::string,double> pair;
        pair.first = data[i][8];
        pair.second = distance;
        distanceVector.push_back(pair);
    }
    // find the minimum distance
    // sort the vector based on the distance
    std::sort(distanceVector.begin(), distanceVector.end(), [](const std::pair<std::string,double> &left, const std::pair<std::string,double> &right) {
        return left.second < right.second;
    });
    std::cout << "Closest 3 labels: " << (distanceVector[0].first) << ", " << (distanceVector[1].first) << ", " << (distanceVector[2].first) << std::endl;
    printf("Distance: %f,%f,%f\n",distanceVector[0].second,distanceVector[1].second,distanceVector[2].second);
    // maintain a threshold value, if distance is greater than threshold return "Unknow"
    double threshold = 1.7; //needed some testing
    if(distanceVector[0].second > threshold){
        return "Unknown";
    }
    // else
    // return the label of the image with the minimum distance
    predictedLabel = distanceVector[0].first;
    return predictedLabel;
}

// Method to find the distance between two vectors
// It takes in input of two vectors and uses scaled Euclidean distance metric [ (x_1 - x_2) / stdev_x ], summed over each entry.
// returns the distance between the two vectors
double findDistance(double vector1[7], double vector2[7], double stDev[7]) {

    // calculate the distance
    double distance = 0;
    for(int i = 0; i < 7; i++){
        distance += std::abs((vector1[i] - vector2[i]) / stDev[i]);
    }
    
    return distance;
    //distance = sqrt(distance);
    /*double distance = 0;
    for(int i = 0; i < 7; i++){
        distance += pow((vector1[i] - vector2[i]),2);
    }
    distance = sqrt(distance);
    return distance;*/
}
