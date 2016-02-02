#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


void lapMethod(Mat& res)
{
	// argument for filter
	int ddepth = -1;
	//source and result
	//img = res;
	// initialize filter outputs        ~2-3us
	Mat nablaN, nablaS, nablaW, nablaE, nablaNE, nablaSE, nablaSW, nablaNW, nablaHc,GradX,GradZ,GradSobel;

	//window for laplacian computation
	Mat hN = (Mat_<double>(3, 3) << 0, 1, 0, 0, -1, 0, 0, 0, 0);
	Mat hS = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 0, 1, 0);
	Mat hE = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 1, 0, 0, 0);
	Mat hW = (Mat_<double>(3, 3) << 0, 0, 0, 1, -1, 0, 0, 0, 0);
	Mat hNE = (Mat_<double>(3, 3) << 0, 0, 1, 0, -1, 0, 0, 0, 0);
	Mat hSE = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 0, 0, 1);
	Mat hSW = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 1, 0, 0);
	Mat hNW = (Mat_<double>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, 0);
	Mat Hc = (Mat_<double>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);

		// filtering                ~5ms
		filter2D(res, nablaN, ddepth, hN);
		filter2D(res, nablaS, ddepth, hS);
		filter2D(res, nablaW, ddepth, hW);
		filter2D(res, nablaE, ddepth, hE);
		filter2D(res, nablaNE, ddepth, hNE);
		filter2D(res, nablaSE, ddepth, hSE);
		filter2D(res, nablaSW, ddepth, hSW);
		filter2D(res, nablaNW, ddepth, hNW);
		filter2D(res, nablaHc, ddepth, Hc);

		Sobel(res, GradX, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
		convertScaleAbs(grad_x, abs_grad_x);

		//create 8 empty windows
		namedWindow("North", CV_WINDOW_AUTOSIZE);
		namedWindow("South", CV_WINDOW_AUTOSIZE);
		namedWindow("West", CV_WINDOW_AUTOSIZE);
		namedWindow("East", CV_WINDOW_AUTOSIZE);

		namedWindow("North East", CV_WINDOW_AUTOSIZE);
		namedWindow("South East", CV_WINDOW_AUTOSIZE);
		namedWindow("South West", CV_WINDOW_AUTOSIZE);
		namedWindow("North West", CV_WINDOW_AUTOSIZE);
		namedWindow("Gradient", CV_WINDOW_AUTOSIZE);


		//show the loaded image
		imshow("North", nablaN);
		imshow("South", nablaS);
		imshow("West", nablaW);
		imshow("East", nablaE);
		imshow("North East", nablaNE);
		imshow("South East", nablaSE);
		imshow("South West", nablaSW);
		imshow("North West", nablaNW);
		imshow("Gradient", nablaHc);
		
		/*imwrite("TestData_4_north.jpg", nablaN);
		imwrite("TestData_4_south.jpg", nablaS);
		imwrite("TestData_4_west.jpg", nablaW);
		imwrite("TestData_4_east.jpg", nablaE);
		imwrite("TestData_4_northEast.jpg", nablaNE);
		imwrite("TestData_4_southEast.jpg", nablaSE);
		imwrite("TestData_4_southWest.jpg", nablaSW);
		imwrite("TestData_4_northWest.jpg", nablaNW);*/
//		imwrite("TestData_4_gradient.jpg", nablaHc);

		
}

void gaussSmooth(Mat& img, Mat& res, int num_iter, int window){
	for (int i = 0; i < num_iter; i++)
	{
		//copy the text to the "zBuffer"
		//	_snprintf_s(zBuffer, 35, "iterations : %d", i);

		//smooth the image using Gaussian kernel in the "src" and save it to "dst"
	//	GaussianBlur(img, res, Size(window, window), 0, 0);
		medianBlur(img, res, window);

		// assign source to the modified image
		img = res;

		//put the text in the "zBuffer" to the "dst" image
		//	putText(dst, zBuffer, Point(src.cols / 4, src.rows / 8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2);

		//show the blurred image with the text
	}
	imshow("Smoothed Image", res);
}
int main(int argc, char** argv)
{

	/*int iteration;
	cout << " enter the number of iterations ::  " << endl;
	cin >> iteration;*/

	/*double intConst;
	cout << " enter the integration constant ::  " << endl;
	cin >> intConst;

	double edgeThre;
	cout << " enter the edge thyreshold value ::  " << endl;
	cin >> edgeThre;*/

	//create 2 empty windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);

	// Load an image from file
	Mat src = imread("Original_Lines.tif", CV_LOAD_IMAGE_UNCHANGED);

	//show the loaded image
	imshow("Original Image", src);

	Mat dst;
	gaussSmooth(src, dst, 5, 3);
	lapMethod(dst);
//	anisotropicDiffusion(src, dst, iteration, intConst, edgeThre);
	//make the "dst" image, black
	//dst = Mat::zeros(src.size(), src.type());
	//imwrite("TestData_4_med.jpg", dst);
	//copy the text to the "zBuffer"

	//show the black image with the text
	//imshow("Smoothed Image", dst);
	cout << " Gradient is done is done ::  " << endl;
	//wait for a key press infinitely
	waitKey(0);

	return 0;
}