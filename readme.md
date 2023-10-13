# Project 2: Content-based Image Retrieval
This is Project 2: Content-based Image Retrieval by Yixiang Xie for CS5330 Pattern Recognition & Computer Vision.

The code is written in C++ with OpenCV4 on Visual Studio Code on macOS Sonoma 14.0 and compiled with a CMakeLists.txt file.

# Run the code
In order to run the code, use command line to run the bash script by ```./run.sh```. To try different configurations, change ```./run.sh``` in the format of ```./matching <target image> <image database path> <number of matching results> <method> ```. The methods can be baseline, rgChromaticity, rgbHistogram, topBtmRGChromaticity, topBtmRGBHistogram, topBtmCntRGChromaticity, topBtmCntRGBHistogram, wholeCntRGChromaticity, wholeCntRGBHistogram, magnitude, rgChromaticityMagnitude, rgbHistogramMagnitude, orientation, rgChromaticityOrientation, rgbHistogramOrientation, 2DGradient, rgChromaticity2DGradient, rgbHistogram2DGradient, findCenterLarge, findCenterMedium and findCenterSmall.

# Extensions
For extensions, I explored and compared different color histogram matching methods, different multi-color-histogram matching methods, different texture matching methods, different combinations of texture and color matching methods, and several object finds methods. Set ```<method>``` to rgbHistogram, topBtmRGChromaticity, topBtmCntRGChromaticity, topBtmCntRGBHistogram, wholeCntRGChromaticity, wholeCntRGBHistogram, magnitude, rgChromaticityMagnitude, orientation, rgChromaticityOrientation, rgbHistogramOrientation, 2DGradient, rgChromaticity2DGradient, rgbHistogram2DGradient, findCenterLarge and findCenterMedium to test these extensions. 

# Travel days used
3 travel days