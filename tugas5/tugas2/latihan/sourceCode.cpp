#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
  uchar data[5][4] = {
    {29, 10, 12, 13},
    {34, 12, 13, 13},
    {31, 10, 11, 12},
    {30, 11, 14, 14},
    {31, 12, 12, 11}
  };

  Mat input(5, 4, CV_8UC1, data); // membuat citra 5x4 8-bit single channel

  // Copy input ke bentuk Mat baru (agar tidak share memory)
  Mat img = input.clone();

  // Filter lowpass (blur biasa)
  Mat blurred;
  blur(img, blurred, Size(3, 3)); // kernel 3x3

  // Print hasil
  cout << "Input Matrix:\n" << img << endl;
  cout << "\nFiltered (Lowpass - blur 3x3) Matrix:\n" << blurred << endl;

  return 0;
}

/*
msys2 mingw64 :
g++ sourceCode.cpp -o sourceCode pkg-config --cflags --libs opencv4
./sourceCode
*/