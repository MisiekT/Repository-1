#include <iostream>
#include "/usr/include/opencv2/imgproc/imgproc.hpp"
#include "/usr/include/opencv2/core/core.hpp"
#include "/usr/include/opencv2/highgui/highgui.hpp"
using namespace cv;
using namespace std;

int main(void)
{
	const string nazwa_pliku = "zdj.jpg";
	int status = 0;
	Mat img = imread(nazwa_pliku);
	if( !img.data )
	{
		status = 0;
	} else {
		status = 1;
	}
	return status;
}
