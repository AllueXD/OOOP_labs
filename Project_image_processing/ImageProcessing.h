#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cassert>
#include <algorithm >
#include <vector>

using namespace cv;

Mat get_intensity_diff (std::string& imgFirstName, std::string& imgLastName, std::string& imgCurrName) {
    assert (!imgFirstName.empty());
    assert (!imgLastName.empty());
    assert (!imgCurrName.empty());

    Mat imgFirst, imgCurr, imgLast;
    imgFirst = imread(imgFirstName);
    imgCurr = imread(imgCurrName);
    imgLast = imread(imgLastName);
    Mat imgRes = Mat::zeros(imgCurr.size(), CV_8UC3);

    for (int x = 0; x < imgCurr.rows; x++) {
        for (int y = 0; y < imgCurr.cols; y++) {
            imgRes.at<uchar>(y,x) = (imgFirst.at<uchar>(y,x) + imgLast.at<uchar>(y,x))/2 - imgCurr.at<uchar>(y,x);
        }
    }
    return imgRes;
}

Mat transform_to_bin (Mat img) {
    Mat imgGray = Mat::zeros(img.size(), CV_8UC3);
    Mat imgRes;
    cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    threshold(imgGray, imgRes, 125, 255, 0); //converting to binary
    return imgRes;
}

void median_filter (Mat& img) {
    for (int x = 1; x < img.rows-1; x += 2) {
        for (int y = 1; y < img.cols-1; y += 2) {
            std::vector<uchar> around_pix;
            for (int i = x - 1; i++; i < (x + 2)) {
                for (int j = y - 1; j++; j < (y + 2)) {
                    around_pix.push_back(img.at<uchar>(j,i));
                }
            }
            std::sort(around_pix.begin(), around_pix.end());
            uchar median = around_pix[5];
            for (int i = x - 1; i++; i < (x + 2)) {
                for (int j = y - 1; j++; j < (y + 2)) {
                    img.at<uchar>(j,i) = median;
                }
            }
        }
    }
}

void contours (Mat& img) {
    for (int x = 1; x < img.rows-1; x++) {
        for (int y = 1; y < img.cols-1; y ++) {
            std::vector<uchar> around_pix;
            for (int i = x - 1; i++; i < (x + 2)) {
                for (int j = y - 1; j++; j < (y + 2)) {
                    around_pix.push_back(img.at<uchar>(j,i));
                }
            }
            std::sort(around_pix.begin(), around_pix.end());
            uchar dark = 0;
            if (around_pix[0] == dark) {
                img.at<uchar>(y,x) = dark;
            } else {
                img.at<uchar>(y,x) = 255;
            }
        }
    }
}

//finding contours using cv methods
void find_contour_cv (std::string imgName, int red) {
    assert (!imgName.empty());
    Mat img;
    Mat img_gray;

     img = imread(imgName);

     cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
     cv::medianBlur(img_gray, img_gray, 5);
     Mat output = Mat::zeros(img.size(), CV_8UC3);

     std::vector<std::vector<Point> > contours;
     std::vector<Vec4i> hierarchy;
     findContours(output, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, Point(0, 0));

     Mat drawing = Mat::zeros(img.size(), CV_8UC3);

     for (int i = 0; i < contours.size(); i++) {
         Scalar color = Scalar(red, 0, 0);
         drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
     }
     imwrite("res.jpg", drawing);
}

//finding contours using own implemented methods
void find_contour_own (std::string curr, std::string first, std::string last, int red) {
    assert (!curr.empty());
    assert (!first.empty());
    assert (!last.empty());

    Mat img;

    img = get_intensity_diff(first, last, curr);
    img = transform_to_bin(img);

    median_filter(img);
    contours(img);

    imwrite("res.jpg", img);
}
#endif // IMAGEPROCESSING_H
