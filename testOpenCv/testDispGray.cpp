#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	//read the image data in the file "MyPic.JPG" and store it in 'img'
	Mat img = imread("Lighthouse.jpg", CV_LOAD_IMAGE_UNCHANGED); 
	// Convert images to gray scale;
	Mat img_gray = imread("Lighthouse.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	// Convert images to gray scale;
	Mat img_bw = img_gray > 64;
	//equalize the histogram
	Mat img_hist_equalized, img_gray_hist_equalized;
	equalizeHist(img, img_hist_equalized);
	//equalizeHist(img_gray, img_gray_hist_equalized);

	if (img.empty()) //check whether the image is loaded or not
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
		//system("pause"); //wait for a key press
		return -1;
	}
	//create a window with the name "MyWindow"
	namedWindow("InputImage", CV_WINDOW_AUTOSIZE); 
	namedWindow("GrayImage", CV_WINDOW_AUTOSIZE);
	namedWindow("BWImage", CV_WINDOW_AUTOSIZE);
	namedWindow("HistColorImage", CV_WINDOW_AUTOSIZE);
//	namedWindow("HistGrayImage", CV_WINDOW_AUTOSIZE);

	//display the image which is stored in the 'img' in the "MyWindow" window
	imshow("InputImage", img); 
	imshow("GrayImage", img_gray);
	imshow("BWImage", img_bw);
	imshow("HistColorImage", img_hist_equalized);
	//imshow("HistGrayImage", img_gray_hist_equalized);
	waitKey(0); //wait infinite time for a keypress
	//destroy the window with the name, "MyWindow"
	destroyWindow("InputImage"); 
	destroyWindow("GrayImage");
	destroyWindow("BWImage");
	destroyWindow("HistColorImage");
	//destroyWindow("HistGrayImage");
	return 0;
}