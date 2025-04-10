#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static Mat imageInput;

// fungsi untuk menangani trackbar
void onTrackbarSharpening(int, void*) {
  int amountSlider = getTrackbarPos("Amount x0.1", "Sharpened Image");
  int kernelSlider = getTrackbarPos("Sigma x0.1", "Sharpened Image");

  double amount = amountSlider / 10.0;
  double sigma = kernelSlider / 10.0;

  int kernelSize = 5;
  Mat blurred, sharpened;
  GaussianBlur(imageInput, blurred, Size(kernelSize, kernelSize), sigma);
  addWeighted(imageInput, 1.0 + amount, blurred, -amount, 0, sharpened);

  imshow("Sharpened Image", sharpened);
}

// spatialSharpening dengan Gaussian Blur
bool spatialSharpening(const Mat& image) {
  imshow("Original Image", image);

  imageInput = image.clone();

  namedWindow("Sharpened Image", WINDOW_AUTOSIZE);
  createTrackbar("Amount x0.1", "Sharpened Image", NULL, 50, onTrackbarSharpening);
  setTrackbarPos("Amount x0.1", "Sharpened Image", 15);

  createTrackbar("Sigma x0.1", "Sharpened Image", NULL, 50, onTrackbarSharpening);
  setTrackbarPos("Sigma x0.1", "Sharpened Image", 10);

  onTrackbarSharpening(0, 0);

  while (true) {
    int key = waitKey(50);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
