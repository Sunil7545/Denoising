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
	cout << " enter the contrast factor ::  " << endl;
	cin >> bAmount;
	Mat imgH;
	//increase the contrast 
	img.convertTo(imgH, -1, bAmount, 0); 
	//decrease the contrast 
	Mat imgL;
	img.convertTo(imgL, -1, 1./bAmount, 0); 
	imwrite("lighthouse_HighContrast.jpg", imgH);
	imwrite("lighthouse_LowContrast.jpg", imgL);
	//create windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("High Contrast", CV_WINDOW_AUTOSIZE);
	namedWindow("Low Contrast", CV_WINDOW_AUTOSIZE);
	//show the image
	imshow("Original Image", img);
	imshow("High Contrast", imgH);
	imshow("Low Contrast", imgL);
	waitKey(0);
	destroyAllWindows(); //destroy all open windows
	return 0;
}