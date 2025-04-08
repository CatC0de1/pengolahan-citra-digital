#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static Mat grayInputSmooth;

void onTrackbarSmoothing(int, void*) {
  int kernelSlider = getTrackbarPos("Kernel Size", "Smoothed Image");
  int sigmaSlider = getTrackbarPos("Sigma x0.1", "Smoothed Image");

  int kernelSize = kernelSlider * 2 + 1; // always odd
  double sigma = sigmaSlider / 10.0;

  if (kernelSize < 1) kernelSize = 1;
  Mat smoothed;
  GaussianBlur(grayInputSmooth, smoothed, Size(kernelSize, kernelSize), sigma);

  imshow("Smoothed Image", smoothed);
}

bool spatialSmoothing(const Mat& gray) {
  grayInputSmooth = gray.clone();

  namedWindow("Smoothed Image", WINDOW_AUTOSIZE);
  createTrackbar("Kernel Size", "Smoothed Image", NULL, 10, onTrackbarSmoothing);
  setTrackbarPos("Kernel Size", "Smoothed Image", 2); // Default: 5

  createTrackbar("Sigma x0.1", "Smoothed Image", NULL, 50, onTrackbarSmoothing);
  setTrackbarPos("Sigma x0.1", "Smoothed Image", 10); // Default: 1.0

  onTrackbarSmoothing(0, 0);

  while (true) {
    int key = waitKey(30);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
