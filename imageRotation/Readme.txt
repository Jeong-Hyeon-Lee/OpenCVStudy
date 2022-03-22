- Purpose of this code: Rotate a image

- How to run this code: run without debugging (Ctrl + F5)

- How to adjust parameters (if any):

Mat myrotate(const Mat input, float angle, const char* opt);

1. can change the image by changing the file name in
	// Read each image
	input = imread("lena.jpg");
2. can change rotation angle by changing parameter 'angle'
3. can change interpolation method(nearest neighborhood/bilinear) by changing parameter 'opt'