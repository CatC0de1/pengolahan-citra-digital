/// error ///



// #include <iostream>
// #include <opencv2/opencv.hpp>

// using namespace std;
// using namespace cv;

// int main() {
//     int image[4][8] = {
//         {0, 0, 0, 0, 0, 0, 1, 1},
//         {0, 0, 1, 0, 0, 1, 0, 0},
//         {0, 0, 1, 0, 1, 1, 0, 0},
//         {0, 1, 1, 1, 0, 0, 0, 0}
//     };
    
//     int M = 4; // Jumlah baris
//     int N = 8; // Jumlah kolom
//     int L = 2; // Tingkat keabuan (0 dan 1)
    
//     Mat img = Mat::zeros(M, N, CV_8UC1);
    
//     for (int i = 0; i < M; i++) {
//         for (int j = 0; j < N; j++) {
//             img.at<uchar>(i, j) = image[i][j] * 255; // Skala nilai 0 dan 1 ke 0 dan 255
//         }
//     }
    
//     cout << "\nInformasi Citra:\n";
//     cout << "Resolusi Spasial: " << M << " x " << N << endl;
//     cout << "Tingkat Keabuan: " << L << endl;
    
//     namedWindow("Citra", WINDOW_NORMAL);
//     imshow("Citra", img);
//     waitKey(0);
//     destroyAllWindows();
    
//     return 0;
// }
