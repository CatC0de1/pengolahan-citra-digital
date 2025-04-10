#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// bit plance slicing
void showBitPlane(const Mat& input, int bit) {
  Mat bitPlane = (input & (1 << bit)) > 0;  // ambil bit-plane ke-n
  bitPlane *= 255;  // mengubah nilai boolean ke 0 atau 255
  imshow("Bit-Plane Viewer", bitPlane);
}

// fungsi untuk menampilkan trackbar bit-plane
void showBitPlaneGUI(const Mat& input) {
  namedWindow("Bit-Plane Viewer", WINDOW_AUTOSIZE);
  createTrackbar("Bit (0-7)", "Bit-Plane Viewer", NULL, 7, [](int, void* userdata) {
    const Mat* grayImage = static_cast<const Mat*>(userdata);
    int bit = getTrackbarPos("Bit (0-7)", "Bit-Plane Viewer");
    showBitPlane(*grayImage, bit);
  }, (void*)&input);

  showBitPlane(input, 0);
}

// entry form2
bool form2(const Mat& inputImage) {
  Mat grayImage;
  if (inputImage.channels() == 3) {
    cvtColor(inputImage, grayImage, COLOR_BGR2GRAY);
  } else {
    grayImage = inputImage.clone();
  }

  showBitPlaneGUI(grayImage);

  while (true) {
    int key = waitKey(50);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
