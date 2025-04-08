#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace cv;
using namespace std;


void showImage(const string& winName, const Mat& img) {
  imshow(winName, img);
}

// Fungsi untuk mengubah gambar ke grayscale(jika di app.cpp tidak diubah) dan biner
Mat convertToGrayBinary(const Mat& src) {
  Mat gray, binary;
  if (src.channels() == 3)
    cvtColor(src, gray, COLOR_BGR2GRAY);
  else
    gray = src.clone();

  threshold(gray, binary, 127, 255, THRESH_BINARY);
  return binary;
}

// Entry Form 4
bool form4(const Mat& img1, const Mat& img2) {
  imshow("Prepared Image 1", img1);
  imshow("Prepared Image 2", img2);

  // Konversi ke biner
  Mat bin1 = convertToGrayBinary(img1);
  Mat bin2 = convertToGrayBinary(img2);

  // Operasi logika
  Mat andImg, orImg, xorImg;
  bitwise_and(bin1, bin2, andImg);
  bitwise_or(bin1, bin2, orImg);
  bitwise_xor(bin1, bin2, xorImg);

  // Tampilkan hasil
  showImage("Logical AND", andImg);
  showImage("Logical OR", orImg);
  showImage("Logical XOR", xorImg);

  while (true) {
    int key = waitKey(30);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
