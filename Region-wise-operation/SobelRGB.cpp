#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>       /* exp */
#define IM_TYPE	CV_8UC3

using namespace cv;

// Image Type
// "G" for GrayScale Image, "C" for Color Image
#if (IM_TYPE == CV_8UC3)
typedef uchar G;
typedef cv::Vec3b C;
#elif (IM_TYPE == CV_16SC3)
typedef short G;
typedef Vec3s C;
#elif (IM_TYPE == CV_32SC3)
typedef int G;
typedef Vec3i C;
#elif (IM_TYPE == CV_32FC3)
typedef float G;
typedef Vec3f C;
#elif (IM_TYPE == CV_64FC3)
typedef double G;
typedef Vec3d C;
#endif

Mat sobelfilter(const Mat input);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output;

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);
	output = sobelfilter(input); //Boundary process: zero-paddle, mirroring, adjustkernel

	namedWindow("Sobel Filter", WINDOW_AUTOSIZE);
	imshow("Sobel Filter", output);


	waitKey(0);

	return 0;
}


Mat sobelfilter(const Mat input) {

	Mat kernel_Sx, kernel_Sy;

	int row = input.rows;
	int col = input.cols;
	int n = 1; // Sobel Filter Kernel N
	int tempa;
	int tempb;
	int Sx, Sy;

	// Initialiazing 2 Kernel Matrix with 3x3 size for Sx and Sy
	//Fill code to initialize Sobel filter kernel matrix for Sx and Sy (Given in the lecture notes)
	kernel_Sx = Mat::zeros(3, 3, CV_32F);
	kernel_Sy = Mat::zeros(3, 3, CV_32F);

	int fillSx[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int fillSy[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kernel_Sx.at<float>(i, j) = fillSx[k];
			k++;
		}
	}
	k = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kernel_Sy.at<float>(i, j) = fillSy[k];
			k++;
		}
	}

	Mat output = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			float sum1_r = 0.0;
			float sum1_g = 0.0;
			float sum1_b = 0.0;
			for (int a = -n; a <= n; a++) {
				for (int b = -n; b <= n; b++) {
					// Use mirroring boundary process
					// Find output M(x,y) = sqrt( input.at<G>(x, y)*Sx + input.at<G>(x, y)*Sy ) 
					Sx = kernel_Sx.at<float>(a + n, b + n);
					Sy = kernel_Sy.at<float>(a + n, b + n);
					if (i + a > row - 1) {  //mirroring for the border pixels
						tempa = i - a;
					}
					else if (i + a < 0) {
						tempa = -(i + a);
					}
					else {
						tempa = i + a;
					}
					if (j + b > col - 1) {
						tempb = j - b;
					}
					else if (j + b < 0) {
						tempb = -(j + b);
					}
					else {
						tempb = j + b;
					}
					sum1_r += sqrt(pow(input.at<C>(tempa, tempb)[0] * Sx, 2) + pow(input.at<C>(tempa, tempb)[0] * Sy, 2));
					sum1_g += sqrt(pow(input.at<C>(tempa, tempb)[1] * Sx, 2) + pow(input.at<C>(tempa, tempb)[1] * Sy, 2));
					sum1_b += sqrt(pow(input.at<C>(tempa, tempb)[2] * Sx, 2) + pow(input.at<C>(tempa, tempb)[2] * Sy, 2));
				}
				output.at<C>(i, j)[0] = (G)sum1_r;
				output.at<C>(i, j)[1] = (G)sum1_g;
				output.at<C>(i, j)[2] = (G)sum1_b;

			}
		}
	}
	return output;
}