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
	// Create a window
	namedWindow("My Window", 1);

	//Create trackbar to change brightness
	int iSliderValue1 = 100;
	createTrackbar("Brightness", "My Window", &iSliderValue1, 400);

	//Create trackbar to change contrast
	int iSliderValue2 = 100;
	createTrackbar("Contrast", "My Window", &iSliderValue2, 400);

	while (true)
	{
		//Change the brightness and contrast of the image 
		Mat dst;
		int iBrightness = iSliderValue1 - 100;
		double dContrast = iSliderValue2 / 100.0;
		img.convertTo(dst, -1, dContrast, iBrightness);

		//show the brightness and contrast adjusted image
		imshow("My Window", dst);

		// Wait until user press some key for 50ms
		int iKey = waitKey(50);

		//if user press 'ESC' key
		if (iKey == 27)
		{
			break;
		}
	}

	return 0;
}