//
//  vidDisplay.cpp
//  Project1
//
//  Created by Dhruv Kamalesh Kumar on 2/5/23.
//  Edited by Bennett Brain on 2/14/23

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "vidDisplay.h"
#include "filter.h"
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "task5.h"
#include "task6.h"
#include "task7.h"
#include <fstream>
#include <iostream>

const std::string csvFileName = "data.csv";

int displayLiveVideoFeed(cv::VideoCapture *capdev){
    cv::namedWindow("Live Video", 1);
    cv::Mat originalFrame;
    // filtered frame / modified frame
    cv::Mat filteredFrame;
    // get some properties of the image
   cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                  (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
   printf("Expected size: %d %d\n", refS.width, refS.height);

   // open a csv file for write
    std::ofstream csvFile;
    csvFile.open(csvFileName, std::ios::out | std::ios::app);
    if (!csvFile.is_open()) {
        printf("Error opening csv file.\n");
        return -1;
    }
    
    // open a csv file for reading
    std::fstream readCsvFile;
    readCsvFile.open(csvFileName, std::ios::in);
    if(!readCsvFile.is_open()){
        printf("Error opening csv file.\n");
        return -1;
    }
    
    // creating a caching DB
    std::vector<std::vector<std::string>> database;
    std::string line;
    while(getline(readCsvFile,line)){
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while(getline(ss,cell,',')){
            row.push_back(cell);
        }
        database.push_back(row);
    }
    
    // turn filter on/off
    bool filterOn;
    // store the char for the filter selected
    char lastFilterSelected;
    filterOn = false;
    // o --> original
    lastFilterSelected = 'o';
    for(;;) {
        *capdev >> originalFrame; // get a new frame from the camera, treat as a stream
        if(originalFrame.empty()) {
            printf("Frame is empty\n");
            break;
        }
        //if filter is on display filter frame
        if (filterOn && lastFilterSelected != 'o') {
            if(lastFilterSelected == '1'){
                int threshold = 115;
                thresholding(originalFrame, filteredFrame, threshold);
            }
            else if (lastFilterSelected == '2') {
                int threshold = 115;
                thresholding(originalFrame, filteredFrame, threshold); //first you threshold

                cv::Mat distFrame;
                binaryDistance4c(filteredFrame,distFrame,true); //we're going to shrink first so we want distance in the foreground from the background
                shrinkFromDist(distFrame, filteredFrame, 2); //going to do 2 shrinks, then 4 grows, then 2 shrinks
                binaryDistance8c(filteredFrame, distFrame, false); //now grows, so we need distance in bkg from fg, using 8-connected instead of 4-connected to balance
                expandFromDist(distFrame, filteredFrame, 4); //now 4 grows
                binaryDistance4c(filteredFrame, distFrame, true); //final 2 shrinks
                shrinkFromDist(distFrame, filteredFrame, 2);
            }
            else if (lastFilterSelected == '3') {
                int threshold = 115;
                thresholding(originalFrame, filteredFrame, threshold); //first you threshold

                cv::Mat distFrame;
                binaryDistance4c(filteredFrame, distFrame, true); //we're going to shrink first so we want distance in the foreground from the background
                shrinkFromDist(distFrame, filteredFrame, 2); //going to do 2 shrinks, then 4 grows, then 2 shrinks
                binaryDistance8c(filteredFrame, distFrame, false); //now grows, so we need distance in bkg from fg, using 8-connected instead of 4-connected to balance
                expandFromDist(distFrame, filteredFrame, 4); //now 4 grows
                binaryDistance4c(filteredFrame, distFrame, true); //final 2 shrinks
                shrinkFromDist(distFrame, filteredFrame, 2);

                //Now use openCV functionality to do connected components analysis
                cv::Mat labels;
                cv::Mat stats;
                cv::Mat centroids;
                int nlabels;

                //existing openCV functionality
                nlabels = cv::connectedComponentsWithStats(filteredFrame,labels, stats, centroids);

                //displays largest non-bg area as red, second largest as blue, third largest as green
                connectedComponentsDisplay(labels,filteredFrame,stats,nlabels);
                

                //commented out for now, but this gets the id of the largest region in the center 70% of the image
                //int desiredID = largestCenterID(labels, stats, centroids, nlabels, 0.7);
                //std::cout << desiredID << std::endl;
                
            }else if(lastFilterSelected == '4'){
                // task 4 code

                int threshold = 115;
                thresholding(originalFrame, filteredFrame, threshold); //first you threshold

                cv::Mat distFrame;
                binaryDistance4c(filteredFrame, distFrame, true); //we're going to shrink first so we want distance in the foreground from the background
                shrinkFromDist(distFrame, filteredFrame, 2); //going to do 2 shrinks, then 4 grows, then 2 shrinks
                binaryDistance8c(filteredFrame, distFrame, false); //now grows, so we need distance in bkg from fg, using 8-connected instead of 4-connected to balance
                expandFromDist(distFrame, filteredFrame, 4); //now 4 grows
                binaryDistance4c(filteredFrame, distFrame, true); //final 2 shrinks
                shrinkFromDist(distFrame, filteredFrame, 2);

                //Now use openCV functionality to do connected components analysis
                cv::Mat labels;
                cv::Mat stats;
                cv::Mat centroids;
                int nlabels;

                //existing openCV functionality
                nlabels = cv::connectedComponentsWithStats(filteredFrame, labels, stats, centroids);

                int desiredID = largestCenterID(labels, stats, centroids, nlabels, 0.5);
                reThresholdID(labels, filteredFrame, desiredID);

                cv::Moments moments = cv::moments(filteredFrame, false);

                drawBB(filteredFrame,stats,desiredID);

                double huMoments[7]; //rotation, translation, scale invariant moments
                cv::HuMoments(moments, huMoments);
                for (int i = 0; i < 7; i++) { //convert to log so moments are roughly on the same scale as each other
                    huMoments[i] = -1 * copysign(1.0, huMoments[i]) * log10(abs(huMoments[i]));
                }
                std::cout << "Hu moment 0: " << huMoments[0] << ", Hu moment 1: " << huMoments[1] << std::endl;
            }
            else if (lastFilterSelected == '5'){
                int threshold = 115;
                thresholding(originalFrame, filteredFrame, threshold); //first you threshold

                cv::Mat distFrame;
                binaryDistance4c(filteredFrame, distFrame, true); //we're going to shrink first so we want distance in the foreground from the background
                shrinkFromDist(distFrame, filteredFrame, 2); //going to do 2 shrinks, then 4 grows, then 2 shrinks
                binaryDistance8c(filteredFrame, distFrame, false); //now grows, so we need distance in bkg from fg, using 8-connected instead of 4-connected to balance
                expandFromDist(distFrame, filteredFrame, 4); //now 4 grows
                binaryDistance4c(filteredFrame, distFrame, true); //final 2 shrinks
                shrinkFromDist(distFrame, filteredFrame, 2);

                //Now use openCV functionality to do connected components analysis
                cv::Mat labels;
                cv::Mat stats;
                cv::Mat centroids;
                int nlabels;

                //existing openCV functionality
                nlabels = cv::connectedComponentsWithStats(filteredFrame, labels, stats, centroids);

                int desiredID = largestCenterID(labels, stats, centroids, nlabels, 0.5);
                reThresholdID(labels, filteredFrame, desiredID);

                cv::Moments moments = cv::moments(filteredFrame, false);

                double huMoments[7]; //rotation, translation, scale invariant moments
                cv::HuMoments(moments, huMoments);
                for (int i = 0; i < 7; i++) { //convert to log so moments are roughly on the same scale as each other
                    huMoments[i] = -1 * copysign(1.0, huMoments[i]) * log10(abs(huMoments[i]));
                }

                // saving the feature vector and label to csvFile
                int result = storeFeatureVectorInDB(huMoments, csvFile, database);
                if(result != 0){
                    printf("Something wennt wrong while saving to csv\n");
                    return -1;
                }
                //lastFilterSelected = '4';
                //filterOn = !filterOn;
                lastFilterSelected = 'o';
                filterOn = false;
            }
            else if (lastFilterSelected == '6'){
                int threshold = 115;
                thresholding(originalFrame, filteredFrame, threshold); //first you threshold

                cv::Mat distFrame;
                binaryDistance4c(filteredFrame, distFrame, true); //we're going to shrink first so we want distance in the foreground from the background
                shrinkFromDist(distFrame, filteredFrame, 2); //going to do 2 shrinks, then 4 grows, then 2 shrinks
                binaryDistance8c(filteredFrame, distFrame, false); //now grows, so we need distance in bkg from fg, using 8-connected instead of 4-connected to balance
                expandFromDist(distFrame, filteredFrame, 4); //now 4 grows
                binaryDistance4c(filteredFrame, distFrame, true); //final 2 shrinks
                shrinkFromDist(distFrame, filteredFrame, 2);

                //Now use openCV functionality to do connected components analysis
                cv::Mat labels;
                cv::Mat stats;
                cv::Mat centroids;
                int nlabels;

                //existing openCV functionality
                nlabels = cv::connectedComponentsWithStats(filteredFrame, labels, stats, centroids);

                int desiredID = largestCenterID(labels, stats, centroids, nlabels, 0.5);
                reThresholdID(labels, filteredFrame, desiredID);

                cv::Moments moments = cv::moments(filteredFrame, false);

                double huMoments[7]; //rotation, translation, scale invariant moments
                cv::HuMoments(moments, huMoments);
                for (int i = 0; i < 7; i++) { //convert to log so moments are roughly on the same scale as each other
                    huMoments[i] = -1 * copysign(1.0, huMoments[i]) * log10(abs(huMoments[i]));
                }
                std::string label;
                label = classifyNewImage(huMoments, database);
                if(label == "Error"){
                    printf("Got an Error and quit in Task 6\n");
                    return -1;
                }
                originalFrame.copyTo(filteredFrame);
                cv::putText(filteredFrame, //target image
                            label, //text
                            cv::Point(80, 250), //position
                            cv::FONT_HERSHEY_DUPLEX,
                            3.0, //size
                            CV_RGB(256, 256, 256), //font color
                            8); //thickness of font
            }
             else if (lastFilterSelected == '7'){
                int threshold = 115;
                int k = 5;
                thresholding(originalFrame, filteredFrame, threshold); //first you threshold

                cv::Mat distFrame;
                binaryDistance4c(filteredFrame, distFrame, true); //we're going to shrink first so we want distance in the foreground from the background
                shrinkFromDist(distFrame, filteredFrame, 2); //going to do 2 shrinks, then 4 grows, then 2 shrinks
                binaryDistance8c(filteredFrame, distFrame, false); //now grows, so we need distance in bkg from fg, using 8-connected instead of 4-connected to balance
                expandFromDist(distFrame, filteredFrame, 4); //now 4 grows
                binaryDistance4c(filteredFrame, distFrame, true); //final 2 shrinks
                shrinkFromDist(distFrame, filteredFrame, 2);

                //Now use openCV functionality to do connected components analysis
                cv::Mat labels;
                cv::Mat stats;
                cv::Mat centroids;
                int nlabels;

                //existing openCV functionality
                nlabels = cv::connectedComponentsWithStats(filteredFrame, labels, stats, centroids);

                int desiredID = largestCenterID(labels, stats, centroids, nlabels, 0.5);
                reThresholdID(labels, filteredFrame, desiredID);

                cv::Moments moments = cv::moments(filteredFrame, false);

                double huMoments[7]; //rotation, translation, scale invariant moments
                cv::HuMoments(moments, huMoments);
                for (int i = 0; i < 7; i++) { //convert to log so moments are roughly on the same scale as each other
                    huMoments[i] = -1 * copysign(1.0, huMoments[i]) * log10(abs(huMoments[i]));
                }
                std::string label;
                label = knnClassify(huMoments, database, k);
                if(label == "Error"){
                    printf("Got an Error and quit in Task 7\n");
                    return -1;
                }
                originalFrame.copyTo(filteredFrame);
                cv::putText(filteredFrame, //target image
                            label, //text
                            cv::Point(80, 250), //position
                            cv::FONT_HERSHEY_DUPLEX,
                            3.0, //size
                            CV_RGB(256, 256, 256), //font color
                            8); //thickness of font
            }
            
            originalFrame = filteredFrame;
        }
        cv::imshow("Live Video", originalFrame);
        
        // see if there is a waiting keystroke
        char key = cv::waitKey(10);
        if( key == 'q') {
            // to quit
            delete capdev;
            csvFile.close();
            cv::destroyWindow("Live Video");
            return 0;
        }
        else if (key == 's'){
            // to save a frame
            std::string filename;
            filename = currentDateTime();
            filename = filename.append(".jpeg");
            cv::imwrite(filename, originalFrame);
            printf("Screenshot saved!\n");
        }
        // get original feed in color
        else if (key == 'o'){
            filterOn = false;
            lastFilterSelected = key;
        }
        else if(key == '1'){
            // thresholding
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '2') {
            // thresholding + cleaning up
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '3') {
            // thresholding + cleaning up + CCA
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '4') {
                    // thresholding + cleaning up + CCA + feature generation
                    filterOn = !filterOn;
                    lastFilterSelected = key;
                }
        else if (key == '5'){
            // saving to database and csv
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '6'){
            // classifying the image based on nearest neighbour
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
        else if (key == '7'){
            // knn-classifying the image
            filterOn = !filterOn;
            lastFilterSelected = key;
        }
    }
    return 0;
}


// method to get current date and time so we can use it name the screenshot and save it.
const std::string currentDateTime() {
    // Current date/time based on current system
    time_t now = time(0);
    struct tm  tstruct;
    char temp[80];
    // Convert now to tm struct for local timezone
    tstruct = *localtime(&now);
    strftime(temp, sizeof(temp), "%Y-%m-%d %X", &tstruct);
    return temp;
}
