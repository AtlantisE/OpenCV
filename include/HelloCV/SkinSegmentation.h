#pragma once
#include "stdafx.h"  
// skin region location using rgb limitation  
void SkinRGB(IplImage* rgb, IplImage* _dst)
{
	assert(rgb->nChannels == 3 && _dst->nChannels == 3);

	static const int R = 2;
	static const int G = 1;
	static const int B = 0;

	IplImage* dst = cvCreateImage(cvGetSize(_dst), 8, 3);
	cvZero(dst);

	for (int h = 0; h<rgb->height; h++)
	{
		unsigned char* prgb = (unsigned char*)rgb->imageData + h*rgb->widthStep;
		unsigned char* pdst = (unsigned char*)dst->imageData + h*dst->widthStep;
		for (int w = 0; w<rgb->width; w++)
		{
			if ((prgb[R]>95 && prgb[G]>40 && prgb[B]>20 &&
				prgb[R] - prgb[B]>15 && prgb[R] - prgb[G]>15) ||//uniform illumination  
				(prgb[R]>200 && prgb[G]>210 && prgb[B]>170 &&
					abs(prgb[R] - prgb[B]) <= 15 && prgb[R]>prgb[B] && prgb[G]>prgb[B])//lateral illumination  
				)
			{
				memcpy(pdst, prgb, 3);
			}
			prgb += 3;
			pdst += 3;
		}
	}
	cvCopy(dst, _dst);
	cvReleaseImage(&dst);
}

// skin detection in rg space  
void cvSkinRG(IplImage* rgb, IplImage* gray)
{
	assert(rgb->nChannels == 3 && gray->nChannels == 1);

	const int R = 2;
	const int G = 1;
	const int B = 0;

	double Aup = -1.8423;
	double Bup = 1.5294;
	double Cup = 0.0422;
	double Adown = -0.7279;
	double Bdown = 0.6066;
	double Cdown = 0.1766;
	for (int h = 0; h<rgb->height; h++)
	{
		unsigned char* pGray = (unsigned char*)gray->imageData + h*gray->widthStep;
		unsigned char* pRGB = (unsigned char*)rgb->imageData + h*rgb->widthStep;
		for (int w = 0; w<rgb->width; w++)
		{
			int s = pRGB[R] + pRGB[G] + pRGB[B];
			double r = (double)pRGB[R] / s;
			double g = (double)pRGB[G] / s;
			double Gup = Aup*r*r + Bup*r + Cup;
			double Gdown = Adown*r*r + Bdown*r + Cdown;
			double Wr = (r - 0.33)*(r - 0.33) + (g - 0.33)*(g - 0.33);
			if (g<Gup && g>Gdown && Wr>0.004)
			{
				*pGray = 255;
			}
			else
			{
				*pGray = 0;
			}
			pGray++;
			pRGB += 3;
		}
	}

}
// implementation of otsu algorithm  
// author: onezeros#yahoo.cn  
// reference: Rafael C. Gonzalez. Digital Image Processing Using MATLAB  
void cvThresholdOtsu(IplImage* src, IplImage* dst)
{
	int height = src->height;
	int width = src->width;

	//histogram  
	float histogram[256] = { 0 };
	for (int i = 0; i<height; i++)
	{
		unsigned char* p = (unsigned char*)src->imageData + src->widthStep*i;
		for (int j = 0; j<width; j++)
		{
			histogram[*p++]++;
		}
	}
	//normalize histogram  
	int size = height*width;
	for (int i = 0; i<256; i++)
	{
		histogram[i] = histogram[i] / size;
	}

	//average pixel value  
	float avgValue = 0;
	for (int i = 0; i<256; i++)
	{
		avgValue += i*histogram[i];
	}

	int threshold;
	float maxVariance = 0;
	float w = 0, u = 0;
	for (int i = 0; i<256; i++)
	{
		w += histogram[i];
		u += i*histogram[i];

		float t = avgValue*w - u;
		float variance = t*t / (w*(1 - w));
		if (variance>maxVariance)
		{
			maxVariance = variance;
			threshold = i;
		}
	}

	cvThreshold(src, dst, threshold, 255, CV_THRESH_BINARY);
}

void cvSkinOtsu(IplImage* src, IplImage* dst)//yCbCr  
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

