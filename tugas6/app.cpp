#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "components/header.hpp"

using namespace cv;
using namespace std;

// fungsi untuk memuat gambar
Mat loadImage() {
  string path;
  cout << "Masukkan nama file gambar (contoh: ./kucing.png): ";
  cin >> path;
  Mat image = imread(path);
  if (image.empty()) {
    cerr << "Gagal memuat gambar: " << path << endl;
    return Mat();
  }

  imshow("Original Image", image);
  
  cout << "Tekan ESC pada gambar untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela gambar untuk melihat gambar yang lain.\n";
  return image;
}

int main() {
  SetDllDirectoryA("libs");

  int pilihan;
  while (true) {
    cout << "\n\n=== Menu Form Pengolahan Citra Digital (Demo Pertemuan 6) ===\n";
    cout << "1. Konversi Model Warna\n";
    cout << "2. Sharpening RGB\n";
    cout << "3. Smoothing RGB\n";
    cout << "0. Keluar\n";
    cout << "Pilihanmu: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
      int subPilihan;
      while (true) {
        cout << "\n\n=== Menu Konversi Model Warna ===\n";
        cout << "1. RGB ke CMY\n";
        cout << "2. RGB ke CMYK\n";
        cout << "3. RGB ke HSI\n";
        cout << "4. RGB ke YUV\n";
        cout << "5. RGB ke YCbCr\n";
        cout << "6. Kembali ke menu utama\n";
        cout << "Pilihanmu: ";
        cin >> subPilihan;
        cin.ignore();
        if (subPilihan < 6 && subPilihan > 0) {
          Mat image = loadImage();
          if (!image.empty()) convert(image, subPilihan);
        } else if (subPilihan == 6) {
          break; 
        } else {
          cout << "Pilihan tidak valid!\n";
        }
      }
    } else if (pilihan == 2) {
      Mat image = loadImage();
      if (!image.empty()) sharpening(image);
    } else if (pilihan == 3) {
      Mat image = loadImage();
      if (!image.empty()) smoothing(image);
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
compile via MSYS2 MinGW64:
g++ app.cpp components/*.cpp -o Demo6 `pkg-config --cflags --libs opencv4`

execute via MSYS2 MinGW64:
./Demo6

deploy dinamyc linking via MSYS2 MinGW64:

mkdir -p libs

for dll in $(ldd Demo6 | grep "=>" | awk '{print $3}'); do
  cp "$dll" libs/
done
*/