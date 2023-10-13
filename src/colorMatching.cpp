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

// do histogram matching by getting rg chromaticity histograms and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the rg chromaticity histogram of the target image
  cv::Mat targetHistogram;
  getRGChromaticityHistogram(target, targetHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the rg chromaticity histogram of the image
    cv::Mat imageHistogram;
    getRGChromaticityHistogram(imageDatabase[i].second, imageHistogram, 16);

    // calculate the histogram intersection between the two feature vectors
    float distance = getHistogramDistance(targetHistogram, imageHistogram);

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do histogram matching by getting RGB histograms and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int rgbHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the RGB histogram of the target image
  cv::Mat targetHistogram;
  getRGBHistogram(target, targetHistogram, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the RGB histogram of the image
    cv::Mat imageHistogram;
    getRGBHistogram(imageDatabase[i].second, imageHistogram, histSize);

    // calculate the histogram distances
    float distance = getHistogramDistance(targetHistogram, imageHistogram);

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do multi-histogram matching by splitting the image into top and bottom halves
// and getting rg chromaticity histograms and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int topBtmRGChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // split the target image into top and bottom halves
  cv::Mat targetTop = target(cv::Rect(0, 0, target.cols, target.rows / 2));
  cv::Mat targetBtm = target(cv::Rect(0, target.rows / 2, target.cols, target.rows / 2));

  // get the rg chromaticity histogram of the top half of the target image
  cv::Mat targetHistogramTop;
  getRGChromaticityHistogram(targetTop, targetHistogramTop, histSize);
  // get the rg chromaticity histogram of the bottom half of the target image
  cv::Mat targetHistogramBtm;
  getRGChromaticityHistogram(targetBtm, targetHistogramBtm, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // split the image into top and bottom halves
    cv::Mat imageTop = image(cv::Rect(0, 0, image.cols, image.rows / 2));
    cv::Mat imageBtm = image(cv::Rect(0, image.rows / 2, image.cols, image.rows / 2));

    // get the rg chromaticity histogram of the top half of the image
    cv::Mat imageHistogramTop;
    getRGChromaticityHistogram(imageTop, imageHistogramTop, histSize);
    // get the rg chromaticity histogram of the bottom half of the image
    cv::Mat imageHistogramBtm;
    getRGChromaticityHistogram(imageBtm, imageHistogramBtm, histSize);

    // calculate the histogram distances of the two halves
    float distanceTop = getHistogramDistance(targetHistogramTop, imageHistogramTop);
    float distanceBtm = getHistogramDistance(targetHistogramBtm, imageHistogramBtm);

    // calculate the mean histogram distance
    float distance = distanceTop + distanceBtm;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do multi-histogram matching by splitting the image into top and bottom halves
// and getting RGB histograms and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int topBtmRGBHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // split the target image into top and bottom halves
  cv::Mat targetTop = target(cv::Rect(0, 0, target.cols, target.rows / 2));
  cv::Mat targetBtm = target(cv::Rect(0, target.rows / 2, target.cols, target.rows / 2));

  // get the RGB histogram of the top half of the target image
  cv::Mat targetHistogramTop;
  getRGBHistogram(targetTop, targetHistogramTop, histSize);
  // get the RGB histogram of the bottom half of the target image
  cv::Mat targetHistogramBtm;
  getRGBHistogram(targetBtm, targetHistogramBtm, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // split the image into top and bottom halves
    cv::Mat imageTop = image(cv::Rect(0, 0, image.cols, image.rows / 2));
    cv::Mat imageBtm = image(cv::Rect(0, image.rows / 2, image.cols, image.rows / 2));

    // get the RGB histogram of the top half of the image
    cv::Mat imageHistogramTop;
    getRGBHistogram(imageTop, imageHistogramTop, histSize);
    // get the RGB histogram of the bottom half of the image
    cv::Mat imageHistogramBtm;
    getRGBHistogram(imageBtm, imageHistogramBtm, histSize);

    // calculate the histogram distances of the two halves
    float distanceTop = getHistogramDistance(targetHistogramTop, imageHistogramTop);
    float distanceBtm = getHistogramDistance(targetHistogramBtm, imageHistogramBtm);

    // calculate the mean histogram distance
    float distance = distanceTop + distanceBtm;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do multi-histogram matching by getting rg chromaticity histograms
// of the top and bottom halves of the image and the center of the image
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int topBtmCntRGChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the top and bottom halves and the center of the target image
  cv::Mat targetTop = target(cv::Rect(0, 0, target.cols, target.rows / 2));
  cv::Mat targetBtm = target(cv::Rect(0, target.rows / 2, target.cols, target.rows / 2));
  cv::Mat targetCnt = target(cv::Rect(target.cols * 3 / 8, target.rows * 3 / 8, target.cols / 4, target.rows / 4));

  // get the rg chromaticity histogram of the top half of the target image
  cv::Mat targetHistogramTop;
  getRGChromaticityHistogram(targetTop, targetHistogramTop, histSize);
  // get the rg chromaticity histogram of the bottom half of the target image
  cv::Mat targetHistogramBtm;
  getRGChromaticityHistogram(targetBtm, targetHistogramBtm, histSize);
  // get the rg chromaticity histogram of the center of the target image
  cv::Mat targetHistogramCnt;
  getRGChromaticityHistogram(targetCnt, targetHistogramCnt, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // get the top and bottom halves and the center of the target image
    cv::Mat imageTop = image(cv::Rect(0, 0, image.cols, image.rows / 2));
    cv::Mat imageBtm = image(cv::Rect(0, image.rows / 2, image.cols, image.rows / 2));
    cv::Mat imageCnt = image(cv::Rect(image.cols * 3 / 8, image.rows * 3 / 8, image.cols / 4, image.rows / 4));

    // get the rg chromaticity histogram of the top half of the image
    cv::Mat imageHistogramTop;
    getRGChromaticityHistogram(imageTop, imageHistogramTop, histSize);
    // get the rg chromaticity histogram of the bottom half of the image
    cv::Mat imageHistogramBtm;
    getRGChromaticityHistogram(imageBtm, imageHistogramBtm, histSize);
    // get the rg chromaticity histogram of the center of the image
    cv::Mat imageHistogramCnt;
    getRGChromaticityHistogram(imageCnt, imageHistogramCnt, histSize);

    // calculate the histogram distances of the three sections
    float distanceTop = getHistogramDistance(targetHistogramTop, imageHistogramTop);
    float distanceBtm = getHistogramDistance(targetHistogramBtm, imageHistogramBtm);
    float distanceCnt = getHistogramDistance(targetHistogramCnt, imageHistogramCnt);

    // calculate the weighted mean histogram distance
    float distance = distanceTop + distanceBtm + 2.0 * distanceCnt;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do multi-histogram matching by getting RGB histograms
// of the top and bottom halves of the image and the center of the image
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int topBtmCntRGBHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the top and bottom halves and the center of the target image
  cv::Mat targetTop = target(cv::Rect(0, 0, target.cols, target.rows / 2));
  cv::Mat targetBtm = target(cv::Rect(0, target.rows / 2, target.cols, target.rows / 2));
  cv::Mat targetCnt = target(cv::Rect(target.cols * 3 / 8, target.rows * 3 / 8, target.cols / 4, target.rows / 4));

  // get the RGB histogram of the top half of the target image
  cv::Mat targetHistogramTop;
  getRGBHistogram(targetTop, targetHistogramTop, histSize);
  // get the RGB histogram of the bottom half of the target image
  cv::Mat targetHistogramBtm;
  getRGBHistogram(targetBtm, targetHistogramBtm, histSize);
  // get the RGB histogram of the center of the target image
  cv::Mat targetHistogramCnt;
  getRGBHistogram(targetCnt, targetHistogramCnt, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // get the top and bottom halves and the center of the target image
    cv::Mat imageTop = image(cv::Rect(0, 0, image.cols, image.rows / 2));
    cv::Mat imageBtm = image(cv::Rect(0, image.rows / 2, image.cols, image.rows / 2));
    cv::Mat imageCnt = image(cv::Rect(image.cols * 3 / 8, image.rows * 3 / 8, image.cols / 4, image.rows / 4));

    // get the RGB histogram of the top half of the image
    cv::Mat imageHistogramTop;
    getRGBHistogram(imageTop, imageHistogramTop, histSize);
    // get the RGB histogram of the bottom half of the image
    cv::Mat imageHistogramBtm;
    getRGBHistogram(imageBtm, imageHistogramBtm, histSize);
    // get the RGB histogram of the center of the image
    cv::Mat imageHistogramCnt;
    getRGBHistogram(imageCnt, imageHistogramCnt, histSize);

    // calculate the histogram distances of the three sections
    float distanceTop = getHistogramDistance(targetHistogramTop, imageHistogramTop);
    float distanceBtm = getHistogramDistance(targetHistogramBtm, imageHistogramBtm);
    float distanceCnt = getHistogramDistance(targetHistogramCnt, imageHistogramCnt);

    // calculate the weighted mean histogram distance
    float distance = distanceTop + distanceBtm + 2.0 * distanceCnt;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do multi-histogram matching by getting rg chromaticity histograms
// of the whole image and the center of the image
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int wholeCntRGChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the center of the target image
  cv::Mat targetCnt = target(cv::Rect(target.cols * 3 / 8, target.rows * 3 / 8, target.cols / 4, target.rows / 4));

  // get the rgChromaticity of the whole target image
  cv::Mat targetHistogram;
  getRGChromaticityHistogram(target, targetHistogram, histSize);
  // get the rgChromaticity of the center of the target image
  cv::Mat targetHistogramCnt;
  getRGChromaticityHistogram(targetCnt, targetHistogramCnt, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // get the center of the target image
    cv::Mat imageCnt = image(cv::Rect(image.cols * 3 / 8, image.rows * 3 / 8, image.cols / 4, image.rows / 4));

    // get the rgChromaticity of the whole image
    cv::Mat imageHistogram;
    getRGChromaticityHistogram(image, imageHistogram, histSize);
    // get the rgChromaticity of the center of the image
    cv::Mat imageHistogramCnt;
    getRGChromaticityHistogram(imageCnt, imageHistogramCnt, histSize);

    // calculate the histogram distances of the two sections
    float distanceWhole = getHistogramDistance(targetHistogram, imageHistogram);
    float distanceCnt = getHistogramDistance(targetHistogramCnt, imageHistogramCnt);

    // calculate the weighted mean histogram distance
    float distance = distanceWhole + 2.0 * distanceCnt;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}

// do multi-histogram matching by getting RGB histograms
// of the whole image and the center of the image
// and compare the histogram intersection
// target: the target image
// imageDatabase: the database of images
// distanceArr: the vector to store the distances
// histSize: the size of the histogram
// return: 0 if success
int wholeCntRGBHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize)
{
  // get the center of the target image
  cv::Mat targetCnt = target(cv::Rect(target.cols * 3 / 8, target.rows * 3 / 8, target.cols / 4, target.rows / 4));

  // get the RGB histogram of the whole target image
  cv::Mat targetHistogram;
  getRGBHistogram(target, targetHistogram, histSize);
  // get the RGB histogram of the center of the target image
  cv::Mat targetHistogramCnt;
  getRGBHistogram(targetCnt, targetHistogramCnt, histSize);

  // loop through all the images in the database
  for (int i = 0; i < imageDatabase.size(); i++)
  {
    // get the image
    cv::Mat image = imageDatabase[i].second;

    // get the center of the target image
    cv::Mat imageCnt = image(cv::Rect(image.cols * 3 / 8, image.rows * 3 / 8, image.cols / 4, image.rows / 4));

    // get the RGB histogram of the whole image
    cv::Mat imageHistogram;
    getRGBHistogram(image, imageHistogram, histSize);
    // get the RGB histogram of the center of the image
    cv::Mat imageHistogramCnt;
    getRGBHistogram(imageCnt, imageHistogramCnt, histSize);

    // calculate the histogram distances of the two sections
    float distanceWhole = getHistogramDistance(targetHistogram, imageHistogram);
    float distanceCnt = getHistogramDistance(targetHistogramCnt, imageHistogramCnt);

    // calculate the weighted mean histogram distance
    float distance = distanceWhole + 2.0 * distanceCnt;

    // store the filename along with the distance value
    distanceArr.push_back(std::make_pair(imageDatabase[i].first, distance));
  }

  return (0);
}