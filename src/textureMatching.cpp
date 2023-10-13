/*
  Yixiang Xie
  Fall 2023
  CS 5330
*/

#include <cstdio>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <vector>
#include "matchingMethods.hpp"
#include "util.hpp"

// do histogram matching by getting gradient magnitude histograms and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int gradientMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the magnitude histogram of the target image
  cv::Mat targetHistogram;
  getMagnitudeHistogram(target, targetHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the magnitude histogram of the image
    cv::Mat imageHistogram;
    getMagnitudeHistogram(imageDatabase[i].second, imageHistogram, histSize);

    // calculate the histogram intersection between the two feature vectors
    float distance = getHistogramDistance(targetHistogram, imageHistogram);

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting orientation histograms and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int gradientOrientationMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> & distanceArr, int histSize)
{
  // get the orientation histogram of the target image
  cv::Mat targetHistogram;
  getOrientationHistogram(target, targetHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the orientation histogram of the image
    cv::Mat imageHistogram;
    getOrientationHistogram(imageDatabase[i].second, imageHistogram, histSize);

    // calculate the histogram intersection between the two feature vectors
    float distance = getHistogramDistance(targetHistogram, imageHistogram);

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting a 2D histogram of gradient orientation and magnitude and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int gradientOrientationMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> & distanceArr, int histSize)
{
  // get the orientation magnitude histogram of the target image
  cv::Mat targetHistogram;
  getOrientationMagnitudeHistogram(target, targetHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the orientation magnitude histogram of the image
    cv::Mat imageHistogram;
    getOrientationMagnitudeHistogram(imageDatabase[i].second, imageHistogram, histSize);

    // calculate the histogram intersection between the two feature vectors
    float distance = getHistogramDistance(targetHistogram, imageHistogram);

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}