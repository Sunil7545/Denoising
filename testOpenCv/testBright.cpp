#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	//read the image data in the file "MyPic.JPG" and store it in 'img'
	Mat img = imread("Lighthouse.jpg", CV_LOAD_IMAGE_UNCHANGED);
	//check whether the image is loaded or not
	if (img.empty())
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
		//system("pause"); //wait for a key press
		return -1;
	}
	int bAmount;
	cout << " enter the brighness amount (0-255)::  " << endl;
	cin >> bAmount;
	Mat imgH = img + Scalar(bAmount, bAmount, bAmount); //increase the brightness by 75 units
	Mat imgL = img + Scalar(-bAmount, -bAmount, -bAmount); //decrease the brightness by 75 units
	imwrite("lighthouse_HighBright.jpg", imgH);
	imwrite("lighthouse_LowBright.jpg", imgL);

	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("High Brightness", CV_WINDOW_AUTOSIZE);
	namedWindow("Low Brightness", CV_WINDOW_AUTOSIZE);

	imshow("Original Image", img);
	imshow("High Brightness", imgH);
	imshow("Low Brightness", imgL);
	waitKey(0);
	destroyAllWindows(); //destroy all open windows
	return 0;
}