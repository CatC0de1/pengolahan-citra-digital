#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

static Mat grayInput;

void onTrackbarSharpening(int, void*) {
  int amountSlider = getTrackbarPos("Amount x0.1", "Sharpened Image");
  int kernelSlider = getTrackbarPos("Sigma x0.1", "Sharpened Image");

  double amount = amountSlider / 10.0;
  double sigma = kernelSlider / 10.0;

  int kernelSize = 5; // Fixed size for stability
  Mat blurred, sharpened;
  GaussianBlur(grayInput, blurred, Size(kernelSize, kernelSize), sigma);
  addWeighted(grayInput, 1.0 + amount, blurred, -amount, 0, sharpened);

  imshow("Sharpened Image", sharpened);
}

bool spatialSharpening(const Mat& gray) {
  grayInput = gray.clone(); // Simpan input secara global lokal

  namedWindow("Sharpened Image", WINDOW_AUTOSIZE);
  createTrackbar("Amount x0.1", "Sharpened Image", NULL, 50, onTrackbarSharpening);
  setTrackbarPos("Amount x0.1", "Sharpened Image", 15); // Default: 1.5

  createTrackbar("Sigma x0.1", "Sharpened Image", NULL, 50, onTrackbarSharpening);
  setTrackbarPos("Sigma x0.1", "Sharpened Image", 10); // Default: 1.0

  onTrackbarSharpening(0, 0);

  while (true) {
    int key = waitKey(30);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
