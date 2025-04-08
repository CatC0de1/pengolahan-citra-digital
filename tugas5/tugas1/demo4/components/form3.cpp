#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Menampilkan hasil operasi subtraction
void showSubtraction(const Mat& img1, const Mat& img2) {
  Mat result;
  absdiff(img1, img2, result); // Perbedaan mutlak
  imshow("Hasil Subtraction", result);
}

// Entry Form 3
bool form3(const Mat& img1, const Mat& img2) {
  if (img1.empty() || img2.empty()) {
    cerr << "Salah satu gambar kosong!" << endl;
    return false;
  }

  imshow("Prepared Image 1", img1);
  imshow("Prepared Image 2", img2);

  showSubtraction(img1, img2);

  while (true) {
    int key = waitKey(30);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
