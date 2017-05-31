#include<iostream>
#include"/usr/include/opencv2/imgproc/imgproc.hpp"
#include"/usr/include/opencv2/highgui/highgui.hpp"

using namespace cv; 
using namespace std; 
  
 
int main() 
{ 
    VideoCapture capture = VideoCapture(1);                             //kamera  
    Mat img, hsv_img, progowanie;                                       //obraz z kamery, obraz w hsv, wynik progowania
    vector<Mat> hsv_split;                                              //wektor, rozdzielone hsv
    namedWindow("live", CV_WINDOW_AUTOSIZE);                            //okno 
    Point center;                                                       //punkt
    int l_val = 100, u_val = 109;                                       //inty dla paskow
    
    createTrackbar( "dolna", "live", &l_val, 255, NULL ); 
    createTrackbar( "gorna", "live", &u_val, 255, NULL );
    cout << "hejjjj\n";
    
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
        
        cout << center.x << endl;					                              //wypisz wartosc
        imshow("live", progowanie);                                     //wynik progowania
    } 
    capture.release();                                                  //wyjscie z programu
    return 0; 								                                          //------------------
}
