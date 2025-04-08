#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "OpenCV is working!" << std::endl;

    cv::Mat img = cv::imread("../images/image.jpg");
    // cv::Mat img = cv::imread("./images/image.jpg");  // jikapada msys2 mingw64 hanya memiliki path "cd /c/users/arman/vsc/pcd"

    if (img.empty()) {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

    cv::imshow("Test Image", img);
    cv::waitKey(0);
    return 0;
}


/*
msys2 mingw64 :
cd /c/users/arman/vsc/pcd/(path file cpp)
g++ (namaFile).cpp -o (namaFile).exe $(pkg-config --cflags --libs opencv4)
./(namaFile).exe
*/