#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main(char argc, char* argv[])
{
	cout << "Progarm is Starting" << endl;

	Mat image;


	image = imread("..\\..\\resources\\images\\hand.jpg");
	if (image.empty())
	{
		cout << "Read Error" << endl;
	}

	cout << "This image is " << image.rows << " x " << image.cols << endl;

	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", image);

	waitKey(0);
	return 0;
}