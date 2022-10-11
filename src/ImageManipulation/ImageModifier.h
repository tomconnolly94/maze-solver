#ifndef IMAGEMODIFIER_H
#define IMAGEMODIFIER_H

#include <string>
#include <vector>

#include "GraphPosition.h"

using namespace std;
using namespace Models;

namespace ImageManipulation
{

    class ImageModifier {
    private:
        string _imagePath = "";
    public:
        ImageModifier(string imagePath);
        void DrawPathOnImage(vector<GraphPosition> path);
    };
}

#endif