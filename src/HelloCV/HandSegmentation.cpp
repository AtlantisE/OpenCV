#include "stdafx.h"

void cvThresholdOtsu(IplImage* src, IplImage* dst)//otsu 最大类间差分法，一种自适应阈值确定方法  
{
	int height = src->height;
	int width = src->width;

	float histogram[256] = { 0 };
	for (int i = 0; i < height; i++)
	{
		unsigned char* p = (unsigned char*)src->imageData + src->widthStep*i;
		for (int j = 0; j < width; j++)
		{
			if (*(p + j) > 137 && *(p + j) < 175) {//cr值在人肤色范围内
			}
			else {//非肤色（背景色），置为黑色
				*(p + j) = 0;
			}
			histogram[*(p + j)]++;
			//histogram[*p++]++;
		}
	}
	int size = height * width;
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = histogram[i] / size;
	}
	float avgValue = 0;
	for (int i = 0; i < 256; i++)
	{
		avgValue += i*histogram[i];
	}

	int threshold;
	float maxVariance = 0;
	float w = 0, u = 0;
	for (int i = 0; i < 256; i++)
	{
		w += histogram[i];
		u += i*histogram[i];
		float t = avgValue*w - u;
		float variance = t*t / (w*(1 - w));
		if (variance > maxVariance)
		{
			maxVariance = variance;
			threshold = i;
		}
	}
	cvThreshold(src, dst, threshold, 255, CV_THRESH_BINARY);
}

void cvSkinOtsu(IplImage* src, IplImage* dst)
{
	assert(dst->nChannels == 1 && src->nChannels == 3);

	IplImage* ycrcb = cvCreateImage(cvGetSize(src), 8, 3);
	IplImage* cr = cvCreateImage(cvGetSize(src), 8, 1);
	cvCvtColor(src, ycrcb, CV_BGR2YCrCb);
	cvSplit(ycrcb, 0, cr, 0, 0);
	cvThresholdOtsu(cr, cr);
	cvCopy(cr, dst);
	cvReleaseImage(&cr);
	cvReleaseImage(&ycrcb);
}

// 计算两点(p1,p2) 和 (p3,p4) 之间的距离   
double distance(double p1, double p2, double p3, double p4)
{
	double a = (p1 - p3)*(p1 - p3) + (p2 - p4)*(p2 - p4);
	double b = sqrt(a);
	return b;
}

