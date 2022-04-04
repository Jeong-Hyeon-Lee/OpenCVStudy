//OSP_Assignment03_Region-wise operation
//c++ project: opencv_region

1. MeanFilterGray.cpp
  : implements "Uniform Mean filtering" on grayscale image using three types of boundary processing "zero-paddle", "mirroring" and "adjustkernel".
  - The input image file "lena.jpg" should be under the project directory.

Mat meanfilter(const Mat input, int n, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
opt - type of boundary processing

2. MeanFilterRGB.cpp
  : implements "Uniform Mean filtering" on color image using three types of boundary processing "zero-paddle", "mirroring" and "adjustkernel".
  - The input image file "lena.jpg" should be under the project directory.

Mat meanfilter(const Mat input, int n, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
opt - type of boundary processing


3. GaussianGray.cpp
  : implements "Gaussian filtering" on grayscale image using three types of boundary processing "zero-paddle", "mirroring" and "adjustkernel".
  - The input image file "lena.jpg" should be under the project directory.

Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing

4. GaussianRGB.cpp
  : implements "Gaussian filtering" on color image using three types of boundary processing "zero-paddle", "mirroring" and "adjustkernel".
  - The input image file "lena.jpg" should be under the project directory.

Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing

5. SobelGray.cpp
  : implements "Sobel filtering" on grayscale image using boundary processing "mirroring".
  - The input image file "lena.jpg" should be under the project directory.

Mat sobelfilter(const Mat input);
parameters:
input - input image

6. SobelRGB.cpp
  : implements "Sobel filtering" on color image using boundary processing "mirroring".
  - The input image file "lena.jpg" should be under the project directory.

Mat sobelfilter(const Mat input);
parameters:
input - input image

7. LaplacianGray.cpp
  : implements "Laplacian filtering" on grayscale image using boundary processing "mirroring".
  - The input image file "lena.jpg" should be under the project directory.

Mat laplacianfilter(const Mat input);
parameters:
input - input image

8. LaplacianRGB.cpp
  : implements "Laplacian filtering" on color image using boundary processing "mirroring".
  - The input image file "lena.jpg" should be under the project directory.

Mat laplacianfilter(const Mat input);
parameters:
input - input image

9. GaussianGraySeparable.cpp
  : implements "Gaussian filtering" in a seperable manner on grayscale image using three types of boundary processing "zero-paddle", "mirroring" and "adjustkernel".
  - The input image file "lena.jpg" should be under the project directory.

Mat gaussianfilter_sep(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing

10. GaussianRGBSeparable.cpp
  : implements "Gaussian filtering" in a seperable manner on color image using three types of boundary processing "zero-paddle", "mirroring" and "adjustkernel".
  - The input image file "lena.jpg" should be under the project directory.

Mat gaussianfilter_sep(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing

11. UnsharpMaskingGray.cpp
  : implements "Unsharp masking" on grayscale image using Gaussian filtering as low-pass filter
  - The input image file "lena.jpg" should be under the project directory.

Mat unsharpmask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing
k - determines the amount of reducing low-frequency component (0<=k<=1)

Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing

12. UnsharpMaskingRGB.cpp
  : implements "Unsharp masking" on grayscale image using Gaussian filtering as low-pass filter
  - The input image file "lena.jpg" should be under the project directory.

Mat unsharpmask(const Mat input, int n, float sigmaT, float sigmaS, const char* opt, float k);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing
k - determines the amount of reducing low-frequency component (0<=k<=1)

Mat gaussianfilter(const Mat input, int n, float sigmaT, float sigmaS, const char* opt);
parameters:
input - input image
n - determines kernel size (2n+1)x(2n+1)
sigmaT, sigmaS - for Gaussian distribution
opt - type of boundary processing