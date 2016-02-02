#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	VideoCapture cap("joker.avi"); // open the video file for reading

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video file" << endl;
		return -1;
	}

	//cap.set(CV_CAP_PROP_POS_MSEC, 200); //start the video at 300ms

	double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
	int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));     // Get Codec Type- Int form


	cout << "Frame per seconds : " << fps << endl;
	cout << "Frame size : " << dWidth << " x " << dHeight << endl;
	cout << "Codec type of the video : " << ex << endl;

	int askFileTypeBox = cap.get(CV_CAP_PROP_FOURCC); //-1 is show box of codec  
	int Color = 1;
	Size S = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));

	VideoWriter outputVideo;
	outputVideo.open(".\\outVideo.avi", -1, cap.get(CV_CAP_PROP_FPS), S, Color);

	//namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	//while (1)
	//{
	//	Mat frame;

	//	bool bSuccess = cap.read(frame); // read a new frame from video

	//	if (!bSuccess) //if not success, break loop
	//	{
	//		cout << "Cannot read the frame from video file" << endl;
	//		break;
	//	}

	//	imshow("MyVideo", frame); //show the frame in "MyVideo" window

		if (waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
	//		break;
		}
	//}
	return 0;

}