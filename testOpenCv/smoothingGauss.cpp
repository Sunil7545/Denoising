#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void meanFiltering( Mat& img, Mat& res, int num_iter, int window)
{
	for (int i = 0; i<num_iter; i++)
	{
		//copy the text to the "zBuffer"
	//	_snprintf_s(zBuffer, 35, "iterations : %d", i);

		//smooth the image using Gaussian kernel in the "src" and save it to "dst"
		GaussianBlur(img, res, Size(window, window), 0, 0);

		// assign source to the modified image
		img = res;

		//put the text in the "zBuffer" to the "dst" image
	//	putText(dst, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);

		//show the blurred image with the text
		imshow("Smoothed Image", res);

		//wait for 2 seconds
		int c = waitKey(2000);
		//if the "esc" key is pressed during the wait, return
		if (c == 27)
		{
			return;
		}
	}
}

int main(int argc, char** argv)
{
	int iteration;
	cout << " enter the number of iterations ::  " << endl;
	cin >> iteration;

	int wSize;
	cout << " enter the window size ::  " << endl;
	cin >> wSize;

	//create 2 empty windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);

	// Load an image from file
	Mat src = imread("TestData_4.jpg", CV_LOAD_IMAGE_UNCHANGED);

	//show the loaded image
	imshow("Original Image", src);

	Mat dst;
	char zBuffer[35];

	meanFiltering(src,dst,iteration,wSize);
	//make the "dst" image, black
//	dst = Mat::zeros(src.size(), src.type());
//	imwrite("TestData_4_gauss.jpg", dst);
	//copy the text to the "zBuffer"
	_snprintf_s(zBuffer, 35, "Press Any Key to Exit");

	//put the text in the "zBuffer" to the "dst" image
	putText(dst, zBuffer, Point(src.cols / 4, src.rows / 2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

	//show the black image with the text
	imshow("Smoothed Image", dst);
	cout << dst;
	//wait for a key press infinitely
	waitKey(0);

	return 0;
}