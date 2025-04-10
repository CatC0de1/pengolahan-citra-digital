#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

bool form1(const Mat& img);
bool form2(const Mat& img);
bool form3(const Mat& img1, const Mat& img2);
bool form4(const Mat& img1, const Mat& img2);

// fungsi untuk mengubah citra ke grayscale
Mat convertToGray(const Mat& img) {
  Mat gray;
  cvtColor(img, gray, COLOR_BGR2GRAY);
  return gray;
}

// fungsi crop center sesuai ukuran minimum
Mat cropCenter(const Mat& img, Size targetSize) {
  int x = (img.cols - targetSize.width) / 2;
  int y = (img.rows - targetSize.height) / 2;
  return img(Rect(x, y, targetSize.width, targetSize.height)).clone();
}

// fungsi penyesuaian dua gambar agar ukuran dan format sama (grayscale)
pair<Mat, Mat> prepareTwoImages(Mat img1, Mat img2) {
  img1 = convertToGray(img1);
  img2 = convertToGray(img2);

  Size minSize(min(img1.cols, img2.cols), min(img1.rows, img2.rows));
  if (img1.size() != minSize) img1 = cropCenter(img1, minSize);
  if (img2.size() != minSize) img2 = cropCenter(img2, minSize);

  return {img1, img2};
}

// fungsi untuk memuat 1 gambar
Mat loadSingleImage() {
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
  cout << "Tekan ESC pada gambar untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela gambar untuk melihat gambar yang lain.\n";
  return img;
}

// fungsi untuk memuat 2 gambar
pair<Mat, Mat> loadTwoImages() {
  string path1, path2;
  cout << "Masukkan file gambar ke-1 (contoh: ./kucing1.png): ";
  cin >> path1;
  cout << "Masukkan file gambar ke-2 (contoh: ./kucing2.png): ";
  cin >> path2;

  // string fullPath1 = "../../../images/" + path1;
  // string fullpath2 = "../../../images/" + path2;
  Mat img1 = imread(path1);
  Mat img2 = imread(path2);

  if (img1.empty() || img2.empty()) {
    cerr << "Gagal memuat gambar: " << path1 << " atau " << path2 << endl;
    return {Mat(), Mat()};
  }

  imshow("Original Image 1", img1);
  imshow("Original Image 2", img2);
  cout << "Tekan ESC pada gambar untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela gambar untuk melihat gambar yang lain.\n";
  return {img1, img2};
}

int main() {
  int pilihan;
  while (true) {
    cout << "\n=== Menu Form Pengolahan Citra Digital (Demo Pertemuan 4) ===\n";
    cout << "1. Form 1 - Transformasi Piksel\n";
    cout << "2. Form 2 - Bit-Plane Slicing\n";
    cout << "3. Form 3 - Operasi Aritmatika (Subtraction)\n";
    cout << "4. Form 4 - Operasi Logika (AND, OR, XOR)\n";
    cout << "0. Keluar\n";
    cout << "Pilihanmu: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
      Mat img = loadSingleImage();
      if (!img.empty()) { // Ensure the image is valid
        Mat gray = convertToGray(img);
        form1(gray);
      } else {
        cout << "Gambar tidak valid. Kembali ke menu.\n";
      }
    } else if (pilihan == 2) {
      Mat img = loadSingleImage();
      if (!img.empty()) form2(img);
    } else if (pilihan == 3) {
      auto [img1, img2] = loadTwoImages();
      if (!img1.empty() && !img2.empty()) {
        auto [prepared1, prepared2] = prepareTwoImages(img1, img2);
        form3(prepared1, prepared2);
      }
    } else if (pilihan == 4) {
      auto [img1, img2] = loadTwoImages();
      if (!img1.empty() && !img2.empty()) {
        auto [prepared1, prepared2] = prepareTwoImages(img1, img2);
        form4(prepared1, prepared2);
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
compile: g++ app.cpp components/*.cpp -o Demo4 `pkg-config --cflags --libs opencv4`
execute: ./Demo4.exe
*/