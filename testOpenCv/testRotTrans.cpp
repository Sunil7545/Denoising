#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	// Read original image 
	Mat imgOriginal = imread("Lighthouse.jpg");

	//if fail to read the image
	if (imgOriginal.data == false)
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	//show the original image
	const char* pzOriginalImage = "Original Image";
	namedWindow(pzOriginalImage, CV_WINDOW_AUTOSIZE);
	imshow(pzOriginalImage, imgOriginal);

	const char* pzRotatedImage = "Rotated and Translated Image";
	namedWindow(pzRotatedImage, CV_WINDOW_AUTOSIZE);

	int iAngle = 180;
	createTrackbar("Angle", pzRotatedImage, &iAngle, 360);

	int iImageHeight = imgOriginal.rows / 2;
	int iImageWidth = imgOriginal.cols / 2;

	int xTrans = imgOriginal.rows / 2; 
	int yTrans = imgOriginal.cols / 2;
	createTrackbar("X-Translation", pzRotatedImage, &xTrans, imgOriginal.rows);
	createTrackbar("Y-Translation", pzRotatedImage, &yTrans, imgOriginal.cols);


	while (true)
	{
		Mat matRotation = getRotationMatrix2D(Point(iImageWidth, iImageHeight), (iAngle - 180), 1);
		matRotation.at<int>(0, 2) = xTrans - 500;
		matRotation.at<int>(1, 2) = yTrans - 500;
		cout << "Matrix column " << matRotation.cols <<endl;
		cout << "Matrix rows " << matRotation.rows << endl;
		// Rotate the image
		Mat imgRotated;
		warpAffine(imgOriginal, imgRotated, matRotation, imgOriginal.size());

		imshow(pzRotatedImage, imgRotated);

		int iRet = waitKey(30);
		if (iRet == 27)
		{
			break;
		}
	}

	return 0;
}