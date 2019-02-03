#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;


int main(){
    char filename[] = "ncku.jpg";
    Mat img = imread(filename);
    std::cout << "The image size: " << img.cols << " x " << img.size().height << " x " << img.channels() << "\n";
    /*namedWindow("image", CV_WINDOW_AUTOSIZE);
    imshow("image", img);
    waitKey();*/


}