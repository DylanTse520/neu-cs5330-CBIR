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

// get the center 9x9 square of a given image
// target: the given image
// featureVector: the center 9x9 square of the given image
// return: 0 if success
int getCenter9x9Square(cv::Mat const target, cv::Mat &targetFeatureVector)
{
  // error checking
  if (target.rows < 9 || target.cols < 9)
  {
    printf("error: image is too small\n");
    return (-1);
  }

  // extract the feature vector of the target image
  // get the dimension of the target image
  int targetRows = target.rows;
  int targetCols = target.cols;
  // calculate the center of the target image
  int targetCenterRow = targetRows / 2;
  int targetCenterCol = targetCols / 2;
  // get the center 9x9 square of the target image
  targetFeatureVector = target(cv::Rect(targetCenterCol - 4, targetCenterRow - 4, 9, 9));

  return (0);
}

// calculate sum-of-squared-differences between two feature vectors
// featureVector1: the first feature vector
// featureVector2: the second feature vector
// return: the sum-of-squared-differences between the two feature vectors
float sumOfSquaredDifferences(cv::Mat const featureVector1, cv::Mat const featureVector2)
{
  // error checking
  if (featureVector1.rows != featureVector2.rows || featureVector1.cols != featureVector2.cols)
  {
    printf("error: feature vectors have different dimensions\n");
    return (-1);
  }

  // calculate the sum-of-squared-differences for each pixel at three channels
  float ssd = 0.0;
  for (int i = 0; i < featureVector1.rows; i++)
  {
    // get the ith row of the feature vectors
    const cv::Vec3b *row1 = featureVector1.ptr<cv::Vec3b>(i);
    const cv::Vec3b *row2 = featureVector2.ptr<cv::Vec3b>(i);

    for (int j = 0; j < featureVector1.cols; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        float diff = row1[j][k] - row2[j][k];
        ssd += diff * diff;
      }
    }
  }

  return (ssd);
}

// do baseline matching by getting the center 9x9 square and compare the sum-of-squared-differences
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// return: 0 if success
int baselineMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr)
{
  // get the center 9x9 square of the target image
  cv::Mat targetFeatureVector;
  getCenter9x9Square(target, targetFeatureVector);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the center 9x9 square of the image
    cv::Mat imageFeatureVector;
    getCenter9x9Square(imageDatabase[i].second, imageFeatureVector);

    // calculate the sum-of-squared-differences between the two feature vectors
    float ssd = sumOfSquaredDifferences(targetFeatureVector, imageFeatureVector);

    // store the filename along with the ssd value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, ssd));
  }

  return (0);
}
