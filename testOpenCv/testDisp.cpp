#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


string type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "User"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

void imgChk(Mat &img){
	int r = img.rows;
	int c = img.cols;
	int counter = 0;
	for (int j = 0; j<r; j++)
	{
		for (int i = 0; i<c; i++)
		{
			if ((img.at<float>(j, i)) != (img.at<float>(j, i))){
				img.at<float>(j, i) = 0.0;
				counter++;
			}
		}
	}
	cout << "Number of NaN pixels in the image: ";
	cout << counter << endl;
}

int main(int argc, const char** argv)
{
	Mat img = imread("TestData_2.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'
	//check whether the image is loaded or not
	if (img.empty()) 
	{
		cout << "Error : Image cannot be loaded..!!" << endl;
		return -1;
	}
	//check for the data type of the image
	string ty = type2str(img.type());
	printf("Matrix: %s %dx%d \n", ty.c_str(), img.cols, img.rows);
	// convert the floating data type image if its not one
	if ( ty[2] != 'F'){
		cout << "Input is not a single channel float image so converting!!!"<<endl;
		double min, max;
		minMaxLoc(img, &min, &max);
		img.convertTo(img, CV_32FC1, 1.0 / max);
	}
	
	//check for valid pixel value in the image i.e. remove NaN
	imgChk(img);

	namedWindow("InputImage", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("InputImage", img); //display the image which is stored in the 'img' in the "MyWindow" window

	waitKey(0); //wait infinite time for a keypress

	destroyWindow("InputImage"); //destroy the window with the name, "MyWindow"

	return 0;
}