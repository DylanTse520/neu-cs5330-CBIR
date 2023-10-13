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

// do histogram matching by getting rg chromaticity histograms and gradient magnitude histograms
// and compare each of the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgChromaticityMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the rg chromaticity histogram of the target image
  cv::Mat targetRGChromaticityHistogram;
  getRGChromaticityHistogram(target, targetRGChromaticityHistogram, histSize);
  // get the gradient magnitude histogram of the target image
  cv::Mat targetMagnitudeHistogram;
  getMagnitudeHistogram(target, targetMagnitudeHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the rg chromaticity histogram of the image
    cv::Mat imageRGChromaticityHistogram;
    getRGChromaticityHistogram(imageDatabase[i].second, imageRGChromaticityHistogram, histSize);
    // get the gradient magnitude histogram of the image
    cv::Mat imageMagnitudeHistogram;
    getMagnitudeHistogram(imageDatabase[i].second, imageMagnitudeHistogram, histSize);

    // calculate the rg chromaticity histogram intersection between the two feature vectors
    float rgChromaticityDistance = getHistogramDistance(targetRGChromaticityHistogram, imageRGChromaticityHistogram);
    // calculate the gradient magnitude histogram intersection between the two feature vectors
    float magnitudeDistance = getHistogramDistance(targetMagnitudeHistogram, imageMagnitudeHistogram);

    // calculate the final distance
    float distance = rgChromaticityDistance + magnitudeDistance;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting RGB histograms and gradient magnitude histograms
// and compare each of the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgbHistogramMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the RGB histogram of the target image
  cv::Mat targetRGBHistogram;
  getRGBHistogram(target, targetRGBHistogram, histSize);
  // get the gradient magnitude histogram of the target image
  cv::Mat targetMagnitudeHistogram;
  getMagnitudeHistogram(target, targetMagnitudeHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the RGB histogram of the image
    cv::Mat imageRGBHistogram;
    getRGBHistogram(imageDatabase[i].second, imageRGBHistogram, histSize);
    // get the gradient magnitude histogram of the image
    cv::Mat imageMagnitudeHistogram;
    getMagnitudeHistogram(imageDatabase[i].second, imageMagnitudeHistogram, histSize);

    // calculate the RGB histogram intersection between the two feature vectors
    float rgbHistogramDistance = getHistogramDistance(targetRGBHistogram, imageRGBHistogram);
    // calculate the gradient magnitude histogram intersection between the two feature vectors
    float magnitudeDistance = getHistogramDistance(targetMagnitudeHistogram, imageMagnitudeHistogram);

    // calculate the final distance
    float distance = rgbHistogramDistance + magnitudeDistance;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting rg chromaticity histograms and gradient orientation histograms
// and compare each of the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgChromaticityOrientationMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the rg chromaticity histogram of the target image
  cv::Mat targetRGChromaticityHistogram;
  getRGChromaticityHistogram(target, targetRGChromaticityHistogram, histSize);
  // get the gradient orientation histogram of the target image
  cv::Mat targetOrientationHistogram;
  getOrientationHistogram(target, targetOrientationHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the rg chromaticity histogram of the image
    cv::Mat imageRGChromaticityHistogram;
    getRGChromaticityHistogram(imageDatabase[i].second, imageRGChromaticityHistogram, histSize);
    // get the gradient orientation histogram of the image
    cv::Mat imageOrientationHistogram;
    getOrientationHistogram(imageDatabase[i].second, imageOrientationHistogram, histSize);

    // calculate the rg chromaticity histogram intersection between the two feature vectors
    float rgChromaticityDistance = getHistogramDistance(targetRGChromaticityHistogram, imageRGChromaticityHistogram);
    // calculate the gradient orientation histogram intersection between the two feature vectors
    float orientationDistance = getHistogramDistance(targetOrientationHistogram, imageOrientationHistogram);

    // calculate the final distance
    float distance = rgChromaticityDistance + orientationDistance;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting RGB histograms and gradient orientation histograms
// and compare each of the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgbHistogramOrientationMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the RGB histogram of the target image
  cv::Mat targetRGBHistogram;
  getRGBHistogram(target, targetRGBHistogram, histSize);
  // get the gradient orientation histogram of the target image
  cv::Mat targetOrientationHistogram;
  getOrientationHistogram(target, targetOrientationHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the RGB histogram of the image
    cv::Mat imageRGBHistogram;
    getRGBHistogram(imageDatabase[i].second, imageRGBHistogram, histSize);
    // get the gradient orientation histogram of the image
    cv::Mat imageOrientationHistogram;
    getOrientationHistogram(imageDatabase[i].second, imageOrientationHistogram, histSize);

    // calculate the RGB histogram intersection between the two feature vectors
    float rgbHistogramDistance = getHistogramDistance(targetRGBHistogram, imageRGBHistogram);
    // calculate the gradient orientation histogram intersection between the two feature vectors
    float orientationDistance = getHistogramDistance(targetOrientationHistogram, imageOrientationHistogram);

    // calculate the final distance
    float distance = rgbHistogramDistance + orientationDistance;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting rg chromaticity histograms and a 2D histogram of gradient orientation and magnitude
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgChromaticity2DGradientMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the rg chromaticity histogram of the target image
  cv::Mat targetRGChromaticityHistogram;
  getRGChromaticityHistogram(target, targetRGChromaticityHistogram, histSize);
  // get the orientation magnitude histogram of the target image
  cv::Mat targetGradientHistogram;
  getOrientationMagnitudeHistogram(target, targetGradientHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the rg chromaticity histogram of the image
    cv::Mat imageRGChromaticityHistogram;
    getRGChromaticityHistogram(imageDatabase[i].second, imageRGChromaticityHistogram, histSize);
    // get the orientation magnitude histogram of the image
    cv::Mat imageGradientHistogram;
    getOrientationMagnitudeHistogram(imageDatabase[i].second, imageGradientHistogram, histSize);

    // calculate the rg chromaticity histogram intersection between the two feature vectors
    float rgChromaticityDistance = getHistogramDistance(targetRGChromaticityHistogram, imageRGChromaticityHistogram);
    // calculate the gradient orientation histogram intersection between the two feature vectors
    float orientationDistance = getHistogramDistance(targetGradientHistogram, imageGradientHistogram);

    // calculate the final distance
    float distance = rgChromaticityDistance + orientationDistance;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting RGB histograms and a 2D histogram of gradient orientation and magnitude
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgbHistogram2DGradientMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the RGB histogram of the target image
  cv::Mat targetRGBHistogram;
  getRGBHistogram(target, targetRGBHistogram, histSize);
  // get the orientation magnitude histogram of the target image
  cv::Mat targetGradientHistogram;
  getOrientationMagnitudeHistogram(target, targetGradientHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the RGB histogram of the target image
    cv::Mat imageRGBHistogram;
    getRGBHistogram(imageDatabase[i].second, imageRGBHistogram, histSize);
    // get the orientation magnitude histogram of the image
    cv::Mat imageGradientHistogram;
    getOrientationMagnitudeHistogram(imageDatabase[i].second, imageGradientHistogram, histSize);

    // calculate the RGB histogram intersection between the two feature vectors
    float rgbHistogramDistance = getHistogramDistance(targetRGBHistogram, imageRGBHistogram);
    // calculate the gradient orientation histogram intersection between the two feature vectors
    float orientationDistance = getHistogramDistance(targetGradientHistogram, imageGradientHistogram);

    // calculate the final distance
    float distance = rgbHistogramDistance + orientationDistance;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// a customized matching method that pays special attention to the center of the image
// by specifically calculating the rgb histogram and gradient magnitude histogram of the center of the image
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// objectSize: the size of the object in the image, from the range of 1 to 3, 1 being the smallest
// return 0 if success
int findCenterMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize, int objectSize)
{
  // error checking
  if (objectSize < 1 || objectSize > 3)
  {
    printf("Error: object size must be from 1 to 3\n");
    return (-1);
  }

  // get the half center of the target image
  cv::Mat targetHalfCenter = target(cv::Rect(target.cols / 4, target.rows / 4, target.cols / 2, target.rows / 2));
  // get the quarter center of the target image
  cv::Mat targetQuarterCenter = target(cv::Rect(target.cols * 3 / 8, target.rows * 3 / 8, target.cols / 4, target.rows / 4));
  // get the eighth center of the target image
  cv::Mat targetEighthCenter = target(cv::Rect(target.cols * 7 / 16, target.rows * 7 / 16, target.cols / 8, target.rows / 8));

  // get the RGB histogram of the target image
  cv::Mat targetRGBHistogram;
  getRGBHistogram(target, targetRGBHistogram, histSize);
  // get the RGB histogram of the center half target image
  cv::Mat targetHalfCenterRGBHistogram;
  getRGBHistogram(targetHalfCenter, targetHalfCenterRGBHistogram, histSize);
  // get the gradient magnitude histogram of the center half target image
  cv::Mat targetHalfCenterMagnitudeHistogram;
  getMagnitudeHistogram(targetHalfCenter, targetHalfCenterMagnitudeHistogram, histSize);
  // get the RGB histogram of the quarter center of the target image
  cv::Mat targetQuarterCntRGBHistogram;
  getRGBHistogram(targetQuarterCenter, targetQuarterCntRGBHistogram, histSize);
  // get the gradient magnitude histogram of the quarter center of the target image
  cv::Mat targetQuarterCntMagnitudeHistogram;
  getMagnitudeHistogram(targetQuarterCenter, targetQuarterCntMagnitudeHistogram, histSize);
  // get the RGB histogram of the eighth center of the target image
  cv::Mat targetEighthCntRGBHistogram;
  getRGBHistogram(targetEighthCenter, targetEighthCntRGBHistogram, histSize);
  // get the gradient magnitude histogram of the eighth center of the target image
  cv::Mat targetEighthCntMagnitudeHistogram;
  getMagnitudeHistogram(targetEighthCenter, targetEighthCntMagnitudeHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // get the half center of the image
    cv::Mat imageHalfCenter = image(cv::Rect(image.cols / 4, image.rows / 4, image.cols / 2, image.rows / 2));
    // get the quarter center of the image
    cv::Mat imageQuarterCenter = image(cv::Rect(image.cols * 3 / 8, image.rows * 3 / 8, image.cols / 4, image.rows / 4));
    // get the eighth center of the image
    cv::Mat imageEighthCenter = image(cv::Rect(image.cols * 7 / 16, image.rows * 7 / 16, image.cols / 8, image.rows / 8));

    // get the RGB histogram of the image
    cv::Mat imageRGBHistogram;
    getRGBHistogram(imageDatabase[i].second, imageRGBHistogram, histSize);
    // get the RGB histogram of the half center of the image
    cv::Mat imageHalfCenterRGBHistogram;
    getRGBHistogram(imageHalfCenter, imageHalfCenterRGBHistogram, histSize);
    // get the gradient magnitude histogram of the half center of the image
    cv::Mat imageHalfCenterMagnitudeHistogram;
    getMagnitudeHistogram(imageHalfCenter, imageHalfCenterMagnitudeHistogram, histSize);
    // get the RGB histogram of the quarter center of the image
    cv::Mat imageQuarterCntRGBHistogram;
    getRGBHistogram(imageQuarterCenter, imageQuarterCntRGBHistogram, histSize);
    // get the RGB histogram of the eighth center of the image
    cv::Mat imageEighthCntRGBHistogram;
    getRGBHistogram(imageEighthCenter, imageEighthCntRGBHistogram, histSize);
    // get the gradient magnitude histogram of the quarter center of the image
    cv::Mat imageQuarterCntMagnitudeHistogram;
    getMagnitudeHistogram(imageQuarterCenter, imageQuarterCntMagnitudeHistogram, histSize);
    // get the gradient magnitude histogram of the eighth center of the image
    cv::Mat imageEighthCntMagnitudeHistogram;
    getMagnitudeHistogram(imageEighthCenter, imageEighthCntMagnitudeHistogram, histSize);

    // calculate the RGB histogram intersection between the two feature vectors
    float rgbHistogramDistance = getHistogramDistance(targetRGBHistogram, imageRGBHistogram);
    // calculate the half center RGB histogram intersection between the two feature vectors
    float halfCenterRGBHistogramDistance = getHistogramDistance(targetHalfCenterRGBHistogram, imageHalfCenterRGBHistogram);
    // calculate the half center gradient magnitude histogram intersection between the two feature vectors
    float halfCenterMagnitudeDistance = getHistogramDistance(targetHalfCenterMagnitudeHistogram, imageHalfCenterMagnitudeHistogram);
    // calculate the quarter center RGB histogram intersection between the two feature vectors
    float quarterCntRGBHistogramDistance = getHistogramDistance(targetQuarterCntRGBHistogram, imageQuarterCntRGBHistogram);
    // calculate the quarter center gradient magnitude histogram intersection between the two feature vectors
    float quarterCntMagnitudeDistance = getHistogramDistance(targetQuarterCntMagnitudeHistogram, imageQuarterCntMagnitudeHistogram);
    // calculate the eighth center RGB histogram intersection between the two feature vectors
    float eighthCntRGBHistogramDistance = getHistogramDistance(targetEighthCntRGBHistogram, imageEighthCntRGBHistogram);
    // calculate the eighth center gradient magnitude histogram intersection between the two feature vectors
    float eighthCntMagnitudeDistance = getHistogramDistance(targetEighthCntMagnitudeHistogram, imageEighthCntMagnitudeHistogram);

    // depending on the size of the object, the center of the image will be weighted differently
    if (objectSize == 1)
    {
      // calculate the final distance
      float distance = rgbHistogramDistance + 2.0 * halfCenterRGBHistogramDistance + 2.0 * halfCenterMagnitudeDistance + 4.0 * quarterCntRGBHistogramDistance + 4.0 * quarterCntMagnitudeDistance + 8.0 * eighthCntRGBHistogramDistance + 8.0 * eighthCntMagnitudeDistance;

      // store the filename along with the distance value
      distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
    }
    else if (objectSize == 2)
    {
      // calculate the final distance
      float distance = rgbHistogramDistance + 2.0 * halfCenterRGBHistogramDistance + 2.0 * halfCenterMagnitudeDistance + 8.0 * quarterCntRGBHistogramDistance + 8.0 * quarterCntMagnitudeDistance + 4.0 * eighthCntRGBHistogramDistance + 4.0 * eighthCntMagnitudeDistance;

      // store the filename along with the distance value
      distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
    }
    else if (objectSize == 3)
    {
      // calculate the final distance
      float distance = rgbHistogramDistance + 8.0 * halfCenterRGBHistogramDistance + 8.0 * halfCenterMagnitudeDistance + 4.0 * quarterCntRGBHistogramDistance + 4.0 * quarterCntMagnitudeDistance + 2.0 * eighthCntRGBHistogramDistance + 2.0 * eighthCntMagnitudeDistance;

      // store the filename along with the distance value
      distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
    }
  }

  return (0);
}