void cvSkinOtsu_H(IplImage* src, IplImage* dst)//H通道上做分割，找到区域后再映射到S通道上继续做分割  
{
	assert(dst->nChannels == 1 && src->nChannels == 3);

	IplImage* HSV = cvCreateImage(cvGetSize(src), 8, 3);
	IplImage* H = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* S = cvCreateImage(cvGetSize(src), 8, 1);
	cvCvtColor(src, HSV, CV_BGR2HSV);
	cvSplit(HSV, H, S, 0, 0);

	cvThresholdOtsu(H, S);
	cvCopy(S, dst);
	cvReleaseImage(&H);
	cvReleaseImage(&HSV);
}

void cvSkinYUV(IplImage* src, IplImage* dst)
{
	IplImage* ycrcb = cvCreateImage(cvGetSize(src), 8, 3);
	//IplImage* cr=cvCreateImage(cvGetSize(src),8,1);  
	//IplImage* cb=cvCreateImage(cvGetSize(src),8,1);  
	cvCvtColor(src, ycrcb, CV_BGR2YCrCb);
	//cvSplit(ycrcb,0,cr,cb,0);  

	static const int Cb = 2;
	static const int Cr = 1;
	static const int Y = 0;

	//IplImage* dst=cvCreateImage(cvGetSize(_dst),8,3);  
	cvZero(dst);

	for (int h = 0; h<src->height; h++)
	{
		unsigned char* pycrcb = (unsigned char*)ycrcb->imageData + h*ycrcb->widthStep;
		unsigned char* psrc = (unsigned char*)src->imageData + h*src->widthStep;
		unsigned char* pdst = (unsigned char*)dst->imageData + h*dst->widthStep;
		for (int w = 0; w<src->width; w++)
		{
			if (pycrcb[Cr] >= 133 && pycrcb[Cr] <= 173 && pycrcb[Cb] >= 77 && pycrcb[Cb] <= 127)
			{
				memcpy(pdst, psrc, 3);
			}
			pycrcb += 3;
			psrc += 3;
			pdst += 3;
		}
	}
	//cvCopyImage(dst,_dst);  
	//cvReleaseImage(&dst);  
}

void cvSkinHSV(IplImage* src, IplImage* dst)
{
	IplImage* hsv = cvCreateImage(cvGetSize(src), 8, 3);
	//IplImage* cr=cvCreateImage(cvGetSize(src),8,1);  
	//IplImage* cb=cvCreateImage(cvGetSize(src),8,1);  
	cvCvtColor(src, hsv, CV_BGR2HSV);
	//cvSplit(ycrcb,0,cr,cb,0);  

	static const int V = 2;
	static const int S = 1;
	static const int H = 0;

	//IplImage* dst=cvCreateImage(cvGetSize(_dst),8,3);  
	cvZero(dst);

	for (int h = 0; h<src->height; h++)
	{
		unsigned char* phsv = (unsigned char*)hsv->imageData + h*hsv->widthStep;
		unsigned char* psrc = (unsigned char*)src->imageData + h*src->widthStep;
		unsigned char* pdst = (unsigned char*)dst->imageData + h*dst->widthStep;
		for (int w = 0; w<src->width; w++)
		{
			if (phsv[H] >= 7 && phsv[H] <= 29)
			{
				memcpy(pdst, psrc, 3);
			}
			phsv += 3;
			psrc += 3;
			pdst += 3;
		}
	}
	//cvCopyImage(dst,_dst);  
	//cvReleaseImage(&dst);  
}

