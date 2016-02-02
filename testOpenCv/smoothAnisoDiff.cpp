#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

void anisotropicDiffusion(Mat& img, Mat&dst, int num_iter, double delta_t, int kappa)
{
	// Variables
	//double delta;
	double ikappa = 1 / kappa;

	// argument for filter
	int ddepth = -1;

	// convert to grayscale             ~0.5ms
//	cvtColor(img, res, CV_BGR2GRAY);
	//res = img;

	// initialize filter outputs        ~2-3us
	Mat nablaN, nablaS, nablaW, nablaE, nablaNE, nablaSE, nablaSW, nablaNW;

	// further initializations          ~2-3us
	Mat cN, cS, cW, cE, cNE, cSE, cSW, cNW;

	//window for laplacian computation
	Mat hN = (Mat_<double>(3, 3) << 0,1,0, 0,-1,0, 0,0,0);
	Mat hS = (Mat_<double>(3, 3) << 0,0,0, 0,-1,0, 0,1,0);
	Mat hE = (Mat_<double>(3, 3) << 0,0,0, 0,-1,1, 0,0,0);
	Mat hW = (Mat_<double>(3, 3) << 0,0,0, 1,-1,0, 0,0,0);
	Mat hNE = (Mat_<double>(3, 3) << 0,0,1, 0,-1,0, 0,0,0);
	Mat hSE = (Mat_<double>(3, 3) << 0,0,0, 0,-1,0, 0,0,1);
	Mat hSW = (Mat_<double>(3, 3) << 0,0,0, 0,-1,0, 1,0,0);
	Mat hNW = (Mat_<double>(3, 3) << 1,0,0, 0,-1,0, 0,0,0);

	Mat res;
	// Anisotropic diffusion.           
	for (int i = 1; i <= num_iter; i++) // one iteration ~44ms
	{
		GaussianBlur(img, res, Size(3, 3), 1, 1);
		//medianBlur(img, res, 3);
	//	cout << res;
	//	img.copyTo(res);
		// filtering                ~5ms
		filter2D(res, nablaN, ddepth, hN);
		filter2D(res, nablaS, ddepth, hS);
		filter2D(res, nablaW, ddepth, hW);
		filter2D(res, nablaE, ddepth, hE);
		filter2D(res, nablaNE, ddepth, hNE);
		filter2D(res, nablaSE, ddepth, hSE);
		filter2D(res, nablaSW, ddepth, hSW);
		filter2D(res, nablaNW, ddepth, hNW);
	//	cout << nablaN;
		// Diffusion function       ~28ms
		cN = nablaN*ikappa;
		cN.mul(cN);
		cN = 1.0 / (1.0 + cN);

		cS = nablaS*ikappa;
		cS.mul(cS);
		cS = 1.0 / (1.0 + cN);

		cW = nablaW*ikappa;
		cW.mul(cW);
		cW = 1.0 / (1.0 + cW);

		cE = nablaE*ikappa;
		cE.mul(cE);
		cE = 1.0 / (1.0 + cE);

		cNE = nablaNE*ikappa;
		cNE.mul(cNE);
		cNE = 1.0 / (1.0 + cNE);

		cSE = nablaSE*ikappa;
		cSE.mul(cSE);
		cSE = 1.0 / (1.0 + cSE);

		cSW = nablaSW*ikappa;
		cSW.mul(cSW);
		cSW = 1.0 / (1.0 + cSW);

		cNW = nablaNW*ikappa;
		cNW.mul(cNW);
		cNW = 1.0 / (1.0 + cNW);

		// Discrete PDE solution.       ~11ms
		Mat shift(img.rows, img.cols, DataType<double>::type);
		  shift = delta_t * (cN.mul(nablaN)                                 
			+ cS.mul(nablaS)                               
			+ cW.mul(nablaW)                                
			+ cE.mul(nablaE)                              
			+ cNE.mul(nablaNE) * 0.5                        
			+ cSE.mul(nablaSE) * 0.5                       
			+ cSW.mul(nablaSW) * 0.5                        
			+ cNW.mul(nablaNW) * 0.5);
		img = img + shift;
		//cout << shift;                    //+ (1 / (cv::pow(dd, 2)))*cNW.mul(nablaNW));
		normalize(img, img, 0, 1, NORM_MINMAX, CV_32F);
	}
	

	dst = img;
}

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


int main(int argc, char** argv)
{
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	int iteration;
	cout << " enter the number of iterations ::  " << endl;
	cin >> iteration;

	double intConst;
	cout << " enter the integration constant ::  " << endl;
	cin >> intConst;

	double edgeThre;
	cout << " enter the edge thyreshold value ::  " << endl;
	cin >> edgeThre;

	//create 2 empty windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);

	// Load an image from file
	Mat src = imread("Noise_Lines.tif", CV_LOAD_IMAGE_UNCHANGED);

	//check for the data type of the image
	string ty = type2str(src.type());
	printf("Matrix: %s %dx%d \n", ty.c_str(), src.cols, src.rows);

	// convert the floating data type image if its not one
	if (ty[2] != 'F'){
		cout << "Input is not a single channel float image so converting!!!" << endl;
		double min, max;
		minMaxLoc(src, &min, &max);
		src.convertTo(src, CV_32FC1, 1.0 / max);
	}

	//check for valid pixel value in the image i.e. remove NaN
	imgChk(src);

	//show the loaded image
	imshow("Original Image", src);

	Mat dst;

	anisotropicDiffusion(src, dst, iteration, intConst, edgeThre);
	//make the "dst" image, black
	//dst = Mat::zeros(src.size(), src.type());
	//imwrite("TestData_4_med.jpg", dst);
	//copy the text to the "zBuffer"
//	cout << dst;
	//show the black image with the text
	imshow("Smoothed Image", dst);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Anisotropic smoothing is done in ::  " << endl;
	cout << duration/1000000.0 ;
	//cout << dst;
	//wait for a key press infinitely
	waitKey(0);

	return 0;
}