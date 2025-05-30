#include "header.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


// RGB ke CMY: 
// C = 1 - R, 
// M = 1 - G, 
// Y = 1 - B
Mat convertToCmy(const Mat& image) {
  Mat imageBGR;
  image.convertTo(imageBGR, CV_32F, 1.0 / 255.0); // konversi ke float untuk operasi aritmatika

  // memisahkan kanal warna BGR
  vector<Mat> bgrChannels;
  split(imageBGR, bgrChannels);  // memisahkan kanal warna
  Mat c = 1.0 - bgrChannels[2];  // C = 1 - R
  Mat m = 1.0 - bgrChannels[1];  // M = 1 - G
  Mat y = 1.0 - bgrChannels[0];  // Y = 1 - B

  // menggabungkan kembali kanal CMY dalam urutan BGR
  vector<Mat> cmyChannels = { y, m, c };
  Mat cmy;
  merge(cmyChannels, cmy);

  cmy.convertTo(cmy, CV_8UC3, 255.0);  // konversi kembali ke 8-bit untuk ditampilkan
  imshow("CMY", cmy);
  return cmy;
}


// RGB ke CMYK:
// K = 1 - max(R, G, B)
// C = (1 - R - K) / (1 - K)
// M = (1 - G - K) / (1 - K)
// Y = (1 - B - K) / (1 - K)
Mat convertToCmyk(const Mat& image) {
  Mat imageBGR;
  image.convertTo(imageBGR, CV_32F, 1.0 / 255.0);  // konversi ke float untuk operasi aritmatika

  // memisahkan kanal warna RGB
  vector<Mat> bgrChannel;
  split(imageBGR, bgrChannel);  // memisahkan kanal warna

  // menghitung kanal K
  Mat K = 1 - max(max(bgrChannel[2], bgrChannel[1]), bgrChannel[0]);

  // menghitung kanal C, M, Y
  Mat C = (1 - bgrChannel[2] - K) / (1 - K + 1e-8);
  Mat M = (1 - bgrChannel[1] - K) / (1 - K + 1e-8);
  Mat Y = (1 - bgrChannel[0] - K) / (1 - K + 1e-8);

  // konversi ke 8-bit untuk ditampilkan
  C.convertTo(C, CV_8UC1, 255.0);
  M.convertTo(M, CV_8UC1, 255.0);
  Y.convertTo(Y, CV_8UC1, 255.0);
  K.convertTo(K, CV_8UC1, 255.0);

  // tampilkan kanal CMYK secara terpisah
  imshow("Cyan", C);
  imshow("Magenta", M);
  imshow("Yellow", Y);
  imshow("Black (K)", K);

  // menggabungkan kanal CMYK untuk pengembalian (opsional)
  // vector<Mat> cmykChannels = { C, M, Y, K };
  // Mat cmyk;
  // merge(cmykChannels, cmyk);
  // return cmyk;

  return Mat();
}


// RGB ke HSI: H = Hue, S = Saturation, I = Intensity (manual, kecuali jika HSV)
Mat convertToHsi(const Mat& image) {
  Mat hsi(image.size(), CV_32FC3);
  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      float r = image.at<Vec3b>(i, j)[2] / 255.0;
      float g = image.at<Vec3b>(i, j)[1] / 255.0;
      float b = image.at<Vec3b>(i, j)[0] / 255.0;

      // perhitungan Hue (H)
      float num = 0.5f * ((r - g) + (r - b));
      float den = sqrt((r - g) * (r - g) + (r - b) * (g - b)) + 1e-6f;
      float theta = acos(num / den);

      float H = (b > g) ? (2 * CV_PI - theta) : theta;
      H = H / (2 * CV_PI) * 255.0f;  // konversi ke rentang [0, 255]

      // perhitungan Saturation (S)
      float minVal = min(r, min(g, b));
      float S = 1 - 3 * minVal / (r + g + b + 1e-6f);
      S = S * 255.0f;  // konversi ke rentang [0, 255]

      // perhitungan Intensity (I)
      float I = (r + g + b) / 3.0f;
      I = I * 255.0f;  // konversi ke rentang [0, 255]

      // simpan nilai H, S, I ke matriks HSI
      hsi.at<Vec3f>(i, j)[0] = H; 
      hsi.at<Vec3f>(i, j)[1] = S; 
      hsi.at<Vec3f>(i, j)[2] = I;
    }
  }
  hsi.convertTo(hsi, CV_8UC3);  // Konversi ke 8-bit untuk ditampilkan

  // memisahkan kanal H, S, I
  vector<Mat> hsiChannels;
  split(hsi, hsiChannels);

  imshow("Hue", hsiChannels[0]);
  imshow("Saturation", hsiChannels[1]);
  imshow("Intensity", hsiChannels[2]);

  // menampilkan gambar gabungan HSI
  imshow("HSI", hsi);
  return hsi;
}


// RGB ke YUV: 
// Y = 0.299R + 0.587G + 0.114B, 
// U = 0.492(B - Y), 
// V = 0.877(R - Y)
Mat convertToYuv(const Mat& image) {
  Mat yuv;
  cvtColor(image, yuv, COLOR_BGR2YUV);

  // memisahkan kanal Y, U, V
  vector<Mat> yuvChannels;
  split(yuv, yuvChannels);

  imshow("Y Channel", yuvChannels[0]);
  imshow("U Channel", yuvChannels[1]);
  imshow("V Channel", yuvChannels[2]);

  // menampilkan gambar gabungan YUV
  imshow("YUV", yuv);
  return yuv;
}


// RGB ke YCbCr:
// R = Y + 1.402 * (Cr - 128)
// G = Y - 0.344136 * (Cb - 128) - 0.714136 * (Cr - 128)
// B = Y + 1.772 * (Cb - 128)
Mat convertToYcbcr(const Mat& image) {
  Mat ycbcr;
  cvtColor(image, ycbcr, COLOR_BGR2YCrCb);

  // memisahkan kanal Y, Cb, Cr
  vector<Mat> ycbcrChannels;
  split(ycbcr, ycbcrChannels);

  imshow("Y Channel", ycbcrChannels[0]);
  imshow("Cb Channel", ycbcrChannels[2]);
  imshow("Cr Channel", ycbcrChannels[1]);

  // menampilkan gambar gabungan YCbCr
  imshow("YCbCr", ycbcr);
  return ycbcr;
}


// entry point untuk konversi model warna
bool convert(const Mat& image, int pilihan) {
  switch (pilihan) {
    case 1:
      convertToCmy(image);
      break;
    case 2:
      convertToCmyk(image);
      break;
    case 3:
      convertToHsi(image);
      break;
    case 4:
      convertToYuv(image);
      break;
    case 5:
      convertToYcbcr(image);
      break;
  }

  while (true) {
    int key = waitKey(50); // ESC key
    if (key == 27) {
      destroyAllWindows();
      return true;
    }
  }
}