// 指尖检测
void fingerTip(IplImage* pImgColor)
{
	//IplImage* pImgColor = NULL;
	IplImage* pImgGray = NULL;
	IplImage* pImgContourAll = NULL;
	IplImage* pImgContourAppr = NULL;
	IplImage* pImgHull = NULL;
	IplImage* pImgDefects = NULL;
	//pImgColor = cvLoadImage("D:\\lin\\vs\\images\\gesture\\gesture11.jpg");
	if (!pImgColor) {
		cout << "failed to load image" << endl;
		exit(0);
	}

	pImgGray = cvCreateImage(cvGetSize(pImgColor), 8, 1);
	cvCvtColor(pImgColor, pImgGray, CV_RGB2GRAY);
	pImgContourAppr = cvCreateImage(cvGetSize(pImgGray), 8, 3);
	pImgContourAll = cvCreateImage(cvGetSize(pImgGray), 8, 3);
	pImgHull = cvCreateImage(cvGetSize(pImgGray), 8, 3);
	pImgDefects = cvCreateImage(cvGetSize(pImgGray), 8, 3);
	cvZero(pImgContourAppr);
	cvZero(pImgContourAll);
	cvZero(pImgHull);
	cvZero(pImgDefects);

	//canny
	CvMemStorage* storage = cvCreateMemStorage();
	CvSeq* contourSeqAll = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storage);
	cvCanny(pImgGray, pImgGray, 10, 30, 5);
	//cvFindContours(pImgGray, storage, &contourSeqAll, sizeof(CvContour), CV_RETR_LIST, CV_LINK_RUNS);
	cvFindContours(pImgGray, storage, &contourSeqAll, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	//original contours
	CvSeq* tseq = contourSeqAll;
	for (; contourSeqAll; contourSeqAll = contourSeqAll->h_next) {
		cvDrawContours(pImgContourAll, contourSeqAll, cvScalar(255, 0, 0), cvScalar(0, 0, 255), 0, 2);
	}
	contourSeqAll = tseq;

	CvMemStorage* storageAppr = cvCreateMemStorage();
	CvSeq* contourAppr = cvCreateSeq(0, sizeof(CvSeq), sizeof(CvPoint), storageAppr);
	contourAppr = cvApproxPoly(contourSeqAll, sizeof(CvContour), storageAppr, CV_POLY_APPROX_DP, 5, 1);
	//approximated contours
	tseq = contourAppr;
	for (; contourAppr; contourAppr = contourAppr->h_next) {
		cvDrawContours(pImgContourAppr, contourAppr, cvScalar(255, 0, 0), cvScalar(0, 0, 255), 0, 2);
	}
	contourAppr = tseq;

	//print contours
	/*cout<<"contours:"<<endl;
	for (int i=0;i<contourAppr->total;i++){
	CvPoint* p=(CvPoint*)CV_GET_SEQ_ELEM(CvPoint,contourAppr,i);
	cout<<p->x<<","<<p->y<<endl;
	cvCircle(pImgHull,*p,3,cvScalar(0,255,255));
	cvShowImage("hull",pImgHull);
	cvWaitKey(0);
	}*/


	////convex hull
	CvSeq* hull = cvConvexHull2(contourAppr);
	//convexity defects
	CvSeq* defectSeq = cvConvexityDefects(contourAppr, hull);
	//rearrange the detectSeq in linked sequence

	CvMemStorage* storage_r = cvCreateMemStorage(0);
	CvSeq* seq_r = cvCreateSeq(CV_32FC2, sizeof(CvSeq), sizeof(CvPoint), storage_r);
	for (int i = 0; i<defectSeq->total; i++) {
		CvConvexityDefect* dp = (CvConvexityDefect*)CV_GET_SEQ_ELEM(CvConvexityDefect, defectSeq, i);

		cvLine(pImgDefects, *(dp->start), *(dp->end), cvScalar(0, 0, 255));
		cvLine(pImgDefects, *(dp->start), *(dp->depth_point), cvScalar(0x00, 0x99, 0xff));
		cvLine(pImgDefects, *(dp->depth_point), *(dp->end), cvScalar(0xff, 0x99, 0x00));
		cvCircle(pImgDefects, *(dp->depth_point), 5, cvScalar(255, 0, 0), -1, 8, 0);
		cvSeqPush(seq_r, (dp->depth_point));
		cout <<"CvConvexityDefect "<< i << "	:(" << dp->start->x << "," << dp->start->y << ")" << endl;
	}
	
	//绘制手掌重心
	if (seq_r->total <= 0) {
		cout << "无指谷点，重心无法绘制！" << endl;
	}
	else {
		cout << "指谷点总数：" << seq_r->total << endl;
		CvMat* region = (CvMat*)seq_r;
		// 将保存多边形的矩阵region的重心计算出来并保存在moments中   
		CvMoments moments;
		CvPoint pt1;
		cvMoments(region, &moments, 0);
		double m00 = cvGetSpatialMoment(&moments, 0, 0);
		double m01 = cvGetSpatialMoment(&moments, 0, 1);
		double m10 = cvGetSpatialMoment(&moments, 1, 0);
		//double m00 = moments.m00;  // 总重  
		//double m10 = moments.m10;  // x轴重  
		//double m01 = moments.m01; //  y轴重  
		double inv_m00 = 1. / m00;  // 总重的倒数  
		pt1.x = cvRound(m10 * inv_m00);  // 重心的横坐标    
		pt1.y = cvRound(m01 * inv_m00);  // 重心的纵坐标 
		cvCircle(pImgDefects, pt1, 3, cvScalar(127, 127, 0), -1, 8, 0);
		cout << "手掌重心坐标：(" << pt1.x << ", " << pt1.y << ")" << endl;
	}
	

	cvShowImage("original", pImgColor);
	cvShowImage("canny", pImgGray);
	cvShowImage("contour all", pImgContourAll);
	cvShowImage("contour appr", pImgContourAppr);
	cvShowImage("ConvexityDefects", pImgDefects);
	//cvShowImage("hull",pImgHull);


	//cvWaitKey(0);

	//cvDestroyAllWindows();

	/*cvReleaseImage(&pImgColor);
	cvReleaseImage(&pImgGray);
	cvReleaseImage(&pImgContourAll);
	cvReleaseImage(&pImgContourAppr);
	cvReleaseImage(&pImgDefects);
	cvReleaseImage(&pImgHull);

	cvReleaseMemStorage(&storage);
	cvReleaseMemStorage(&storageAppr);*/
}

