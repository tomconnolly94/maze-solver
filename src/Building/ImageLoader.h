#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>
#include <vector>

class ImageLoader {
private:
    std::string imagePath = "";
public:
    ImageLoader(std::string imagePath);
    std::vector<std::vector<bool>> ReadPixels();
};

#endif