/*
  Yixiang Xie
  Fall 2023
  CS 5330
*/

#include <algorithm>
#include <cstring>
#include <opencv2/opencv.hpp>
#include <vector>
#include "util.hpp"

// get the rg chromaticity histogram of a given image
// target: the given image
// targetHistogram: the rg chromaticity histogram of the given image
// histSize: the size of the histogram
// return: 0 if success
int getRGChromaticityHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize)
{
  // error checking
  if (histSize < 1 || histSize > 256)
  {
    printf("error: histogram size should be between 1 and 256\n");
    return (-1);
  }

  // allocate the histogram as 2D single channel floating point array
  // and initialzed to zero
  targetHistogram = cv::Mat::zeros(cv::Size(histSize, histSize), CV_32FC1);

  // build the histogram
  for (int i = 0; i < target.rows; i++)
  {
    // get the ith row of the feature vectors
    const cv::Vec3b *row = target.ptr<cv::Vec3b>(i);

    for (int j = 0; j < target.cols; j++)
    {
      // get each channel
      float B = row[j][0];
      float G = row[j][1];
      float R = row[j][2];

      // compute rg standard chromaticity
      float divisor = (R + G + B);
      divisor = divisor > 0.0 ? divisor : 1.0;
      float r = R / divisor;
      float g = G / divisor;

      // compute indexes, r, g are in [0, 1]
      int rIndex = (int)(r * (histSize - 1) + 0.5); // rounds to nearest value
      int gIndex = (int)(g * (histSize - 1) + 0.5);

      // increment the histogram
      targetHistogram.at<float>(rIndex, gIndex)++;
    }
  }

  // normalize histogram by divided by the number of pixels, which makes it a probability
  targetHistogram /= (target.rows * target.cols);

  return (0);
}

// get the RGB histogram of a given image
// target: the given image
// targetHistogram: the RBG histogram of the given image
// histSize: the size of the histogram
// return: 0 if success
int getRGBHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize)
{
  // error checking
  if (histSize < 1 || histSize > 256)
  {
    printf("error: histogram size should be between 1 and 256\n");
    return (-1);
  }

  // allocate the histogram as 2D one channels floating point array
  // and initialzed to zero
  targetHistogram = cv::Mat::zeros(cv::Size(histSize * histSize * histSize, 1), CV_32FC1);

  // build the histogram
  for (int i = 0; i < target.rows; i++)
  {
    // get the ith row of the feature vectors
    const cv::Vec3b *row = target.ptr<cv::Vec3b>(i);

    for (int j = 0; j < target.cols; j++)
    {
      // get each channel
      float B = row[j][0];
      float G = row[j][1];
      float R = row[j][2];

      // compute indexes
      int bIndex = (int)(B / 255 * (histSize - 1) + 0.5); // rounds to nearest value
      int gIndex = (int)(G / 255 * (histSize - 1) + 0.5);
      int rIndex = (int)(R / 255 * (histSize - 1) + 0.5);

      // increment the histogram
      targetHistogram.at<float>(0, bIndex * histSize * histSize + gIndex * histSize + rIndex)++;
    }
  }

  // normalize histogram by divided by the number of pixels, which makes it a probability
  targetHistogram /= (target.rows * target.cols);

  return (0);
}

// calculates the horizontal Sobel gradient of an image
// target: the given image
// sobelX: the horizontal Sobel gradient of the given image
// return: 0 if success
int sobelX3x3(cv::Mat const &target, cv::Mat &sobelX)
{
  // the temporary image
  cv::Mat temp = cv::Mat::zeros(target.size(), CV_8UC1);

  // calculate temporary image
  for (int i = 1; i < target.rows - 1; i++)
  {
    // the pointer to the ith row of the temporary image
    unsigned char *tempPtr = temp.ptr<unsigned char>(i);

    // the three row pointers to the i - 1, i, i + 1 rows of the target image
    const unsigned char *targetPtrM1 = target.ptr<unsigned char>(i - 1);
    const unsigned char *targetPtr = target.ptr<unsigned char>(i);
    const unsigned char *targetPtrP1 = target.ptr<unsigned char>(i + 1);

    // multiply [1 2 1] vertical kernel with the image
    for (int j = 0; j < target.cols; j++)
    {
      tempPtr[j] = (targetPtrM1[j] + targetPtr[j] * 2 + targetPtrP1[j]) / 4;
    }
  }

  sobelX = cv::Mat::zeros(target.size(), CV_16SC1);
  for (int i = 0; i < target.rows; i++)
  {
    // the pointer to the ith row of the horizontal Sobel gradient image
    short *desPtr = sobelX.ptr<short>(i);

    // the pointer to the ith row of the temporary image
    unsigned char *tempPtr = temp.ptr<unsigned char>(i);

    // multiply [-1 0 1] horizontal kernel with the image
    for (int j = 1; j < target.cols - 1; j++)
    {
      desPtr[j] = -1 * tempPtr[j - 1] + tempPtr[j + 1];
    }
  }

  return (0);
}

