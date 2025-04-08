#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Fungsi untuk menampilkan bit-plane dari gambar grayscale
void showBitPlane(const Mat& input, int bit) {
  Mat bitPlane = (input & (1 << bit)) > 0;
  bitPlane *= 255;
  imshow("Bit-Plane Viewer", bitPlane);
}

// Fungsi untuk menampilkan GUI untuk memilih bit-plane
void showBitPlaneGUI(const Mat& input) {
  namedWindow("Bit-Plane Viewer", WINDOW_AUTOSIZE);
  createTrackbar("Bit (0-7)", "Bit-Plane Viewer", NULL, 7, [](int, void* userdata) {
    const Mat* grayImage = static_cast<const Mat*>(userdata);
    int bit = getTrackbarPos("Bit (0-7)", "Bit-Plane Viewer");
    showBitPlane(*grayImage, bit);
  }, (void*)&input);

  showBitPlane(input, 0);
}

// Entry Form2
bool form2(const Mat& inputImage) {
  Mat grayImage;
  if (inputImage.channels() == 3) {
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);
  } else {
    grayImage = inputImage.clone();
  }

  showBitPlaneGUI(grayImage);

  while (true) {
    int key = waitKey(30);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
