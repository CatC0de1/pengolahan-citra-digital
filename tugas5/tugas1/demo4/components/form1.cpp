#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// image negative
void showNegative(const Mat& input) {
  Mat negativeImage = 255 - input;  // membalikan nilai piksel
  imshow("1. Image Negative", negativeImage);
}

// log transform
void showLogTransform(const Mat& input) {
  Mat logImage;
  input.convertTo(logImage, CV_32F);
  logImage += 1;
  log(logImage, logImage);  // log transform
  normalize(logImage, logImage, 0, 255, NORM_MINMAX);
  logImage.convertTo(logImage, CV_8U);
  imshow("2. Log Transform", logImage);
}

// power-law)
int gammaSlider = 100;

// fungsi untuk menangani trackbar gamma transform
void onGammaChange(int, void* userdata) {
  Mat* originalImg = static_cast<Mat*>(userdata);
  int sliderVal = getTrackbarPos("Gamma x0.01", "3. Power-Law)");
  float gamma = sliderVal / 100.0f;
  Mat gammaImage;
  originalImg->convertTo(gammaImage, CV_32F);
  normalize(gammaImage, gammaImage, 0, 1, NORM_MINMAX);
  pow(gammaImage, gamma, gammaImage);  // gamma transform
  normalize(gammaImage, gammaImage, 0, 255, NORM_MINMAX);
  gammaImage.convertTo(gammaImage, CV_8U);
  imshow("3. Power-Law)", gammaImage);

  // opsional: simpan gambar saat gamma berubah
  // int key = waitKey(1);
  // if (key == 's' || key == 'S') {
  //   system("mkdir output >nul 2>&1");
  //   string filename = "./output/3. gamma_transform_param" + to_string(gamma) + ".png";
  //   imwrite(filename, gammaImage);
  //   cout << "Gambar Gamma Transform disimpan sebagai: " << filename << endl;
  // }
}

// fungsi untuk menampilkan trackbar gamma transform
void showGammaGUI(const Mat& input) {
  namedWindow("3. Power-Law", WINDOW_AUTOSIZE);
  createTrackbar("Gamma x0.01", "3. Power-Law", NULL, 300, onGammaChange, (void*)&input);
  setTrackbarPos("Gamma x0.01", "3. Power-Law", gammaSlider); // Set default value
  onGammaChange(0, (void*)&input);  
}

// piecewise linear transform
int r1 = 70, r2 = 140, s1 = 0, s2 = 255;

// fungsi untuk menangani trackbar piecewise linear transform
void onPiecewiseChange(int, void* userdata) {
  Mat* originalImg = static_cast<Mat*>(userdata);
  int local_r1 = getTrackbarPos("r1", "4. Piecewise Linear");
  int local_r2 = getTrackbarPos("r2", "4. Piecewise Linear");
  int local_s1 = getTrackbarPos("s1", "4. Piecewise Linear");
  int local_s2 = getTrackbarPos("s2", "4. Piecewise Linear");
  Mat piecewiseImage = originalImg->clone();

  if (piecewiseImage.channels() == 1) { // Handle grayscale images
    for (int y = 0; y < piecewiseImage.rows; y++) {
      for (int x = 0; x < piecewiseImage.cols; x++) {
        uchar r = piecewiseImage.at<uchar>(y, x);
        if (r < local_r1)  // piecewise diterapkan pada blok if else
          r = local_s1;
        else if (r <= local_r2)
          r = static_cast<uchar>((float)(local_s2 - local_s1) / (local_r2 - local_r1) * (r - local_r1) + local_s1);  // rumus utama
        else
          r = 255;
        piecewiseImage.at<uchar>(y, x) = r;
      }
    }
  } else { // Handle color images
    for (int y = 0; y < piecewiseImage.rows; y++) {
      for (int x = 0; x < piecewiseImage.cols; x++) {
        for (int c = 0; c < 3; c++) {
          uchar r = piecewiseImage.at<Vec3b>(y, x)[c];
          if (r < local_r1)
            r = local_s1;
          else if (r <= local_r2)
            r = static_cast<uchar>((float)(local_s2 - local_s1) / (local_r2 - local_r1) * (r - local_r1) + local_s1);
          else
            r = 255;
          piecewiseImage.at<Vec3b>(y, x)[c] = r;
        }
      }
    }
  }
  imshow("4. Piecewise Linear", piecewiseImage);
}

// fungsi untuk menampilkan trackbar piecewise linear transform
void showPiecewiseGUI(const Mat& input) {
  namedWindow("4. Piecewise Linear", WINDOW_AUTOSIZE);
  createTrackbar("r1", "4. Piecewise Linear", NULL, 255, onPiecewiseChange, (void*)&input);
  createTrackbar("r2", "4. Piecewise Linear", NULL, 255, onPiecewiseChange, (void*)&input);
  createTrackbar("s1", "4. Piecewise Linear", NULL, 255, onPiecewiseChange, (void*)&input);
  createTrackbar("s2", "4. Piecewise Linear", NULL, 255, onPiecewiseChange, (void*)&input);

  setTrackbarPos("r1", "4. Piecewise Linear", r1);
  setTrackbarPos("r2", "4. Piecewise Linear", r2);
  setTrackbarPos("s1", "4. Piecewise Linear", s1);
  setTrackbarPos("s2", "4. Piecewise Linear", s2);
  onPiecewiseChange(0, (void*)&input);
}

// entry form1
bool form1(const Mat& input) {
  showNegative(input);
  showLogTransform(input);
  showGammaGUI(input);
  showPiecewiseGUI(input);

  while (true) {
    int key = waitKey(50);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}