// calculate the vertical Sobel gradient of an image
// target: the given image
// sobelY: the vertical Sobel gradient of the given image
// return: 0 if success
int sobelY3x3(const cv::Mat &target, cv::Mat &sobelY)
{
  // the temporary image
  cv::Mat temp = cv::Mat::zeros(target.size(), CV_16SC1);

  // calculate temporary image
  for (int i = 1; i < target.rows - 1; i++)
  {
    // the pointer to the ith row of the temporary image
    short *tempPtr = temp.ptr<short>(i);

    // the two row pointers to the i - 1, i + 1 rows of the target image
    const unsigned char *targetPtrM1 = target.ptr<unsigned char>(i - 1);
    const unsigned char *targetPtrP1 = target.ptr<unsigned char>(i + 1);

    // multiply [1 0 -1] vertical kernel with the image
    for (int j = 0; j < target.cols; j++)
    {
      tempPtr[j] = targetPtrM1[j] - targetPtrP1[j];
    }
  }

  sobelY = cv::Mat::zeros(target.size(), CV_16SC1);
  for (int i = 0; i < target.rows; i++)
  {
    // the pointer to the ith row of the vertical Sobel gradient image
    short *desPtr = sobelY.ptr<short>(i);

    // the pointer to the ith row of the temporary image
    short *tempPtr = temp.ptr<short>(i);

    // multiply [1 2 1] horizontal kernel with the image
    for (int j = 1; j < target.cols - 1; j++)
    {
      desPtr[j] = (tempPtr[j - 1] + tempPtr[j] * 2 + tempPtr[j + 1]) / 4;
    }
  }

  return (0);
}

// calculate the gradient magnitude of an image
// target: the given image
// mag: the gradient magnitude of the given image
// return: 0 if success
int magnitude(const cv::Mat &target, cv::Mat &mag)
{
  // the horizontal and the vertical Sobel gradient image
  cv::Mat sobelX, sobelY;

  // calculate the horizontal and the vertical Sobel gradient image
  sobelX3x3(target, sobelX);
  sobelY3x3(target, sobelY);

  // allocate the gradient magnitude image
  mag = cv::Mat::zeros(target.size(), CV_32FC1);

  for (int i = 0; i < target.rows; i++)
  {
    // the pointer to the ith row of the gradient magnitude image
    float *magPtr = mag.ptr<float>(i);

    // the pointer to the ith row of the horizontal and the vertical Sobel gradient image
    const short *sobelXPtr = sobelX.ptr<short>(i);
    const short *sobelYPtr = sobelY.ptr<short>(i);

    for (int j = 0; j < target.cols; j++)
    {
      magPtr[j] = sqrt(sobelXPtr[j] * sobelXPtr[j] + sobelYPtr[j] * sobelYPtr[j]);
    }
  }

  return (0);
}

// calculate the gradient orientation of an image
// target: the given image
// ori: the gradient orientation of the given image
// return: 0 if success
int orientation(const cv::Mat &target, cv::Mat &ori)
{
  // the horizontal and the vertical Sobel gradient image
  cv::Mat sobelX, sobelY;

  // calculate the horizontal and the vertical Sobel gradient image
  sobelX3x3(target, sobelX);
  sobelY3x3(target, sobelY);

  // allocate the gradient orientation image
  ori = cv::Mat::zeros(target.size(), CV_32FC1);

  for (int i = 0; i < target.rows; i++)
  {
    // the pointer to the ith row of the gradient orientation image
    float *oriPtr = ori.ptr<float>(i);

    // the pointer to the ith row of the horizontal and the vertical Sobel gradient image
    const short *sobelXPtr = sobelX.ptr<short>(i);
    const short *sobelYPtr = sobelY.ptr<short>(i);

    for (int j = 0; j < target.cols; j++)
    {
      oriPtr[j] = atan2(sobelYPtr[j], sobelXPtr[j]);
    }
  }

  return (0);
}

