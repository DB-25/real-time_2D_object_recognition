//
//  task7.cpp
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/19/23.
//  Edited by Bennett Brain on 2/20/23

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "task7.h"
#include "task6.h"

std::string knnClassify(double targetVector[7],std::vector<std::vector<std::string>> data, int k){
    std::string predictedLabel = "";
    if(data.size() <= k){
        printf("Not Enough data in csv File.\n");
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

    //print statements
    std::cout << "closest labels: ";
    for (int i = 0; i < k; i++) {
        std::cout << distanceVector[i].first << ", ";
    }
    std::cout << std::endl;
    std::cout << "distances: ";
    for (int i = 0; i < k; i++) {
        std::cout << distanceVector[i].second << ", ";
    }
    std::cout << std::endl;


    // maintain a threshold value, if distance is greater than threshold return "Unknow"
    double threshold = 1.7; //needed some testing
    if(distanceVector[0].second > threshold){
        return "Unknown";
    }
    // find the k nearest neighbours
    std::vector<std::string> kNearestNeighbours;
    for(int i = 0; i < k; i++){
        kNearestNeighbours.push_back(distanceVector[i].first);
    }
    // find the label with max frequency
    std::map<std::string,int> frequencyMap;
    for(int i = 0; i < kNearestNeighbours.size(); i++){
        if(frequencyMap.find(kNearestNeighbours[i]) == frequencyMap.end()){
            frequencyMap[kNearestNeighbours[i]] = 1;
        }
        else{
            frequencyMap[kNearestNeighbours[i]] = frequencyMap[kNearestNeighbours[i]] + 1;
        }
    }
    // find the label with max frequency
    int index = 0;
    int max = 0;
    for(int i = 0; i < kNearestNeighbours.size(); i++){
        if(frequencyMap[kNearestNeighbours[i]] > max){
            max = frequencyMap[kNearestNeighbours[i]];
            index = i;
        }
    }
    return kNearestNeighbours[index];
}
