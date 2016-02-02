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
	// Convert images to gray scale;
	Mat img_gray = imread("Lighthouse.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	// Convert images to gray scale;
	int threshold;
	cout << "Enter the threshold value for binary image: " << endl;
	cin >> threshold;
	// valid threshold input
	if (threshold<0 && threshold>255)
	{
		cout << " Please enter the valid threshold value: " << endl;
		//system("pause"); //wait for a key press
		return -1;
	}
	Mat img_bw = img_gray > threshold;
	imwrite("lightHouse_bw.jpg", img_bw);
	
	//create a window with the name "MyWindow"
	namedWindow("InputImage", CV_WINDOW_AUTOSIZE);
	namedWindow("BWImage", CV_WINDOW_AUTOSIZE);
	
	//display the image which is stored in the 'img' in the "MyWindow" window
	imshow("InputImage", img);
	imshow("BWImage", img_bw);
	waitKey(0); //wait infinite time for a keypress
	//destroy the window with the name, "MyWindow"
	destroyWindow("InputImage");
	destroyWindow("BWImage");
	return 0;
}