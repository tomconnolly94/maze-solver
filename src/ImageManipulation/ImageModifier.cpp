#include <algorithm>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include "ImageModifier.h"

using namespace cv;

namespace ImageManipulation {

    /*
        Constructor for ImageModifier.
    */
    ImageModifier::ImageModifier(string imagePath)
    {
        _imagePath = imagePath;
    }

    /*
        DrawPathOnImage.
    */
    void ImageModifier::DrawPathOnImage(vector<GraphPosition> path)
    {
        Mat image = imread(_imagePath);
        Vec3b pixelColor(255,0,0);

        for(auto graphPosition : path)
            image.at<Vec3b>(cv::Point(graphPosition.first, graphPosition.second)) = pixelColor;

        bool check = imwrite("../resources/input/solved.png", image);
        if (check == false) {
            cout << "Saving the image, FAILED" << endl;
        }
    }
}