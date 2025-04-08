#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
bool histogramEqualization(const Mat& img);
bool spatialSharpening(const Mat& img);
bool spatialSmoothing(const Mat& img);


Mat convertToGray(const Mat& img) {
  Mat gray;
  cvtColor(img, gray, COLOR_BGR2GRAY);
  imshow("Grayscale Image", gray);
  return gray;
}

Mat loadImage() {
  string path;
  cout << "Masukkan nama file gambar (contoh: kucing.png): ";
  cin >> path;
  string fullpath = "../../../images/" + path;
  Mat img = imread(fullpath);
  if (img.empty()) {
    cerr << "Gagal memuat gambar: " << fullpath << endl;
    return Mat();
  }

  imshow("Original Image", img);
  cout << "Tekan ESC pada gambar untuk menutup dan kembali ke menu.\n";
  return img;
}

int main() {
  int pilihan;
  while (true) {
    cout << "\n=== Menu Pengolahan Citra Digital (Demo Pertemuan 5) ===\n";
    cout << "1. Histogram Equalization\n";
    cout << "2. Spatial Sharpening\n";
    cout << "3. Spatial Smoothing\n";
    cout << "0. Keluar\n";
    cout << "Pilihanmu: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
      Mat img = loadImage();
      if (!img.empty()) {
        Mat gray = convertToGray(img);
        histogramEqualization(gray);
      }
    } else if (pilihan == 2) {
      Mat img = loadImage();
      if (!img.empty()) {
        Mat gray = convertToGray(img);
        spatialSharpening(gray);
      }
    } else if (pilihan == 3) {
      Mat img = loadImage();
      if (!img.empty()) {
        Mat gray = convertToGray(img);
        spatialSmoothing(gray);
      }
    } else if (pilihan == 0) {
      cout << "Keluar dari program.\n";
      break;
    } else {
      cout << "Pilihan tidak valid!\n";
    }
  }

  destroyAllWindows();
  return 0;
}

/*
// Compile and exceute dengan MSYS2 MinGW64
compile: g++ app.cpp components/*.cpp -o app `pkg-config --cflags --libs opencv4`
execute: ./app
*/