void Skin_HSV_2(IplImage *initial, IplImage *distinction)
{
	CvScalar Avg, Sdv;
	IplImage *temp = cvCreateImage(cvGetSize(initial), 8, 3);
	cvCvtColor(initial, temp, CV_BGR2HSV);
	IplImage *h_img = cvCreateImage(cvGetSize(initial), 8, 1);
	IplImage *s_img = cvCreateImage(cvGetSize(initial), 8, 1);
	IplImage *v_img = cvCreateImage(cvGetSize(initial), 8, 1);

	double h_avg, s_avg, v_avg;
	double h_sdv, s_sdv, v_sdv;

	cvAvgSdv(temp, &Avg, &Sdv, 0);

	h_avg = Avg.val[0];
	s_avg = Avg.val[1];
	v_avg = Avg.val[2];
	//cout<<h_avg<<'\n'<<s_img<<'\n'<<v_img;  
	h_sdv = Sdv.val[0];
	s_sdv = Sdv.val[1];
	v_sdv = Sdv.val[2];


	cvSplit(temp, h_img, s_img, v_img, 0);
	/*cvShowImage("h_img1",h_img);
	cvShowImage("s_img1",s_img);
	cvShowImage("v_img1",v_img);*/
	int value = 0;
	for (int i = 0; i< h_img->height; i++)
	{
		for (int j = 0; j< h_img->width; j++)
		{
			value = cvGetReal2D(h_img, i, j);
			if ((value<(h_avg + h_sdv)) && (value>(h_avg - h_sdv)))
			{
				*(h_img->imageData + i*h_img->widthStep + j) = 0;
			}
			else
			{
				*(h_img->imageData + i*h_img->widthStep + j) = 255;
			}
		}
	}


	for (int i = 0; i< s_img->height; i++)
	{
		for (int j = 0; j< s_img->width; j++)
		{
			value = cvGetReal2D(s_img, i, j);
			if ((value<(s_avg + 0.5*s_sdv)) && (value>(s_avg - 0.5*s_sdv)))
			{
				*(s_img->imageData + i*s_img->widthStep + j) = 0;
			}
			else
			{
				*(s_img->imageData + i*s_img->widthStep + j) = 255;
			}
		}
	}

	for (int i = 0; i< v_img->height; i++)
	{
		for (int j = 0; j< v_img->width; j++)
		{
			value = cvGetReal2D(v_img, i, j);
			if ((value<(v_avg + v_sdv)) && (value>(v_avg - v_sdv)))
			{
				*(v_img->imageData + i*v_img->widthStep + j) = 0;
			}
			else

			{
				*(v_img->imageData + i*v_img->widthStep + j) = 255;
			}

		}
	}
	cvShowImage("h_img", h_img);
	/*cvShowImage("s_img",s_img);
	cvShowImage("v_img",v_img);*/
	cvAnd(h_img, s_img, distinction);
	//cvAnd(v_img,distinction,distinction);  

	/*cvShowImage("distinction",distinction);*/


	/*cvReleaseImage(&temp);*/
	cvReleaseImage(&h_img);
	cvReleaseImage(&s_img);
	cvReleaseImage(&v_img);
}

//void main()
//{
//
//	IplImage* img = cvLoadImage("original.jpg"); //随便放一张jpg图片在D盘或另行设置目录  
//	IplImage* dstRGB = cvCreateImage(cvGetSize(img), 8, 3);
//	IplImage* dstRG = cvCreateImage(cvGetSize(img), 8, 1);
//	IplImage* dst_crotsu = cvCreateImage(cvGetSize(img), 8, 1);
//	IplImage* dst_YUV = cvCreateImage(cvGetSize(img), 8, 3);
//	IplImage* dst_HSV = cvCreateImage(cvGetSize(img), 8, 3);
//	IplImage* dst_crotsu_H = cvCreateImage(cvGetSize(img), 8, 1);
//
//	IplImage* dst_HSV_2 = cvCreateImage(cvGetSize(img), 8, 1);
//
//	cvNamedWindow("inputimage", CV_WINDOW_AUTOSIZE);
//	cvShowImage("inputimage", img);
//	cvWaitKey(0);
//
//	SkinRGB(img, dstRGB);
//	cvNamedWindow("SkinRGB", CV_WINDOW_AUTOSIZE);
//	cvShowImage("SkinRGB", dstRGB);
//	///cvWaitKey(0);  
//	cvSkinRG(img, dstRG);
//	cvNamedWindow("cvSkinRG", CV_WINDOW_AUTOSIZE);
//	cvShowImage("cvSkinRG", dstRG);
//	//cvWaitKey(0);  
//	cvSkinOtsu(img, dst_crotsu);
//	cvNamedWindow("cvSkinOtsu", CV_WINDOW_AUTOSIZE);
//	cvShowImage("cvSkinOtsu", dst_crotsu);
//
//	cvSkinOtsu_H(img, dst_crotsu_H);
//	cvNamedWindow("cvSkinOtsu_H", CV_WINDOW_AUTOSIZE);
//	cvShowImage("cvSkinOtsu_H", dst_crotsu_H);
//	//cvWaitKey(0);  
//	cvSkinYUV(img, dst_YUV);
//	cvNamedWindow("cvSkinYUV", CV_WINDOW_AUTOSIZE);
//	cvShowImage("cvSkinYUV", dst_YUV);
//	//cvWaitKey(0);  
//	cvSkinHSV(img, dst_HSV);
//	cvNamedWindow("cvSkinHSV", CV_WINDOW_AUTOSIZE);
//	cvShowImage("cvSkinHSV", dst_HSV);
//
//
//	Skin_HSV_2(img, dst_HSV_2);
//	cvShowImage("cvSkinHSV2", dst_HSV_2);
//	cvWaitKey(0);
//
//}
