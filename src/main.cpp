#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "ImageLoader.h"
#include "GraphBuilder.h"
#include "GraphNode.h"
#include "PathFinder.h"
#include "ImageModifier.h"


using namespace std;
using namespace Models;
using namespace GraphBuilding;
using namespace GraphSolving;
using namespace ImageManipulation;

int main()
{
    string filename = "../resources/input/maze-10x10.png";
    ImageLoader imageLoader(filename);
    vector<vector<bool>> mazeArray = imageLoader.ReadPixels();

    for(int i = 0; i < mazeArray.size(); i++){
        for(int j = 0; j < mazeArray[i].size(); j++)
        {
            cout << mazeArray[i][j] << " ";
        }
        cout << endl;
    }

    GraphBuilder graphBuilder(mazeArray);
    GraphEntryPoints graphEntryPoints = graphBuilder.BuildGraph();

    PathFinder pathFinder(graphEntryPoints);
    vector<GraphPosition> positionList = pathFinder.FindPath();

    ImageModifier imageModifier(filename);
    imageModifier.DrawPathOnImage(positionList);
}
