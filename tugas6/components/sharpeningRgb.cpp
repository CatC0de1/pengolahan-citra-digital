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
  vector<Mat> channels, blurredChannels, sharpenedChannels;
  split(imageInput, channels);  // memisahkan channel RGB

  for (int i = 0; i < 3; i++) {
    Mat blurred, sharpened;
    GaussianBlur(channels[i], blurred, Size(kernelSize, kernelSize), sigma);  // menghasilkan blur dengan gaussian utk digunakan dalam masking
    addWeighted(channels[i], 1.0 + amount, blurred, -amount, 0, sharpened);  // menambahkan kembali detail ke channel asli
    sharpenedChannels.push_back(sharpened);
  }

  Mat sharpenedImage;
  merge(sharpenedChannels, sharpenedImage);  // menggabungkan kembali channel RGB
  imshow("Sharpened Image", sharpenedImage);
}

// sharpening dengan Gaussian Blur
bool sharpening(const Mat& image) {
  imageInput = image.clone();

  namedWindow("Sharpened Image", WINDOW_AUTOSIZE);
  createTrackbar("Amount x0.1", "Sharpened Image", NULL, 50, onTrackbarSharpening);
  setTrackbarPos("Amount x0.1", "Sharpened Image", 15);

  createTrackbar("Sigma x0.1", "Sharpened Image", NULL, 50, onTrackbarSharpening);
  setTrackbarPos("Sigma x0.1", "Sharpened Image", 10);

  onTrackbarSharpening(0, 0);

  while (true) {
    int key = waitKey(50); // ESC key
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
