#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "OpenCV is working!" << std::endl;

    cv::Mat img = cv::imread("image.jpg");
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
cd /c/users/arman/vsc/pcd
g++ test.cpp -o test.exe $(pkg-config --cflags --libs opencv4)
./test.exe
*/