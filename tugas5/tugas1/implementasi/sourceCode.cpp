#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Fungsi untuk konversi grayscale menggunakan Lightness Method
Mat convertToGray_Lightness(const Mat& src) {
  Mat gray(src.rows, src.cols, CV_8UC1);
  for(int i = 0; i < src.rows; ++i) {
    for(int j = 0; j < src.cols; ++j) {
      Vec3b pixel = src.at<Vec3b>(i, j);
      int R = pixel[2], G = pixel[1], B = pixel[0];
      uchar lightness = (std::max({R, G, B}) + std::min({R, G, B})) / 2;
      gray.at<uchar>(i, j) = lightness;
    }
  }
  return gray;
}

// Fungsi untuk konversi grayscale menggunakan Average Method
Mat convertToGray_Average(const Mat& src) {
  Mat gray(src.rows, src.cols, CV_8UC1);
  for(int i = 0; i < src.rows; ++i) {
    for(int j = 0; j < src.cols; ++j) {
      Vec3b pixel = src.at<Vec3b>(i, j);
      int R = pixel[2], G = pixel[1], B = pixel[0];
      uchar average = (R + G + B) / 3;
      gray.at<uchar>(i, j) = average;
    }
  }
  return gray;
}

// Fungsi untuk konversi grayscale menggunakan Luminosity Method
Mat convertToGray_Luminosity(const Mat& src) {
  Mat gray(src.rows, src.cols, CV_8UC1);
  for(int i = 0; i < src.rows; ++i) {
    for(int j = 0; j < src.cols; ++j) {
      Vec3b pixel = src.at<Vec3b>(i, j);
      int R = pixel[2], G = pixel[1], B = pixel[0];
      uchar luminosity = static_cast<uchar>(0.21 * R + 0.71 * G + 0.07 * B);
      gray.at<uchar>(i, j) = luminosity;
    }
  }
  return gray;
}

int main() {
  cout << "OpenCV is working!" << endl;

  Mat img = imread("../../../images/kucing.png");
  if(img.empty()) {
    cout << "Gagal memuat gambar!" << endl;
    return -1;
  }

  // Proses konversi
  Mat gray_lightness = convertToGray_Lightness(img);
  Mat gray_average = convertToGray_Average(img);
  Mat gray_luminosity = convertToGray_Luminosity(img);

  // Tampilkan hasil
  imshow("Original", img);
  imshow("Gray - Lightness Method", gray_lightness);
  imshow("Gray - Average Method", gray_average);
  imshow("Gray - Luminosity Method", gray_luminosity);

  // Simpan hasil konversi
  imwrite("./output/gray_lightness.cpp.jpg", gray_lightness);
  imwrite("./output/gray_average.cpp.jpg", gray_average);
  imwrite("./output/gray_luminosity.cpp.jpg", gray_luminosity);
  cout << "Gambar hasil grayscale telah disimpan.\n";

  waitKey(0);
  destroyAllWindows();
  return 0;
}