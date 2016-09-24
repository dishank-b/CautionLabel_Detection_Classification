#include <iostream>
#include <vector>
#include <stdio.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/photo/photo.hpp"


using namespace std;
using namespace cv;

Mat label1;
Mat label2;
Mat label3;
Mat image_color;
Mat bin_image1;
Mat label1_bin;
Mat label2_bin;
Mat label3_bin;
Mat image1;
Mat With_Contours = Mat::zeros(600, 1200, CV_8UC3);





int main( int argc, char** argv )
{


	label1 = imread("label1.png",0);
	label2 = imread("label2.png",0);
	label3 = imread("label3.png",0);
	image1 = imread(argv[1],0);
	image_color = imread(argv[1], 1);
	

	fastNlMeansDenoising(image1, image1, 25, 7, 21);
	resize(image1, image1, Size(1200,600), 0, 0, INTER_LINEAR );

	fastNlMeansDenoising(image_color, image_color, 25, 7, 21);
	resize(image_color, image_color, Size(1200,600), 0, 0, INTER_LINEAR );

	
	threshold( label1, label1_bin, 230, 255,THRESH_BINARY );
	threshold( label2, label2_bin, 230, 255,THRESH_BINARY );
	threshold( label3, label3_bin, 230, 255,THRESH_BINARY );
	threshold( image1, bin_image1, 160, 255,THRESH_BINARY );


	vector<vector<Point> > contours;
	vector<vector<Point> > contours_app;
  	vector<Vec4i> hierarchy;
  	vector<Point> cnt;
  	vector<Point> approxCurve;
  	double epsilon;
  	Mat copy;
  	int i = 10;
  	int count = 0;

  	
  	bin_image1.copyTo(copy);
  	findContours( bin_image1, contours, hierarchy, CV_RETR_TREE, CHAIN_APPROX_SIMPLE);

  	contours_app.resize(contours.size());
    for( int k = 0; k < contours.size(); k++ ){
		approxPolyDP(Mat(contours[k]), contours_app[k], 0.05*arcLength(contours[k], true), true);
		if (contourArea(contours[k],false)> 5000.00 && contours_app[k].size()<8 && contours_app[k].size() >3)
		{
			i = hierarchy[k][2];
			while(i != -1){
				if (contourArea(contours[i], false) > 120.00)
				{
					drawContours(image_color, contours, i, Scalar(0,255,0), 3);
					count++;
				}
				
				i = hierarchy[i][0];
			}
			if( count == 1){
				drawContours(image_color, contours, k, Scalar(0,0,255), 3);	
			}

			if( count == 2){
				drawContours(image_color, contours, k, Scalar(255,0,255), 3 );	
			}

			if( count == 5){
				drawContours(image_color, contours, k, Scalar(255,0,0), 3 );	
			}
				
		}
		count = 0;
        
 	}
 	// drawContours(With_Contours, contours_app, -1, Scalar(0,255,0), 1, 8, hierarchy, 2, Point(0,0) );

 	

    
    // threshold( With_Contours,With_Contours, 3, 255,THRESH_BINARY );
   	
  	namedWindow( "Label 1", CV_WINDOW_AUTOSIZE );
 	namedWindow( "Label 2", CV_WINDOW_AUTOSIZE );
	namedWindow( "Label 3", CV_WINDOW_AUTOSIZE );
	namedWindow( "Sample", CV_WINDOW_AUTOSIZE );
	namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
	// namedWindow( "With_Contours", CV_WINDOW_AUTOSIZE );

	imshow( "Label 1", label1_bin );
	imshow( "Label 2", label2_bin );
	imshow( "Label 3", label3_bin );
	imshow( "Sample", copy);
	imshow( "Contours", image_color );
	// imshow( "With_Contours", canny_output);


	waitKey(0);
	return 0;

}
