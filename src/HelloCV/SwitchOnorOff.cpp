#include "stdafx.h"

int g_switch_value = 0;

void switch_callback(int position) {
		switch (position)
		{
		case 0:
			printf("0");
			break;
		case 1:
			printf("1");
			break;
		}
}

//int main() {
//
//	cvNamedWindow("Demo Window", 1);
//	cvCreateTrackbar(
//		"Switch",
//		"Demo Window",
//		&g_switch_value,
//		1,
//		switch_callback
//	);
//	while (1) {
//		if (cvWaitKey(100) == 27) {
//			break;
//		}
//	}
//	cvDestroyAllWindows();
//
//	return 0;
//}