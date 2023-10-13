/*
  Yixiang Xie
  Fall 2023
  CS 5330
*/

#include <cstring>
#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>

int baselineMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr);

int rgChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);
int rgbHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);

int topBtmRGChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);
int topBtmRGBHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);
int topBtmCntRGChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);
int topBtmCntRGBHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);
int wholeCntRGChromaticityMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string,float>> & distanceArr, int histSize = 256);
int wholeCntRGBHistogramMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string,float>> & distanceArr, int histSize = 256);

int gradientMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> &distanceArr, int histSize = 256);
int rgChromaticityMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> & distanceArr, int histSize = 256);
int rgbHistogramMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> & distanceArr, int histSize = 256);

int gradientOrientationMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>>& distanceArr, int histSize = 256);
int rgChromaticityOrientationMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> & distanceArr, int histSize = 256);
int rgbHistogramOrientationMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string, float>> & distanceArr, int histSize = 256);

int gradientOrientationMagnitudeMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string,float>> & distanceArr, int histSize = 256);
int rgChromaticity2DGradientMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string,float>> & distanceArr, int histSize = 256);
int rgbHistogram2DGradientMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string,float>> & distanceArr, int histSize = 256);

int findCenterMatching(cv::Mat const target, std::vector<std::pair<std::string, cv::Mat>> const imageDatabase, std::vector<std::pair<std::string,float>> & distanceArr, int histSize = 256, int objectSize = 2);