// calculate the gradient magnitude histogram of a given image
// target: the given image
// targetHistogram: the gradient magnitude histogram of the given image
// histSize: the size of the histogram
// return: 0 if success
int getMagnitudeHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize)
{
  // error checking
  if (histSize < 1 || histSize > 256)
  {
    printf("error: histogram size should be between 1 and 256\n");
    return (-1);
  }

  // get the gray scale image
  cv::Mat grayScale;
  cv::cvtColor(target, grayScale, cv::COLOR_BGR2GRAY);

  // calculate the gradient magnitude
  cv::Mat gradientMagnitude;
  magnitude(grayScale, gradientMagnitude);

  // allocate the histogram as 1D single channel floating point array
  // and initialzed to zero
  targetHistogram = cv::Mat::zeros(cv::Size(histSize, 1), CV_32FC1);

  // build the histogram
  for (int i = 0; i < gradientMagnitude.rows; i++)
  {
    // get the ith row of the feature vectors
    const float *row = gradientMagnitude.ptr<float>(i);

    for (int j = 0; j < gradientMagnitude.cols; j++)
    {
      // get pixel value
      float value = row[j];

      // compute index
      int index = (int)(value / 360 * (histSize - 1) + 0.5); // rounds to nearest value

      // increment the histogram
      targetHistogram.at<float>(0, index)++;
    }
  }

  // normalize histogram by divided by the number of pixels, which makes it a probability
  targetHistogram /= (target.rows * target.cols);

  return (0);
}

// calculate the gradient orientation histogram of a given image
// target: the given image
// targetHistogram: the gradient orientation histogram of the given image
// histSize: the size of the histogram
// return: 0 if success
int getOrientationHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize)
{
  // error checking
  if (histSize < 1 || histSize > 256)
  {
    printf("error: histogram size should be between 1 and 256\n");
    return (-1);
  }

  // get the gray scale image
  cv::Mat grayScale;
  cv::cvtColor(target, grayScale, cv::COLOR_BGR2GRAY);

  // calculate the gradient orientation
  cv::Mat gradientOrientation;
  orientation(grayScale, gradientOrientation);

  // allocate the histogram as 1D single channel floating point array
  // and initialzed to zero
  targetHistogram = cv::Mat::zeros(cv::Size(histSize, 1), CV_32FC1);

  // build the histogram
  for (int i = 0; i < gradientOrientation.rows; i++)
  {
    // get the ith row of the feature vectors
    const float *row = gradientOrientation.ptr<float>(i);

    for (int j = 0; j < gradientOrientation.cols; j++)
    {
      // get pixel value
      float value = row[j];

      // compute index
      int index = (int)(value / 360 * (histSize - 1) + 0.5); // rounds to nearest value

      // increment the histogram
      targetHistogram.at<float>(0, index)++;
    }
  }

  // normalize histogram by divided by the number of pixels, which makes it a probability
  targetHistogram /= (target.rows * target.cols);

  return (0);
}

