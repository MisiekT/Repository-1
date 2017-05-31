#include<iostream>
#include"/usr/include/opencv2/imgproc/imgproc.hpp"
#include"/usr/include/opencv2/highgui/highgui.hpp"

using namespace cv; 
using namespace std; 
  
 
int main(int argc, char** argv) 
{ 
    VideoCapture capture = VideoCapture(0);                             //kamera  
    Mat img, hsv_img, progowanie;                                       //obraz z kamery, obraz w hsv, wynik progowania
    vector<Mat> hsv_split;                                              //wektor, rozdzielone hsv
    Point center;                                                       //punkt
    int l_val = 100, u_val = 109;                                       //inty dla paskow  
    if (argc == 2) {
	l_val = std::stoi( argv[1] );
	u_val = std::stoi( argv[2] );
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
    } 
    capture.release();                                                  //wyjscie z programu
    return 0; 								//------------------
}


