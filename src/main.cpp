#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImageLoader.h"

#include <stdio.h>

int main()
{
    std::string filename = "resources/input/maze-10x10.png";
    ImageLoader imageLoader(filename);
    std::vector<std::vector<bool>> mazeArray = imageLoader.ReadPixels();


    for(int i = 0; i < mazeArray.size(); i++){
        for(int j = 0; j < mazeArray[i].size(); j++)
        {
            std::cout << mazeArray[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

