#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// fungsi untuk memuat gambar
Mat loadImage() {
  string path;
  cout << "Masukkan nama file gambar(contoh: ./kucing.png): ";
  cin >> path;
  // string fullPath = "../../../images/" + path;
  Mat img = imread(path);
  if (img.empty()) {
    cerr << "Gagal memuat gambar: " << path << endl;
    return Mat();
  }

  imshow("Original Image", img);

  return img;
}

// lightness method
Mat convertToGray_Lightness(const Mat& src) {
  Mat gray(src.rows, src.cols, CV_8UC1);
  for(int i = 0; i < src.rows; ++i) {
    for(int j = 0; j < src.cols; ++j) {
      Vec3b pixel = src.at<Vec3b>(i, j);
      int R = pixel[2], G = pixel[1], B = pixel[0];  // nilai pixel RGB diambil dari gambar dengan format BGR
      uchar lightness = (max({R, G, B}) + min({R, G, B})) / 2;  // mencari nilai max dan min dari RGB lalu menerapkan rumus lightness
      gray.at<uchar>(i, j) = lightness;
    }
  }

  imshow("Gray - Lightness Method", gray);
  imwrite("./output/gray_lightness.cpp.jpg", gray);

  return gray;
}

// average method
Mat convertToGray_Average(const Mat& src) {
  Mat gray(src.rows, src.cols, CV_8UC1);
  for(int i = 0; i < src.rows; ++i) {
    for(int j = 0; j < src.cols; ++j) {
      Vec3b pixel = src.at<Vec3b>(i, j);
      int R = pixel[2], G = pixel[1], B = pixel[0];
      uchar average = (R + G + B) / 3;  // mencari rata-rata dari RGB (rumus average)
      gray.at<uchar>(i, j) = average;
    }
  }

  imshow("Gray - Average Method", gray);
  imwrite("./output/gray_average.cpp.jpg", gray);

  return gray;
}

// luminosity method
Mat convertToGray_Luminosity(const Mat& src) {
  Mat gray(src.rows, src.cols, CV_8UC1);
  for(int i = 0; i < src.rows; ++i) {
    for(int j = 0; j < src.cols; ++j) {
      Vec3b pixel = src.at<Vec3b>(i, j);
      int R = pixel[2], G = pixel[1], B = pixel[0];
      uchar luminosity = static_cast<uchar>(0.21 * R + 0.71 * G + 0.07 * B);  // menghitung luminosity dengan rumus 0.21R + 0.71G + 0.07B (sesuai dengan persepsi manusia)
      gray.at<uchar>(i, j) = luminosity;
    }
  }

  imshow("Gray - Luminosity Method", gray);
  imwrite("./output/gray_luminosity.cpp.jpg", gray);

  return gray;
}

int main() {
  cout << "\nOpenCV is working!\n" << endl;

  Mat img = loadImage();

  convertToGray_Lightness(img);
  convertToGray_Average(img);
  convertToGray_Luminosity(img);

  cout << "Gambar hasil grayscale telah disimpan.\n";
  cout << "Tekan ESC pada gambar untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela gambar untuk melihat gambar yang lain.\n";

  while (true) {
    int key = waitKey(50);
    if (key == 27) {
      cout << "Keluar dari program.\n";
      destroyAllWindows();
      return 0;
    }
  }
}

/*
msys2 mingw64 :
g++ sourceCode.cpp -o LatihanImplementasi `pkg-config --cflags --libs opencv4`
./LatihanImplementasi
*/