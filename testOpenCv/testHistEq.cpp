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
	//equalize the histogram
	vector<Mat> channels;
	Mat img_hist_equalized, img_gray_hist_equalized;
	//change the color image from BGR to YCrCb format
	cvtColor(img, img_hist_equalized, CV_BGR2YCrCb); 
	//split the image into channels
	split(img_hist_equalized, channels); 
	//equalize histogram on the 1st channel (Y)
	equalizeHist(channels[0], channels[0]); 
	//merge 3 channels including the modified 1st channel into one image
	merge(channels, img_hist_equalized); 
	//change the color image from YCrCb to BGR format (to display image properly)
	cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); 
	imwrite("lighthouse_histequal.jpg", img_hist_equalized);
	//for gray image equalization the histogram
	equalizeHist(img_gray, img_gray_hist_equalized);
	imwrite("lighthouse_gray_histequal.jpg", img_gray_hist_equalized);
	//create a window with the name "MyWindow"
	namedWindow("InputImage", CV_WINDOW_AUTOSIZE);
	namedWindow("HistColorImage", CV_WINDOW_AUTOSIZE);
	namedWindow("HistGrayImage", CV_WINDOW_AUTOSIZE);
	//	namedWindow("HistGrayImage", CV_WINDOW_AUTOSIZE);

	//display the image which is stored in the 'img' in the "MyWindow" window
	imshow("InputImage", img);
	imshow("HistColorImage", img_hist_equalized);
	imshow("HistGrayImage", img_gray_hist_equalized);
	waitKey(0); //wait infinite time for a keypress

	destroyWindow("InputImage");
	destroyWindow("HistColorImage");
	return 0;
}