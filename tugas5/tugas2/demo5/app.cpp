#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool histogramEqualization(const Mat& img);
bool spatialSharpening(const Mat& img);
bool spatialSmoothing(const Mat& img);

// fungsi untuk mengubah citra ke grayscale
Mat convertToGray(const Mat& img) {
  Mat gray;
  cvtColor(img, gray, COLOR_BGR2GRAY);
  return gray;
}

// fungsi untuk memuat gambar
Mat loadImage() {
  string path;
  cout << "Masukkan nama file gambar (contoh: kucing.png): ";
  cin >> path;
  // string fullpath = "../../../images/" + path;
  Mat img = imread(path);
  if (img.empty()) {
    cerr << "Gagal memuat gambar: " << path << endl;
    return Mat();
  }

  imshow("Original Image", img);
  cout << "Tekan ESC pada gambar untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela gambar untuk melihat gambar yang lain.\n";
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
compile: g++ app.cpp components/*.cpp -o Demo5 `pkg-config --cflags --libs opencv4`
execute: ./Demo5
*/