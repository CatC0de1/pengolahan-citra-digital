#include <iostream>
#include <opencv2/opencv.hpp>
#include "components/binary_image.hpp"
#include <fstream>

using namespace std;
using namespace cv;

// Fungsi untuk menyimpan matrix ke file txt
void saveFilteredMatrix(const Mat& matrix, const string& filename) {
  ofstream txtFile(filename);
  if (txtFile.is_open()) {
    for (int i = 0; i < matrix.rows; ++i) {
      for (int j = 0; j < matrix.cols; ++j) {
        txtFile << static_cast<int>(matrix.at<uchar>(i, j));
        if (j != matrix.cols - 1) txtFile << "\t";
      }
      txtFile << "\n";
    }
    txtFile.close();
    cout << "Matrix hasil filter berhasil disimpan ke '" << filename << "'\n";
  } else {
    cerr << "Gagal membuka file untuk menulis matrix.\n";
  }
}

int main() {
  cout << "\nOpenCV is working!\n\n";

  // citra biner dari konversi binaryImage
  Mat inputMat = binaryImage * 255 ; // Konversi ke citra biner (0 atau 255)

  // Structuring element 3x3 
  // [{1, 1, 1},
  // {1, 1, 1},
  // {1, 1, 1}]
  Mat structElem = getStructuringElement(MORPH_RECT, Size(3, 3));

  // Operasi morfologi
  Mat dilated, eroded, opened, closed;
  dilate(inputMat, dilated, structElem);
  erode(inputMat, eroded, structElem);
  morphologyEx(inputMat, opened, MORPH_OPEN, structElem);
  morphologyEx(inputMat, closed, MORPH_CLOSE, structElem);

  // Tampilkan hasil
  imshow("Original", inputMat);
  imshow("Dilated", dilated);
  imshow("Eroded", eroded);
  imshow("Opened", opened);
  imshow("Closed", closed);

  // Simpan hasil dalam format jpg
  imwrite("./output/jpg/Original.jpg", inputMat);
  imwrite("./output/jpg/Dilated.jpg", dilated);
  imwrite("./output/jpg/Eroded.jpg", eroded);
  imwrite("./output/jpg/Opened.jpg", opened);
  imwrite("./output/jpg/Closed.jpg", closed);

  // Simpan hasil dalam format txt
  saveFilteredMatrix(inputMat, "./output/txt/Original.txt");
  saveFilteredMatrix(dilated, "./output/txt/Dilated.txt");
  saveFilteredMatrix(eroded, "./output/txt/Eroded.txt");
  saveFilteredMatrix(opened, "./output/txt/Opened.txt");
  saveFilteredMatrix(closed, "./output/txt/Closed.txt");

  cout << "\nTekan ESC pada citra untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela citra untuk melihat citra yang lain.\n";

  while (true) {
    int key = waitKey(50);
    if (key == 27) { // ESC key
      cout << "Keluar dari program.\n";
      destroyAllWindows();
      return 0;
    }
  }
}


/*
g++ app.cpp -o Demo7 `pkg-config --cflags --libs opencv4`
./Demo7
*/