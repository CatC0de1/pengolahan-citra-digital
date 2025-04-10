#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// subtraction
void showSubtraction(const Mat& img1, const Mat& img2) {
  Mat result;
  absdiff(img1, img2, result);  // menghitung selisih absolut antara dua gambar
  imshow("Hasil Subtraction", result);
}

// entry form3
bool form3(const Mat& img1, const Mat& img2) {
  if (img1.empty() || img2.empty()) {
    cerr << "Salah satu gambar kosong!" << endl;
    return false;
  }

  imshow("Prepared Image 1", img1);
  imshow("Prepared Image 2", img2);

  showSubtraction(img1, img2);

  while (true) {
    int key = waitKey(50);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
