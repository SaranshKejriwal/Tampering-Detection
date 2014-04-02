#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
int main ()
{
  Mat frame;
  Mat back;
  Mat fore;
  VideoCapture cap1(1);/*to capture from camera*/
  BackgroundSubtractorMOG2 bg;//works on GMM
  bg.set ("nmixtures", 10);
  vector < vector < Point > >contours;
  namedWindow ("Frame");
  int i=0;
	 
  for (;;)
    {
	cap1 >> frame;
    bg.operator()(frame, fore);
    bg.getBackgroundImage (back);
    erode (fore, fore, cv::Mat ());
    erode (fore, fore, cv::Mat ());
    dilate (fore, fore, cv::Mat ());
	dilate (fore, fore, cv::Mat ());
	dilate (fore, fore, cv::Mat ());
	findContours (fore, contours, CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    drawContours (frame, contours, -1, Scalar (255, 255, 255), 1);
	Scalar color = Scalar(200,200,200);
	int a=0;
	vector<Rect> boundRect( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
	  {
		   boundRect[i] = boundingRect( contours[i] );
	  }
	for( i = 0; i< contours.size(); i++ )
     {
		if(boundRect[i].width>=40 || boundRect[i].height>=40)//eliminates small boxes
			{
				a=a+(boundRect[i].height)*(boundRect[i].width);
			 }
		//  cout<<"Net contour area is "<<a<<"\n";
	    if(a>=int(frame.rows)*int(frame.cols)/2)//change denominator as per convenience
			{
				putText(frame,"Tampering",Point(5,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,255,255),2);
				cout<<"\a";
			}
	   }
   imshow ("Frame", frame);
   waitKey(10);	 
 }
  return 1;
}
