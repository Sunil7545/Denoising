#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;


//void anisotropicDiffusion(Mat& img, Mat&dst, int num_iter, double delta_t, int kappa)
//{
//	// Variables
//	//double delta;
//	double ikappa = 1 / kappa;
//
//	// argument for filter
//	int ddepth = -1;
//
//	// convert to grayscale             ~0.5ms
//	//	cvtColor(img, res, CV_BGR2GRAY);
//	//res = img;
//
//	// initialize filter outputs        ~2-3us
//	Mat nablaN, nablaS, nablaW, nablaE, nablaNE, nablaSE, nablaSW, nablaNW;
//
//	// further initializations          ~2-3us
//	Mat cN, cS, cW, cE, cNE, cSE, cSW, cNW;
//
//	//window for laplacian computation
//	Mat hN = (Mat_<double>(3, 3) << 0, 1, 0, 0, -1, 0, 0, 0, 0);
//	Mat hS = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 0, 1, 0);
//	Mat hE = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 1, 0, 0, 0);
//	Mat hW = (Mat_<double>(3, 3) << 0, 0, 0, 1, -1, 0, 0, 0, 0);
//	Mat hNE = (Mat_<double>(3, 3) << 0, 0, 1, 0, -1, 0, 0, 0, 0);
//	Mat hSE = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 0, 0, 1);
//	Mat hSW = (Mat_<double>(3, 3) << 0, 0, 0, 0, -1, 0, 1, 0, 0);
//	Mat hNW = (Mat_<double>(3, 3) << 1, 0, 0, 0, -1, 0, 0, 0, 0);
//
//	Mat res;
//	// Anisotropic diffusion.           
//	for (int i = 1; i <= num_iter; i++) // one iteration ~44ms
//	{
//		//	GaussianBlur(img, res, Size(3, 3), 0.1, 0.1);
//		//medianBlur(img, res, 3);
//		//	res = img;
//		// filtering                ~5ms
//		filter2D(img, nablaN, ddepth, hN);
//		filter2D(img, nablaS, ddepth, hS);
//		filter2D(img, nablaW, ddepth, hW);
//		filter2D(img, nablaE, ddepth, hE);
//		filter2D(img, nablaNE, ddepth, hNE);
//		filter2D(img, nablaSE, ddepth, hSE);
//		filter2D(img, nablaSW, ddepth, hSW);
//		filter2D(img, nablaNW, ddepth, hNW);
//
//		// Diffusion function       ~28ms
//		cN = nablaN*ikappa;
//		cN.mul(cN);
//		cN = 1.0 / (1.0 + cN);
//
//		cS = nablaS*ikappa;
//		cS.mul(cS);
//		cS = 1.0 / (1.0 + cN);
//
//		cW = nablaW*ikappa;
//		cW.mul(cW);
//		cW = 1.0 / (1.0 + cW);
//
//		cE = nablaE*ikappa;
//		cE.mul(cE);
//		cE = 1.0 / (1.0 + cE);
//
//		cNE = nablaNE*ikappa;
//		cNE.mul(cNE);
//		cNE = 1.0 / (1.0 + cNE);
//
//		cSE = nablaSE*ikappa;
//		cSE.mul(cSE);
//		cSE = 1.0 / (1.0 + cSE);
//
//		cSW = nablaSW*ikappa;
//		cSW.mul(cSW);
//		cSW = 1.0 / (1.0 + cSW);
//
//		cNW = nablaNW*ikappa;
//		cNW.mul(cNW);
//		cNW = 1.0 / (1.0 + cNW);
//
//		// Discrete PDE solution.       ~11ms
//		img = img +
//			delta_t * (                                     // dy^2 = 1 und dd^2 = 1/2, deshalb entspricht es:
//			cN.mul(nablaN)                                  //  (1 / (cv::pow(dy, 2)))*cN.mul(nablaN)
//			+ cS.mul(nablaS)                                //+ (1 / (cv::pow(dy, 2)))*cS.mul(nablaS)
//			+ cW.mul(nablaW)                                //+ (1 / (cv::pow(dx, 2)))*cW.mul(nablaW)
//			+ cE.mul(nablaE)                                //+ (1 / (cv::pow(dx, 2)))*cE.mul(nablaE)
//			+ cNE.mul(nablaNE) * 0.5                        //+ (1 / (cv::pow(dd, 2)))*cNE.mul(nablaNE)
//			+ cSE.mul(nablaSE) * 0.5                        //+ (1 / (cv::pow(dd, 2)))*cSE.mul(nablaSE)
//			+ cSW.mul(nablaSW) * 0.5                        //+ (1 / (cv::pow(dd, 2)))*cSW.mul(nablaSW)
//			+ cNW.mul(nablaNW) * 0.5);                      //+ (1 / (cv::pow(dd, 2)))*cNW.mul(nablaNW));
//	}
//	dst = img;
//}


	



int main(int argc, char** argv)
{

	/*int iteration;
	cout << " enter the number of iterations ::  " << endl;
	cin >> iteration;

	double intConst;
	cout << " enter the integration constant ::  " << endl;
	cin >> intConst;

	double edgeThre;
	cout << " enter the edge thyreshold value ::  " << endl;
	cin >> edgeThre;*/

	//create 2 empty windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Padded Image", CV_WINDOW_AUTOSIZE);

	// Load an image from file
	Mat img = imread("TestData_4.jpg", CV_LOAD_IMAGE_UNCHANGED);

	//show the loaded image
	imshow("Original Image", img);

	Mat imgPadded;
	copyMakeBorder(img, imgPadded, 3, 3,
		3, 3, BORDER_REPLICATE);
	// convert image in to double
	//imgPadded.convertTo(imgPadded, CV_64FC1);
	//anisotropicDiffusion(src, dst, iteration, intConst, edgeThre);
	//make the "dst" image, black
	//dst = Mat::zeros(src.size(), src.type());
	//imwrite("TestData_4_med.jpg", dst);
	//copy the text to the "zBuffer"
	//show the black image with the text
	imshow("Padded Image", imgPadded);
	cout << "Size of the original image :: " << endl;
	cout << img.rows<<endl;
	cout << img.cols << endl;
	cout << "Size of the padded image :: " << endl;
	cout << imgPadded.rows << endl;
	cout << imgPadded.cols << endl;
	cout << imgPadded;
	//wait for a key press infinitely
	waitKey(0);

	return 0;
}