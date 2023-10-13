/*
  Yixiang Xie
  Fall 2023
  CS 5330
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include "matchingMethods.hpp"
#include "util.hpp"

int main(int argc, char *argv[])
{
  // // error checking
  // if (argc < 5)
  // {
  //   printf("usage: %s <target image path> <image database directory path> <output count> <matching method>\n", argv[0]);
  //   return (-1);
  // }

  // // target image path
  // char targetPath[256];
  // // get the filename
  // strcpy(targetPath, argv[1]);

  // // read the target image
  // cv::Mat target = cv::imread(targetPath);
  // // error checking
  // if (target.data == NULL)
  // {
  //   printf("error: unable to read image %s\n", targetPath);
  //   return (-2);
  // }

  // // image database directory path
  // char dirname[256];
  // // get the directory path
  // strcpy(dirname, argv[2]);
  // // open the directory
  // DIR *dirp = opendir(dirname);
  // // error checking
  // if (dirp == NULL)
  // {
  //   printf("error: unable to open directory %s\n", dirname);
  //   exit(-3);
  // }

  // // create a vector to store the database image paths
  // std::vector<std::pair<std::string, cv::Mat>> imageDatabase;
  // // loop over all the files in the image database directory
  // struct dirent *dp;
  // while ((dp = readdir(dirp)) != NULL)
  // {
  //   // check if the file is an image
  //   if (strstr(dp->d_name, ".jpg") ||
  //       strstr(dp->d_name, ".png") ||
  //       strstr(dp->d_name, ".ppm") ||
  //       strstr(dp->d_name, ".tif"))
  //   {
  //     // build the overall filename
  //     char buffer[256];
  //     strcpy(buffer, dirname);
  //     strcat(buffer, "/");
  //     strcat(buffer, dp->d_name);

  //     // read the image
  //     cv::Mat image = cv::imread(buffer);

  //     // error checking
  //     if (image.data == NULL)
  //     {
  //       printf("error: unable to read image %s\n", buffer);
  //       return (-4);
  //     }

  //     // store the images
  //     imageDatabase.push_back(std::make_pair(std::string(buffer), image));
  //   }
  // }

  // // close the directory
  // closedir(dirp);

  // // get the matching method
  // std::string matchingMethod = argv[4];

  // // the vector to store the distances
  // std::vector<std::pair<std::string, float>> distanceArr;

  // // use the matching method to compare the target image with all the images in the database
  // if (matchingMethod == "baseline")
  // {
  //   baselineMatching(target, imageDatabase, distanceArr);
  // }
  // else if (matchingMethod == "rgChromaticity")
  // {
  //   rgChromaticityMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgbHistogram")
  // {
  //   rgbHistogramMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "topBtmRGChromaticity")
  // {
  //   topBtmRGChromaticityMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "topBtmRGBHistogram")
  // {
  //   topBtmRGBHistogramMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "topBtmCntRGChromaticity")
  // {
  //   topBtmCntRGChromaticityMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "topBtmCntRGBHistogram")
  // {
  //   topBtmCntRGBHistogramMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "wholeCntRGChromaticity")
  // {
  //   wholeCntRGChromaticityMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "wholeCntRGBHistogram")
  // {
  //   wholeCntRGBHistogramMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "magnitude")
  // {
  //   gradientMagnitudeMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgChromaticityMagnitude")
  // {
  //   rgChromaticityMagnitudeMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgbHistogramMagnitude")
  // {
  //   rgbHistogramMagnitudeMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "orientation")
  // {
  //   gradientOrientationMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgChromaticityOrientation")
  // {
  //   rgChromaticityOrientationMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgbHistogramOrientation")
  // {
  //   rgbHistogramOrientationMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "2DGradient")
  // {
  //   gradientOrientationMagnitudeMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgChromaticity2DGradient")
  // {
  //   rgChromaticity2DGradientMatching(target, imageDatabase, distanceArr, 16);
  // }
  // else if (matchingMethod == "rgbHistogram2DGradient")
  // {
  //   rgbHistogram2DGradientMatching(target, imageDatabase, distanceArr, 8);
  // }
  // else if (matchingMethod == "findCenterLarge")
  // {
  //   findCenterMatching(target, imageDatabase, distanceArr, 8, 3);
  // }
  // else if (matchingMethod == "findCenterMedium")
  // {
  //   findCenterMatching(target, imageDatabase, distanceArr, 8, 2);
  // } 
  // else if (matchingMethod == "findCenterSmall")
  // {
  //   findCenterMatching(target, imageDatabase, distanceArr, 8, 1);
  // } 
  // else
  // {
  //   printf("error: invalid matching method\n");
  //   return (-5);
  // }

  // // sort the vector of pairs by the ssd value in ascending order
  // std::sort(distanceArr.begin(), distanceArr.end(),
  //           [](std::pair<std::string, float> const &a, std::pair<std::string, float> const &b)
  //           {
  //             return a.second < b.second;
  //           });

  // // get the output number
  // int outputNumber = atoi(argv[3]);

  // // error checking
  // if (outputNumber < 1)
  // {
  //   printf("error: output number must be positive integer\n");
  //   return (-6);
  // }

  // // display the target image
  // cv::namedWindow("Target image", 0);

  // // display the image
  // cv::imshow("Target image", target);

  // // select the top N images
  // std::vector<std::string> topNImages;
  // for (int i = 1; i < outputNumber + 1; i++)
  // {
  //   topNImages.push_back(distanceArr[i].first);
  // }

  // // display the top N images
  // display5ImagesInARow(topNImages);

  // // print out top N images paths
  // for (int i = 0; i < topNImages.size(); i++)
  // {
  //   std::string name = topNImages[i].c_str();
  //   std::istringstream iss(name);
  //   std::string token;
  //   std::string lastToken;

  //   while (std::getline(iss, token, '/')) {
  //       if (!token.empty()) {
  //           lastToken = token;
  //       }
  //   }

  //   printf("%s %s\n", topNImages[i].c_str(), lastToken.c_str());
  // }

  // // wait for a key
  // cv::waitKey(0);

  printf("hello world\n");

  return (0);
}
