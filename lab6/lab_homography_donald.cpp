// Lab-6 file provided by Kaustubh Pathak
// Modified by Fanghang Ji

#include <stdio.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace std;
using namespace cv;

int main()
{

	//-- Localize the object
	std::vector<Point2f> srcPoints;
	std::vector<Point2f> dstPoints;

	// Fill-in:
	// Push all other points A, B, C,...,Z

	//Point A
    dstPoints.push_back(Point2f(60, 0));
    srcPoints.push_back(Point2f(157, 359));
    //Point B
    dstPoints.push_back(Point2f(120, 0));
    srcPoints.push_back(Point2f(248,364));
    //Point C
    dstPoints.push_back(Point2f(180, 0));
    srcPoints.push_back(Point2f(338,370));
    //Point D
    dstPoints.push_back(Point2f(240, 0));
    srcPoints.push_back(Point2f(427,378));
    //Point E
    dstPoints.push_back(Point2f(300, 0));
    srcPoints.push_back(Point2f(519,384));
    //Point F
    dstPoints.push_back(Point2f(360, 0));
    srcPoints.push_back(Point2f(612,388));
    //Point G
    dstPoints.push_back(Point2f(360, 60));
    srcPoints.push_back(Point2f(606,320));
    //Point H
    dstPoints.push_back(Point2f(360, 120));
    srcPoints.push_back(Point2f(601,256));
    //Point I
    dstPoints.push_back(Point2f(360, 180));
    srcPoints.push_back(Point2f(597,203));
    //Point J
    dstPoints.push_back(Point2f(360, 240));
    srcPoints.push_back(Point2f(593,155));
    //Point K
    dstPoints.push_back(Point2f(360, 300));
    srcPoints.push_back(Point2f(590,114));
    //Point L
    dstPoints.push_back(Point2f(300, 300));
    srcPoints.push_back(Point2f(522,108));
    //Point M
    dstPoints.push_back(Point2f(240, 300));
    srcPoints.push_back(Point2f(454,107));
    //Point N
    dstPoints.push_back(Point2f(180, 300));
    srcPoints.push_back(Point2f(389,102));
    //Point O
    dstPoints.push_back(Point2f(120, 300));
    srcPoints.push_back(Point2f(325,100));
    //Point P
    dstPoints.push_back(Point2f(60, 300));
    srcPoints.push_back(Point2f(255,95));
    //Point Q
    dstPoints.push_back(Point2f(0, 300));
    srcPoints.push_back(Point2f(194,92));
    //Point R
    dstPoints.push_back(Point2f(0, 240));
    srcPoints.push_back(Point2f(174,133));
    //Point S
    dstPoints.push_back(Point2f(0, 180));
    srcPoints.push_back(Point2f(152,178));
    //Point T
    dstPoints.push_back(Point2f(0, 120));
    srcPoints.push_back(Point2f(130,228));
    //Point U
    dstPoints.push_back(Point2f(0, 60));
    srcPoints.push_back(Point2f(100,287));
    // Example: Point V
    dstPoints.push_back(Point2f(0, 0));
    srcPoints.push_back(Point2f(69, 354));
    //Point W
    dstPoints.push_back(Point2f(60, 60));
    srcPoints.push_back(Point2f(184,293));
    //Point X
    dstPoints.push_back(Point2f(300, 60));
    srcPoints.push_back(Point2f(519,312));
    //Point Y
    dstPoints.push_back(Point2f(300, 240));
    srcPoints.push_back(Point2f(522,152));
    //Point Z
    dstPoints.push_back(Point2f(60, 240));
    srcPoints.push_back(Point2f(241,139));

	// Use the OpenCV findHomography to compute the homography matrix H.
	// Take the third parameter as just 0, which means use regular method using all points. 
	Mat H = findHomography( srcPoints, dstPoints, 0);

	cout << "The computed homography matrix size is: " << endl;
	cout << "rows: "<< H.rows << ", cols= "<< H.cols << endl;
	for (int i = 0; i < H.rows; ++i) {
		for (int j = 0; j < H.cols; ++j) {
			cout << H.at<float>(i, j) << ",\t";
		}
		cout << endl;
	}
	
	Mat Img = imread("donald_annotated_points.png" , 1);
	Mat Out_Img;

	// Use the warpPerspective method of OpenCV to convert the input image Img to
	// the corrected image Out_Img of size 300x300 using H.
	warpPerspective(Img, Out_Img, H, Size(300, 300));

	imshow("Input", Img);
	imshow("Output", Out_Img);
	imwrite("donald_annotated_points_out.png", Out_Img);
	waitKey(0);

}

