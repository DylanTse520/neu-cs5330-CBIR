/*
  Yixiang Xie
  Fall 2023
  CS 5330
*/

#include <cstring>
#include <opencv2/opencv.hpp>
#include <vector>

int getRGChromaticityHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize);
int getRGBHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize);
int getMagnitudeHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize);
int getOrientationHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize);
int getOrientationMagnitudeHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize);
float getHistogramDistance(cv::Mat const histogram1, cv::Mat const histogram2);
int display5ImagesInARow(std::vector<std::string> imagePaths);