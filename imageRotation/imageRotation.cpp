#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt);

int main()
{
	Mat input, nearestRotated, bilinearRotated;

	// Read each image
	input = imread("lena.jpg");

	// Check for invalid input
	if (!input.data) {
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	// original image
	namedWindow("image");
	imshow("image", input);

	nearestRotated = myrotate<Vec3b>(input, 45, "nearest");
	bilinearRotated = myrotate<Vec3b>(input, 45, "bilinear");

	// rotated image
	namedWindow("Nearest Neighborhood");
	imshow("Nearest Neighborhood", nearestRotated);

	namedWindow("Bilinear");
	imshow("Bilinear", bilinearRotated);

	waitKey(0);

	return 0;
}

template <typename T>
Mat myrotate(const Mat input, float angle, const char* opt) {
	int row = input.rows;
	int col = input.cols;

	float radian = angle * CV_PI / 180;

	float sq_row = ceil(row * sin(radian) + col * cos(radian));
	float sq_col = ceil(col * sin(radian) + row * cos(radian));

	Mat output = Mat::zeros(sq_row, sq_col, input.type());

	for (int i = 0; i < sq_row; i++) {
		for (int j = 0; j < sq_col; j++) {
			float x = (j - sq_col / 2) * cos(radian) - (i - sq_row / 2) * sin(radian) + col / 2;
			float y = (j - sq_col / 2) * sin(radian) + (i - sq_row / 2) * cos(radian) + row / 2;

			if ((y >= 0) && (y <= (row - 1)) && (x >= 0) && (x <= (col - 1))) {
				if (!strcmp(opt, "nearest")) {
					output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(round(y), round(x));
				}
				else if (!strcmp(opt, "bilinear")) {
					int x1 = (int)x;
					int y1 = (int)y;
					int x2 = x1 + 1;
					int y2 = y1 + 1;
					float dx = x2 - x1;
					float dy = y2 - y1;

					Mat temp = Mat::zeros(row, col, input.type());

					temp.at<cv::Vec3b>(y1, x) = (1 - dx) * input.at<cv::Vec3b>(y1, x1) + dx * input.at<cv::Vec3b>(y1, x2);
					temp.at<cv::Vec3b>(y2, x) = (1 - dx) * input.at<cv::Vec3b>(y2, x1) + dx * input.at<cv::Vec3b>(y2, x2);
					temp.at<cv::Vec3b>(y, x) = (1 - dy) * temp.at<cv::Vec3b>(y1, x) + dy * temp.at<cv::Vec3b>(y2, x);

					output.at<cv::Vec3b>(i, j) = temp.at<cv::Vec3b>(y, x);
				}
			}
		}
	}

	return output;
}