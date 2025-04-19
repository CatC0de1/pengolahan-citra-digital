#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static Mat imageInput;

// fungsi untuk menangani trackbar
void onTrackbarSmoothing(int, void*) {
  int kernelSlider = getTrackbarPos("Kernel Size", "Smoothed Image");
  int sigmaSlider = getTrackbarPos("Sigma x0.1", "Smoothed Image");

  int kernelSize = kernelSlider * 2 + 1;
  double sigma = sigmaSlider / 10.0;

  if (kernelSize < 1) kernelSize = 1;

  vector<Mat> channels, smoothedChannels;
  split(imageInput, channels);  // memisahkan channel RGB

  for (int i = 0; i < 3; i++) {
    Mat smoothed;
    GaussianBlur(channels[i], smoothed, Size(kernelSize, kernelSize), sigma);  // menghasilkan blur dengan gaussian
    smoothedChannels.push_back(smoothed);
  }

  Mat smoothedImage;
  merge(smoothedChannels, smoothedImage);  // menggabungkan kembali channel RGB
  imshow("Smoothed Image", smoothedImage);
}

// smoothing dengan Gaussian Blur
bool smoothing(const Mat& image) {
  imageInput = image.clone();

  namedWindow("Smoothed Image", WINDOW_AUTOSIZE);
  createTrackbar("Kernel Size", "Smoothed Image", NULL, 10, onTrackbarSmoothing);
  setTrackbarPos("Kernel Size", "Smoothed Image", 2);

  createTrackbar("Sigma x0.1", "Smoothed Image", NULL, 50, onTrackbarSmoothing);
  setTrackbarPos("Sigma x0.1", "Smoothed Image", 10);

  onTrackbarSmoothing(0, 0);

  while (true) {
    int key = waitKey(50); // ESC key
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
