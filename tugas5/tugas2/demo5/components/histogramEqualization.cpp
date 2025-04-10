#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

// fungsi untuk menampilkan histogram
void showHistogram(const string& winName, const Mat& image) {
  CV_Assert(image.type() == CV_8UC1);

  int histSize = 256;
  float range[] = {0, 256};
  const float* histRange = {range};
  Mat hist;

  calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange);

  int histW = 512, histH = 400;
  int binW = cvRound((double)histW / histSize);
  Mat histImage(histH, histW, CV_8UC1, Scalar(255));

  normalize(hist, hist, 0, histImage.rows, NORM_MINMAX);

  for (int i = 1; i < histSize; ++i) {
    line(histImage,
      Point(binW * (i - 1), histH - cvRound(hist.at<float>(i - 1))),
      Point(binW * i,       histH - cvRound(hist.at<float>(i))),
      Scalar(0), 2);
  }

  imshow(winName, histImage);
}

// histogram equalization
bool histogramEqualization(const Mat& image) {
  if (image.empty() || image.type() != CV_8UC1) {
    cerr << "Gambar tidak valid atau bukan grayscale.\n";
    return false;
  }

  imshow("Original Image", image);

  Mat equalized;
  equalizeHist(image, equalized);  // melakukan histogram equalization

  showHistogram("Before Histogram Equalization", image);

  imshow("Image After Histogram Equalization", equalized);
  showHistogram("After Histogram Equalized", equalized);

  while (true) {
    int key = waitKey(50);
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}
