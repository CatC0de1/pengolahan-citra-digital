#ifndef CONVERT_H
#define CONVERT_H

#include <opencv2/opencv.hpp>

bool convert(const cv::Mat& image, int pilihan);
bool sharpening(const cv::Mat& image);
bool smoothing(const cv::Mat& image);

#endif