// calculate the gradient orientation magnitude histogram of a given image
// target: the given image
// targetHistogram: the gradient orientation magnitude histogram of the given image
// histSize: the size of the histogram
// return: 0 if success
int getOrientationMagnitudeHistogram(cv::Mat const target, cv::Mat &targetHistogram, int histSize)
{
  // error checking
  if (histSize < 1 || histSize > 256)
  {
    printf("error: histogram size should be between 1 and 256\n");
    return (-1);
  }

  // get the gray scale image
  cv::Mat grayScale;
  cv::cvtColor(target, grayScale, cv::COLOR_BGR2GRAY);

  // calculate the gradient magnitude
  cv::Mat gradientMagnitude;
  magnitude(grayScale, gradientMagnitude);
  // calculate the gradient orientation
  cv::Mat gradientOrientation;
  orientation(grayScale, gradientOrientation);

  // allocate the histogram as 2D single channel floating point array
  // and initialzed to zero
  targetHistogram = cv::Mat::zeros(cv::Size(histSize, histSize), CV_32FC1);

  // build the histogram
  for (int i = 0; i < target.rows; i++)
  {
    // get the ith row of the feature vectors
    const float *rowMagnitude = gradientMagnitude.ptr<float>(i);
    const float *rowOrientation = gradientOrientation.ptr<float>(i);

    for (int j = 0; j < target.cols; j++)
    {
      // get magnitude value
      float mag = rowMagnitude[j];

      // compute index
      int magIndex = (int)(mag / 360 * (histSize - 1) + 0.5); // rounds to nearest value

      // get orientation value
      float ori = rowOrientation[j] + CV_PI;

      // compute indexes
      int oriIndex = (int)(ori / CV_2PI * (histSize - 1) + 0.5); // rounds to nearest value

      // compute orientation index
      // increment the histogram
      targetHistogram.at<float>(magIndex, oriIndex)++;
    }
  }

  // normalize histogram by divided by the number of pixels, which makes it a probability
  targetHistogram /= (target.rows * target.cols);

  return (0);
}

// calculate the histogram distance between two histograms using histogram intersection
// histogram1: the first histogram
// histogram2: the second histogram
// return: the histogram distance value, between 0 and 1
float getHistogramDistance(cv::Mat const histogram1, cv::Mat const histogram2)
{
  // error checking
  if (histogram1.rows != histogram2.rows || histogram1.cols != histogram2.cols)
  {
    printf("error: histograms have different dimensions\n");
    printf("histogram1: %d x %d\n", histogram1.rows, histogram1.cols);
    printf("histogram2: %d x %d\n", histogram2.rows, histogram2.cols);
    return (-1);
  }

  // calculate the intersection
  float intersection = 0.0;
  for (int i = 0; i < histogram1.rows; i++)
  {
    // get the ith row of the feature vectors
    const float *row1 = histogram1.ptr<float>(i);
    const float *row2 = histogram2.ptr<float>(i);

    for (int j = 0; j < histogram1.cols; j++)
    {
      intersection += std::min(row1[j], row2[j]);
    }
  }

  // return the histogram distance, which is 1 - intersection
  return 1.0 - intersection;
}

// display the given images 5 in a row
// imageArr: the given images
// return: 0 if success
int display5ImagesInARow(std::vector<std::string> imagePaths)
{
  // the vector to store the images
  std::vector<cv::Mat> imageVector;

  // read the images
  for (const auto &path : imagePaths)
  {
    // read the image
    cv::Mat image = cv::imread(path);

    // error checking
    if (image.data == NULL)
    {
      printf("error: unable to read image %s\n", path.c_str());
      return (-1);
    }

    // store the image
    imageVector.push_back(image);
  }

  // calculate the number of rows with 5 images in each row
  int numRows = (imageVector.size() + 4) / 5;
  // calculate the number of columns, 5 columns maximum
  int numCols = std::min((int)imageVector.size(), 5);

  // calculate canvas width, which is 2/5 of first image width times the number of columns
  int canvasWidth = imageVector[0].cols / 5 * 2 * numCols;
  // calculate canvas height, which is 2/5 of first image height times the number of rows
  int canvasHeight = imageVector[0].rows / 5 * 2 * numRows;
  // create the canvas
  cv::Mat canvas(canvasHeight, canvasWidth, imageVector[0].type(), cv::Scalar(255, 255, 255));

  // loop over all the images
  for (int i = 0; i < imageVector.size(); i++)
  {
    // calculate the row index
    int row = i / 5;
    // calculate the column index
    int col = i % 5;

    // the resized image
    cv::Mat resizedImage;
    // resize the image
    cv::resize(imageVector[i], resizedImage, cv::Size(canvasWidth / numCols, canvasHeight / numRows));
    // calculate the ROI
    cv::Rect roi(col * canvasWidth / numCols, row * canvasHeight / numRows, canvasWidth / numCols, canvasHeight / numRows);
    // copy the image to the ROI
    resizedImage.copyTo(canvas(roi));
  }

  // create a window
  char windowName[256];
  snprintf(windowName, sizeof(windowName), "Top %d images", (int)imageVector.size());
  cv::namedWindow(windowName, 1);

  // display the image
  cv::imshow(windowName, canvas);

  return (0);
}