- Purpose of this code: Stitch(merge) two images into one

- How to run this code: run without debugging (Ctrl + F5)

- How to adjust parameters (if any):
1. 넣고 싶은 이미지를 수정하고 싶으면 파일을 바꾼다.
	// Read each image
	I1 = imread("Img01.jpg");
	I2 = imread("Img02.jpg");
2. blend_stitching 함수를 실행할 때 parameter 'alpha' 값이 커질수록 겹치는 부분에서 Image1이 더 큰 영향을 미치며 blending 되고,
'alpha'값이 작아질수록 Image2가 더 큰 영향을 미치며 blending된다
(0<=alpha<=1) 