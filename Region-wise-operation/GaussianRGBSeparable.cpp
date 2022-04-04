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

Mat gaussianfilter_sep(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);

int main() {

	Mat input = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	Mat output_z, output_m, output_a;

	if (!input.data)
	{
		std::cout << "Could not open" << std::endl;
		return -1;
	}

	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", input);
	output_z = gaussianfilter_sep(input, 1, 1, 1, "zero-paddle"); //Boundary process: zero-paddle, mirroring, adjustkernel
	output_m = gaussianfilter_sep(input, 1, 1, 1, "mirroring");
	output_a = gaussianfilter_sep(input, 1, 1, 1, "adjustkernel");

	namedWindow("Gaussian Filter_Zero-paddle_Separable", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter_Zero-paddle_Separable", output_z);

	namedWindow("Gaussian Filter_Mirroring_Separable", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter_Mirroring_Separable", output_m);

	namedWindow("Gaussian Filter_AdjustKernel_Separable", WINDOW_AUTOSIZE);
	imshow("Gaussian Filter_AdjustKernel_Separable", output_a);


	waitKey(0);

	return 0;
}


Mat gaussianfilter_sep(const Mat input, int n, float sigmaT, float sigmaS, const char* opt) {

	Mat kernel;

	int row = input.rows;
	int col = input.cols;
	int kernel_size = (2 * n + 1);
	int tempa;
	int tempb;
	float denom;
	float kernelvalue;

	// Initialiazing Kernel Matrix 
	kernel = Mat::zeros(kernel_size, kernel_size, CV_32F);


	denom = 0.0;
	for (int a = -n; a <= n; a++) {  // Denominator in m(s,t)
		for (int b = -n; b <= n; b++) {
			float value1 = exp(-(pow(a, 2) / (2 * pow(sigmaS, 2))) - (pow(b, 2) / (2 * pow(sigmaT, 2))));
			kernel.at<float>(a + n, b + n) = value1;
			denom += value1;
		}
	}

	for (int a = -n; a <= n; a++) {  // Denominator in m(s,t)
		for (int b = -n; b <= n; b++) {
			kernel.at<float>(a + n, b + n) /= denom;
		}
	}

	Mat output = Mat::zeros(row, col, input.type());
	Mat temp = Mat::zeros(row, col, input.type());


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {


			if (!strcmp(opt, "zero-paddle")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;

				for (int a = -n; a <= n; a++) {
					kernelvalue = kernel.at<float>(a + n, 0);
					if ((i + a <= row - 1) && (i + a >= 0)) { //if the pixel is not a border pixel
						sum1_r += kernelvalue * (float)(input.at<C>(i + a, j)[0]);
						sum1_g += kernelvalue * (float)(input.at<C>(i + a, j)[1]);
						sum1_b += kernelvalue * (float)(input.at<C>(i + a, j)[2]);
					}
				}
				temp.at<C>(i, j)[0] = (G)sum1_r;
				temp.at<C>(i, j)[1] = (G)sum1_g;
				temp.at<C>(i, j)[2] = (G)sum1_b;

				sum1_r = 0.0;
				sum1_g = 0.0;
				sum1_b = 0.0;

				for (int b = -n; b <= n; b++) {
					kernelvalue = kernel.at<float>(0, b + n);
					if ((j + b <= col - 1) && (j + b >= 0)) { //if the pixel is not a border pixel
						sum1_r += kernelvalue * (float)(temp.at<C>(i, j + b)[0]);
						sum1_g += kernelvalue * (float)(temp.at<C>(i, j + b)[1]);
						sum1_b += kernelvalue * (float)(temp.at<C>(i, j + b)[2]);
					}
				}
				output.at<C>(i, j)[0] = (G)sum1_r;
				output.at<C>(i, j)[1] = (G)sum1_g;
				output.at<C>(i, j)[2] = (G)sum1_b;
			}

			else if (!strcmp(opt, "mirroring")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;

				for (int a = -n; a <= n; a++) {
					kernelvalue = kernel.at<float>(a + n, 0);
					if (i + a > row - 1) {  //mirroring for the border pixels
						tempa = i - a;
					}
					else if (i + a < 0) {
						tempa = -(i + a);
					}
					else {
						tempa = i + a;
					}
					sum1_r += kernelvalue * (float)(input.at<C>(tempa, j)[0]);
					sum1_g += kernelvalue * (float)(input.at<C>(tempa, j)[1]);
					sum1_b += kernelvalue * (float)(input.at<C>(tempa, j)[2]);
				}
				temp.at<C>(i, j)[0] = (G)sum1_r;
				temp.at<C>(i, j)[1] = (G)sum1_g;
				temp.at<C>(i, j)[2] = (G)sum1_b;

				sum1_r = 0.0;
				sum1_g = 0.0;
				sum1_b = 0.0;

				for (int b = -n; b <= n; b++) {
					kernelvalue = kernel.at<float>(0, b + n);
					if (j + b > col - 1) {
						tempb = j - b;
					}
					else if (j + b < 0) {
						tempb = -(j + b);
					}
					else {
						tempb = j + b;
					}
					sum1_r += kernelvalue * (float)(temp.at<C>(i, tempb)[0]);
					sum1_g += kernelvalue * (float)(temp.at<C>(i, tempb)[1]);
					sum1_b += kernelvalue * (float)(temp.at<C>(i, tempb)[2]);
				}
				output.at<C>(i, j)[0] = (G)sum1_r;
				output.at<C>(i, j)[1] = (G)sum1_g;
				output.at<C>(i, j)[2] = (G)sum1_b;
			}


			else if (!strcmp(opt, "adjustkernel")) {
				float sum1_r = 0.0;
				float sum1_g = 0.0;
				float sum1_b = 0.0;
				float sum2 = 0.0;

				for (int a = -n; a <= n; a++) {
					kernelvalue = kernel.at<float>(a + n, 0);
					if ((i + a <= row - 1) && (i + a >= 0)) {
						sum1_r += kernelvalue * (float)(input.at<C>(i + a, j)[0]);
						sum1_g += kernelvalue * (float)(input.at<C>(i + a, j)[1]);
						sum1_b += kernelvalue * (float)(input.at<C>(i + a, j)[2]);
						sum2 += kernelvalue;
					}
				}
				temp.at<C>(i, j)[0] = (G)(sum1_r / sum2);
				temp.at<C>(i, j)[1] = (G)(sum1_g / sum2);
				temp.at<C>(i, j)[2] = (G)(sum1_b / sum2);

				sum1_r = 0.0;
				sum1_g = 0.0;
				sum1_b = 0.0;
				sum2 = 0.0;

				for (int b = -n; b <= n; b++) {
					kernelvalue = kernel.at<float>(0, b + n);
					if ((j + b <= col - 1) && (j + b >= 0)) {
						sum1_r += kernelvalue * (float)(temp.at<C>(i, j + b)[0]);
						sum1_g += kernelvalue * (float)(temp.at<C>(i, j + b)[1]);
						sum1_b += kernelvalue * (float)(temp.at<C>(i, j + b)[2]);
						sum2 += kernelvalue;
					}
				}

				output.at<C>(i, j)[0] = (G)(sum1_r / sum2);
				output.at<C>(i, j)[1] = (G)(sum1_g / sum2);
				output.at<C>(i, j)[2] = (G)(sum1_b / sum2);
			}
		}
	}
	return output;
}