#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

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

	for (int i = 1; i < iteration; i++)
	{
		//copy the text to the "zBuffer"
		_snprintf_s(zBuffer, 35, "Iteration : %d", i);

		//smooth the image using Median kernel in the "src" and save it to "dst"
		medianBlur(src, dst, wSize);

		// assign source to the modified image
		src = dst;

		//put the text in the "zBuffer" to the "dst" image
		putText(dst, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);

		//show the blurred image with the text
		imshow("Smoothed Image", dst);

		//wait for 2 seconds
		int c = waitKey(2000);

		//if the "esc" key is pressed during the wait, return
		if (c == 27)
		{
			return 0;
		}
	}

	//make the "dst" image, black
	//dst = Mat::zeros(src.size(), src.type());
	imwrite("TestData_4_med.jpg", dst);
	//copy the text to the "zBuffer"
	_snprintf_s(zBuffer, 35, "Press Any Key to Exit");

	//put the text in the "zBuffer" to the "dst" image
	putText(dst, zBuffer, Point(src.cols / 4, src.rows / 2), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));

	//show the black image with the text
	imshow("Smoothed Image", dst);

	//wait for a key press infinitely
	waitKey(0);

	return 0;
}