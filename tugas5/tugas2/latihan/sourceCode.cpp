#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main() {
  cout << "\nOpenCV is working!\n" << endl;

  uchar data[5][4] = {
    {29, 10, 12, 13},
    {34, 12, 13, 13},
    {31, 10, 11, 12},
    {30, 11, 14, 14},
    {31, 12, 12, 11}
  };

  Mat input(5, 4, CV_8UC1, data); // membuat citra 5x4 8-bit single channel

  // copy input ke bentuk mat baru (agar tidak share memory)
  Mat img = input.clone();

  // filter lowpass (blur biasa)
  Mat blurred;
  blur(img, blurred, Size(3, 3)); // kernel 3x3

  Mat input_resized, blurred_resized;
  resize(img, input_resized, Size(200, 250), 0, 0, INTER_NEAREST);
  resize(blurred, blurred_resized, Size(200, 250), 0, 0, INTER_NEAREST);

  cout << "Input Matrix:\n" << img << endl;
  cout << "\nFiltered (Lowpass - blur 3x3) Matrix:\n" << blurred << endl;

  imshow("Original Image (5x4)", input_resized);
  imshow("Filtered Image (Blur 3x3)", blurred_resized);

  imwrite("./output/original_image.cpp.jpg", input_resized);
  imwrite("./output/filtered_image.cpp.jpg", blurred_resized);
  cout << "\nCitra berhasil disimpan di folder output.\n";

  ofstream txtFile("./output/filtered_matrix.cpp.txt");
  if (txtFile.is_open()) {
    for (int i = 0; i < blurred.rows; ++i) {
      for (int j = 0; j < blurred.cols; ++j) {
        txtFile << static_cast<int>(blurred.at<uchar>(i, j));
        if (j != blurred.cols - 1) txtFile << "\t";
      }
      txtFile << "\n";
    }
    txtFile.close();
    cout << "Matrix hasil filter berhasil disimpan ke './output/filtered_matrix.cpp.txt'\n";
  } else {
    cerr << "Gagal membuka file untuk menulis matrix.\n";
  }

  cout << "Tekan ESC pada citra untuk menutup dan kembali ke menu.\n";
  cout << "Seret jendela citra untuk melihat citra yang lain.\n";

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
g++ sourceCode.cpp -o Latihan `pkg-config --cflags --libs opencv4`
./Latihan
*/