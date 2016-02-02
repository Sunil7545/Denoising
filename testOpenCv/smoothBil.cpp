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

	double a;
	cout << " enter the co-ordination factor ::  " << endl;
	cin >> a;

	//create 2 empty windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Noise", CV_WINDOW_AUTOSIZE);
	namedWindow("Original Image Lap", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image Lap", CV_WINDOW_AUTOSIZE);
	namedWindow("Noise Lap", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image Grad", CV_WINDOW_AUTOSIZE);

	// Load an image from file
	//Mat srcO = imread("TestData_2.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat srcO = imread("Noise_Lines.tif", CV_LOAD_IMAGE_UNCHANGED);
	
	//show the loaded image
//	imshow("Original Image", srcO);
//	Mat multNoise = cvRandArr
	Mat dst, dstI,dstA, noise,src,srcOlap,noiseLap,smoothLap;

	 srcO.copyTo(src);

	for (int i = 0; i <iteration; i++)
	{
		
		//GaussianBlur(src, dstI, Size(3, 3), 0, 0);
		blur(src, dstI, Size(3, 3));
		//smooth the image using Bilateral filter in the "src" and save it to "dst"
		bilateralFilter(src, dstA, wSize, 3, 6);

		// assign source to the modified image
		src = (dstA + (a*dstI))/(1+a);
		a = 0.8*a;

	}

	dst = src;
	noise = (srcO - dst);
	imshow("Original Image", srcO);

	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,grad;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(dst, grad_x, -1, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(dst, grad_y, -1, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

	imshow("Smoothed Image Grad", grad);

	//show the blurred image with the text
	imshow("Smoothed Image", dst);
	imshow("Noise", noise);
	// laplacian operator
	Mat Hc = (Mat_<double>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	filter2D(srcO, srcOlap, -1, Hc);
	filter2D(dst, smoothLap, -1, Hc);
	filter2D(noise, noiseLap, -1, Hc);
	imshow("Original Image Lap", srcOlap);
	imshow("Smoothed Image Lap", smoothLap);
	imshow("Noise Lap", noiseLap);
	//wait for a key press infinitely
	waitKey(0);

	return 0;
}