//主函数  
//int main()
//{
//
//	//CvCapture* capture = cvCaptureFromCAM(0);//从对摄像头的初始化捕获  
//	//if (!cvQueryFrame(capture)) {
//	//	cout << "Video capture failed, please check the camera." << endl;
//	//}
//	//else {
//	//	cout << "Video camera capture status: OK" << endl;
//	//}
//
//	//CvSize sz = cvGetSize(cvQueryFrame(capture));//得到摄像头图像大小  
//
//	//IplImage* src1 = cvLoadImage("D:\\lin\\vs\\images\\gesture\\gesture11.jpg");
//	IplImage* src1 = cvLoadImage("E:\\Programming\\C++\\vs_workspace\\images\\gesture\\gesture15.jpg");
//	CvSize sz = cvGetSize(src1);
//
//	//IplImage* src = cvCreateImage(sz, 8, 3);//3通道，每个通道8位  
//	IplImage* dst_crotsu = cvCreateImage(sz, 8, 1);
//	IplImage* dst_MaxSecond = cvCreateImage(sz, 8, 1);
//	IplImage* dst_hand = cvCreateImage(sz, 8, 3);
//	CvMemStorage* storage = cvCreateMemStorage(0);//分配大小为0的内存空间  
//	CvMemStorage* storageHand = cvCreateMemStorage(0);
//	CvMemStorage* dftStorage = cvCreateMemStorage(0);
//	CvMemStorage* minStorage = cvCreateMemStorage(0);
//
//	CvSeq* contour = 0;//用于选取最大两区域 
//	CvSeq* sq = 0;//用于选取手  
//
//	cvNamedWindow("source", CV_WINDOW_AUTOSIZE);//创建用于显示的窗口  
//	cvNamedWindow("cvSkinOtsu", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("cvHandFace", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("Hand", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("bg", CV_WINDOW_AUTOSIZE);
//
//	// 以下两行是为了计算图形的重心做准备   
//	CvMoments moments;
//	CvMat* region;
//	//定义一些点和具体的参数   
//	CvPoint pt1, pt2, ptmax;
//	double m00 = 0, m10, m01, p1x, p1y, p2x, p2y, max, sum, average;
//	int n = 0, Nc;
//
//	//    src = cvQueryFrame(capture);  
//	//    cvShowImage("source", src);  
//	//    cvSaveImage("test.img", src);  
//	//    cout<<"hejhd"<<endl;      
//	//while (1)
//	//{
//		IplImage* bg = cvCreateImage(sz, 8, 3);//  
//		cvRectangle(bg, cvPoint(0, 0), cvPoint(bg->width, bg->height), CV_RGB(255, 255, 255), -1, 8, 0);//画矩形，参数：Image，两个顶点坐标，线的颜色，线的厚度(CV_FILLED时绘制填充了色彩的矩形)，线条类型，坐标点的小数点位数  
//		bg->origin = 0;//表示坐标系统的原点，0表示左上，1表示左下  
//		for (int b = 0; b< int(bg->width / 10); b++)//画网格  
//		{
//			cvLine(bg, cvPoint(b * 20, 0), cvPoint(b * 20, bg->height), CV_RGB(200, 200, 200), 1, 8, 0);//画竖线  
//																										//cvLine（图像，线段的第一个端点，第二个端点，颜色，粗细，类型，坐标点的小数点位数）  
//			cvLine(bg, cvPoint(0, b * 20), cvPoint(bg->width, b * 20), CV_RGB(200, 200, 200), 1, 8, 0);//画横线  
//		}
//		cvShowImage("bg", bg);
//		//src = cvQueryFrame(capture);//得到一帧图像  
//		//cvSaveImage("src.jpg", src);
//		//cvShowImage("source", src);
//		cvShowImage("source", src1);
//
//		//中值滤波+高斯滤波去噪
//		cvNamedWindow("Median+Gaussian");
//		cvSmooth(src1, src1, CV_MEDIAN, 3, 3);
//		cvSmooth(src1, src1, CV_GAUSSIAN, 3, 3);
//		cvShowImage("Median+Gaussian", src1);
//
//		//    cvWaitKey(100);  
//		cvZero(dst_crotsu);
//		//cvSkinOtsu(src, dst_crotsu);//得到二值化图像  
//
//		//彩色图像的直方图均衡化
//		/*cvNamedWindow("EqualizeHist");
//		IplImage* channels_image[] = { 0, 0, 0, 0 };
//		IplImage* grayImage = cvCreateImage(cvGetSize(src1), IPL_DEPTH_8U, 1);
//		IplImage* eqHistImage = cvCreateImage(cvGetSize(src1), IPL_DEPTH_8U, 1);
//
//		for (int i = 0; i < src1->nChannels; i++) {
//			channels_image[i] = cvCreateImage(cvGetSize(src1), IPL_DEPTH_8U, 1);
//		}
//		cvSplit(src1, channels_image[0], channels_image[1], channels_image[2], channels_image[3]);
//		for (int i = 0; i < src1->nChannels; i++) {
//			cvEqualizeHist(channels_image[i], channels_image[i]);
//		}
//		cvMerge(channels_image[0], channels_image[1], channels_image[2], channels_image[3], src1);
//		cvShowImage("EqualizeHist", src1);*/
//		
//		////肤色+大津法阈值分割手势
//		cvSkinOtsu(src1, dst_crotsu);
//		cvShowImage("cvSkinOtsu", dst_crotsu);  
//
//		//二值图像的形态学处理
//		IplImage* temp = cvCreateImage(sz, 8, 1);
//		cvNamedWindow("SkinOtsu+Open+Close");
//		cvMorphologyEx(dst_crotsu, dst_crotsu, temp, 0, CV_MOP_OPEN, 1);
//		cvMorphologyEx(dst_crotsu, dst_crotsu, temp, 0, CV_MOP_CLOSE, 1);
//		cvShowImage("SkinOtsu+Open+Close", dst_crotsu);
//
//		//cvSaveImage("skinOtsu.jpg", dst_crotsu);
//
//		//cvThreshold(dst_crotsu, dst_crotsu, 127, 255, CV_THRESH_BINARY);
//
//		//手势轮廓提取
//		int contour_num = cvFindContours(dst_crotsu, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);//得到最大两轮廓  
//		double maxarea = 0;//  
//		double secondarea = 0;
//		double minarea = 100;
//		cvZero(dst_MaxSecond);
//		
//		CvSeq* contour_temp = contour;
//		int m = 0;
//		for (; contour != 0; contour = contour->h_next)
//		{
//			m++;
//			double tmparea = fabs(cvContourArea(contour));
//			if (tmparea < minarea) { cvSeqRemove(contour, 0); continue; }//删除噪声  
//			if (tmparea > maxarea) { secondarea = maxarea; maxarea = tmparea; }//得到最大面积  
//			else if (tmparea > secondarea) { secondarea = tmparea; }//得到第二大面积  
//			//CvScalar color = CV_RGB(255, 255, 255); 
//			//cvDrawContours(dst_MaxSecond, contour, color, color, 0, CV_FILLED);
//		}
//
//		contour = contour_temp;
//		
//		for (; contour != 0; contour = contour->h_next)//画出最大两区域  
//		{
//			if (contour->total <= 0) {//很重要，中断出错
//				continue;
//			}
//			double tmparea = fabs(cvContourArea(contour));
//			if (tmparea == maxarea)
//			{
//				CvScalar color = CV_RGB(255, 255, 255);
//				cvDrawContours(dst_MaxSecond, contour, color, color, 0, CV_FILLED);
//			}
//			else if (tmparea == secondarea)
//			{
//				CvScalar color = CV_RGB(255, 255, 255);
//				cvDrawContours(dst_MaxSecond, contour, color, color, 0, CV_FILLED);
//			}
//		}
//
//		cvShowImage("cvHandFace", dst_MaxSecond);
//		//cvSaveImage("handface.jpg", dst_MaxSecond);
//
//		//    cvWaitKey(100);  
//
//		//选取手区域  
//		cvZero(dst_hand);
//		cvThreshold(dst_MaxSecond, dst_MaxSecond, 127, 255, CV_THRESH_BINARY);
//		Nc = cvFindContours(dst_MaxSecond, storageHand, &sq, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
//		for (; sq != NULL; sq = sq->h_next)
//		{
//			max = 0;
//			sum = 0;
//			average = 0;
//			vector<CvPoint> pt_vec;
//			vector<CvPoint>::iterator piter;
//			n++;
//
//			CvSeq* csq = cvApproxPoly(sq, sizeof(CvContour), storageHand, CV_POLY_APPROX_DP, 25, 0);// 相似多边形逼近该轮廓，以更好地求重心坐标   
//			region = (CvMat*)csq;
//			// 将保存多边形的矩阵region的重心计算出来并保存在moments中   
//			cvMoments(region, &moments, 0);
//			m00 = moments.m00;  // 总重  
//			m10 = moments.m10;  // x轴重  
//			m01 = moments.m01; //  y轴重  
//			double inv_m00 = 1. / m00;  // 总重的倒数  
//			pt1.x = cvRound(m10 * inv_m00);  // 重心的横坐标  
//			p2x = pt1.x * 1.0;               // 用p2x表示重心的横坐标  
//			pt1.y = cvRound(m01 * inv_m00);  // 重心的纵坐标  
//			p2y = pt1.y * 1.0;     // 用p2y来表示重心的纵坐标，以方便计算距离     
//
//			cout << "contour #" << n << ":" << endl;  // 打印当前的轮廓  
//													  // 打印当前轮廓的重心   
//			cout << "重心: " << "(" << p2x << "," << p2y << ")" << endl;
//			// 打印当前轮廓包含像素点的总数   
//			cout << "sq->total = " << sq->total << endl;
//
//			//将当前轮廓中的每一个点保存在链表 pt_vec中   
//			for (int i = 0; i < sq->total; ++i)
//			{
//				CvPoint* p = CV_GET_SEQ_ELEM(CvPoint, sq, i);
//				pt_vec.push_back(*p);
//			}
//			// 将链表的迭代器指向链表中的第一个点上   
//			piter = pt_vec.begin();
//			//循环进行轮廓上每一个点的操作   
//			for (; piter < pt_vec.end(); ++piter)
//			{
//				pt2 = *piter;   // 将当前迭代器所指向的点保存在pt2中  
//				p1x = pt2.x * 1.0; // 获取当前点的横坐标  
//				p1y = pt2.y * 1.0; // 获取当前点的纵坐标  
//				double d = distance(p1x, p1y, p2x, p2y); // 求当前点到重心的距离  
//				sum += d;  // 每次将距离都加在sum，以便求总距离  
//
//						   //求最大距离所对应的点，把最大距离保存在max中，所对应的点 保存在 ptmax中   
//				if (d > max)
//				{
//					max = d;
//					ptmax = pt2;
//				}
//			}
//
//			//求轮廓所有的点到重心的平均距离   
//			average = sum / (sq->total * 1.0);
//			double ab = max / average;   // ab 就是那个倍数  
//			cout << "distanceMax = " << max << endl;  // 打印最大距离  
//			cout << "distanceAverage = " << average << endl; // 打印平均距离  
//			cout << "ab = " << ab << endl;  // 打印那个倍数  
//			if (ab < 1.5)     // 如果该倍数小于1.6,则舍弃该轮廓    改成1.5倍  
//			{
//				cout << "remove #" << n << endl;  // 打印删除的是哪个轮廓  
//				cvSeqRemove(sq, 0);  // 删除该轮廓  
//				continue;
//			}
//
//			//在bg图上确定手的区域  
//			CvRect rect = cvBoundingRect(sq, 0);//返回一个2d矩形的点集合 
//			cout << "Hand Width:" << rect.width << ",Hand Height:" << rect.height << endl;
//			cvRectangle(bg, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(255, 0, 0), 1, 8, 0);
//
//
//			//将保留下的轮廓填充颜色显示   
//			CvScalar color = CV_RGB(255, 0, 0);
//			cvDrawContours(dst_hand, sq, color, color, -1, -1, 8);
//
//			fingerTip(dst_hand);
//
//			//cvRectangle(dst_hand, cvPoint(rect.x, rect.y + rect.height), cvPoint(rect.x + rect.width, rect.y), CV_RGB(255, 0, 0), 1, 8, 0);
//			//cvCircle(dst_hand, cvPoint(p2x, p2y), 3, cvScalar(0, 255, 0), -1, 8, 0);
//
//			cvDrawContours(bg, sq, CV_RGB(127, 0, 0), CV_RGB(127, 0, 0), -1, -1, 8);
//			cvCircle(bg, cvPoint(p2x, p2y), 3, cvScalar(0, 255, 0), -1, 8, 0);
//
//			cvShowImage("bg", bg);
//
//			//在原图确定收的区域并绘制出手势区域的重心
//			cvRectangle(src1, cvPoint(rect.x, rect.y + rect.height), cvPoint(rect.x + rect.width, rect.y), CV_RGB(255, 0, 0), 1, 8, 0);
//			cvCircle(src1, cvPoint(p2x, p2y), 3, cvScalar(0, 255, 0), -1, 8, 0);
//
//			cvShowImage("source", src1);
//
//		}
//
//
//		cvShowImage("Hand", dst_hand);
//		//cvSaveImage("hand.jpg", dst_hand);
//
//		cvWaitKey(0);
//
//	//}
//
//	//cvReleaseCapture(&capture);
//	cvDestroyAllWindows();
//
//	return 0;
//}

