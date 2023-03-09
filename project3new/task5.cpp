//
//  task5.cpp
//  Project3
//
//  Created by Dhruv Kamalesh Kumar on 2/16/23.
//

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "vidDisplay.h"
#include <iostream>
#include <fstream>

int storeFeatureVectorInDB(double featureVector[7], std::ofstream &csvFile, std::vector<std::vector<std::string>> &database)
{
    // get the feature vector
    std::string vector = "";
    // convert the feature vector to a string seperated by spaces
    for (int i = 0; i < 7; i++)
    {
        vector += std::to_string(featureVector[i]);
        if (i != 6)
        {
            vector += ",";
        }
    }
    // get the label
    std::string label = "";
    printf("Enter the label: ");
    std::cin >> label;
    if (label == "")
    {
        printf("Invalid label. Please try again.\n");
        printf("Enter the label: ");
        std::cin >> label;
    }
    if (label == "")
    {
        printf("Try again later.\n");
        return -1;
    }
    // get the current date and time as a primary key
    std::string primaryKey;
    primaryKey = currentDateTime();
    // write the data to the last line of the csv file
    // data: currentDateTime, featureVector, label
    csvFile << primaryKey << "," << vector << "," << label << std::endl;
    std::vector<std::string> data;
    data.push_back(primaryKey);
    data.push_back(std::to_string(featureVector[0]));
    data.push_back(std::to_string(featureVector[1]));
    data.push_back(std::to_string(featureVector[2]));
    data.push_back(std::to_string(featureVector[3]));
    data.push_back(std::to_string(featureVector[4]));
    data.push_back(std::to_string(featureVector[5]));
    data.push_back(std::to_string(featureVector[6]));
    data.push_back(label);
    database.push_back(data);
    return 0;
}
