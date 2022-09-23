#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <string>
#include <vector>

using namespace std;

class ImageLoader {
private:
    string imagePath = "";
public:
    ImageLoader(string imagePath);
    vector<vector<bool>> ReadPixels();
};

#endif