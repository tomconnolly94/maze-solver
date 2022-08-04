#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include <ImageLoader.h>
using namespace cv;


ImageLoader::ImageLoader(std::string newImagePath){
    imagePath = newImagePath;
}

std::vector<std::vector<bool>> ImageLoader::ReadPixels() {

    Mat image = imread(imagePath);
    Vec3b buf;

    std::vector<std::vector<bool>> mazeArray( image.rows, std::vector<bool> (image.cols, 0)); 

    std::cout << "image.rows: " << image.rows << std::endl;
    std::cout << "image.cols: " << image.cols << std::endl;

    for(int i = 0; i < image.rows; i++)
    {        
        for(int j = 0; j < image.cols; j++)
        {
            buf = image.at<Vec3b>(i,j);
            
            int x = image.at<Vec3b>(i, j)[0];//getting the pixel values//
            int y = image.at<Vec3b>(i, j)[1];//getting the pixel values//
            int z = image.at<Vec3b>(i, j)[2];//getting the pixel values//

            // std::cout << "i: " << i << ", j: " << j << "--" << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
            if((x + y + z) < 30)
                mazeArray[i][j] = false;
            else
                mazeArray[i][j] = true;
        }
    }
    return mazeArray;
}
