#include<iostream>
#include"/usr/include/opencv2/imgproc/imgproc.hpp"
#include"/usr/include/opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"
#define BUF_SIZE 128

using namespace cv; 
using namespace std; 
  
 
int main(int argc, char* argv[]) 
{ 
    int i=0;
    int cport_nr=24; /* /dev/ttyUSB0 */
    int bdrate=9600; /* 9600 baud */
    char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
    char str_send[BUF_SIZE]; // send data buffer
    int komenda;
    
    VideoCapture capture = VideoCapture(0);                             //kamera  
    Mat img, hsv_img, progowanie;                                       //obraz z kamery, obraz w hsv, wynik progowania
    vector<Mat> hsv_split;                                              //wektor, rozdzielone hsv
    Point center;                                                       //punkt
    int l_val = 100, u_val = 109;                                       //inty dla paskow  
    if (argc == 2) {
	l_val = atoi( argv[1] );
	u_val = atoi( argv[2] );
    }   
    
    while ( waitKey(20) != 27 )                 
    { 
        capture >> img;                                                 //przechwyt
        cvtColor(img, hsv_img, CV_BGR2HSV);                             //konwersja na hsv 
        split(hsv_img, hsv_split);                                      //podzial do hsv_split
        inRange(hsv_split[0], l_val, u_val, progowanie);                //progowanie do "progowanie" na hue
        cv::Mat element(3,3,CV_8U,cv::Scalar(1));                       // -|
        blur(progowanie, progowanie, cv::Size(3,3) );                   // -|- odszumianie 
        erode(progowanie, progowanie, element);                         // -|
        Moments mu = moments(progowanie, true);                         //momenty (masy)
        center.x = mu.m10 / mu.m00;                                     //wylicz wsp x
        
        cout << center.x << endl;					//wypisz wartosc
        i++;
	if(i%4 == 0){
	    sprintf(str_send, "%d", center.x);
	    RS232_cputs(cport_nr, str_send); 				// sends string on serial
	    printf("Sent to Arduino: '%s'\n", str_send);
	    i=0;
	}
    } 
    capture.release();                                                  //wyjscie z programu
    return 0; 								//------------------
}


