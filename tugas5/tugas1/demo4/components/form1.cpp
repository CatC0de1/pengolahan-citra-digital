#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// Image Negative
void showNegative(const Mat& input) {
  Mat negativeImage = 255 - input;
  imshow("1. Image Negative", negativeImage);
}

// Log Transform
void showLogTransform(const Mat& input) {
  Mat logImage;
  input.convertTo(logImage, CV_32F);
  logImage += 1;
  log(logImage, logImage);
  normalize(logImage, logImage, 0, 255, NORM_MINMAX);
  logImage.convertTo(logImage, CV_8U);
  imshow("2. Log Transform", logImage);
}

// Gamma Transform (Power-Law)
int gammaSlider = 100;

void onGammaChange(int, void* userdata) {
  Mat* originalImg = static_cast<Mat*>(userdata);
  int sliderVal = getTrackbarPos("Gamma x0.01", "3. Gamma Transform (Power-Law)");
  float gamma = sliderVal / 100.0f;
  Mat gammaImage;
  originalImg->convertTo(gammaImage, CV_32F);
  normalize(gammaImage, gammaImage, 0, 1, NORM_MINMAX);
  pow(gammaImage, gamma, gammaImage);
  normalize(gammaImage, gammaImage, 0, 255, NORM_MINMAX);
  gammaImage.convertTo(gammaImage, CV_8U);
  imshow("3. Gamma Transform (Power-Law)", gammaImage);
}

void showGammaGUI(const Mat& input) {
  namedWindow("3. Gamma Transform (Power-Law)", WINDOW_AUTOSIZE);
  createTrackbar("Gamma x0.01", "3. Gamma Transform (Power-Law)", NULL, 300, onGammaChange, (void*)&input);
  setTrackbarPos("Gamma x0.01", "3. Gamma Transform (Power-Law)", gammaSlider); // Set default value
  onGammaChange(0, (void*)&input);
}

// Piecewise Linear Transform
int r1 = 70, r2 = 140, s1 = 0, s2 = 255;

void onPiecewiseChange(int, void* userdata) {
  Mat* originalImg = static_cast<Mat*>(userdata);
  int local_r1 = getTrackbarPos("r1", "4. Piecewise Linear");
  int local_r2 = getTrackbarPos("r2", "4. Piecewise Linear");
  int local_s1 = getTrackbarPos("s1", "4. Piecewise Linear");
  int local_s2 = getTrackbarPos("s2", "4. Piecewise Linear");
  Mat piecewiseImage = originalImg->clone();
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
  imshow("4. Piecewise Linear", piecewiseImage);
}

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

// Entry Form1
bool form1(const Mat& input) {
  showNegative(input);
  showLogTransform(input);
  showGammaGUI(input);
  showPiecewiseGUI(input);

  while (true) {
    int key = waitKey(30);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}