#ifndef HUGHCIRCLE_H
#define HUGHCIRCLE_H
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "Comparator.h"

using namespace std;
using namespace cv;

class HughCircle
{
    public:
        HughCircle();
        ~HughCircle();

        // This function will load and validate the image and the image name.
        void loadImage(string fileName);

    private:
        // Private variables
        vector<Vec3f> _allCircles;
        Mat _originalImg;
        Mat _ProcessedImg;
        string _imageName;
        Comparator _sortCoordinates;

        // This function will take as a parameter a string containing a file path of a photo
        // and extract the name of the image from the file path e.g. if you
        // send C:/Users/John/Desktop/favoritePhoto.png into the function as a string, it will
        // return the string favoritePhoto (without the file extension)
        string getImageName(string filePath);

        // This function will apply filters and handle image analysis to find all the data we need to complete the partial circles.
        void processImage();

        // This function will draw the complete circles over the partial circles in an image.
        void drawCircleOverlay();

        // This function should handle all results, it will output data to the console screen and
        // also write the data (such as .bmp photos and .txt files) to the output folder.
        void outputResults();

        // Writes output data into the .txt file
        void writeToFile();

        // Overloads the output stream so we can write circle x, y coordinates and radius to a file, in correct format
        friend ostream& operator << (ostream& lhs, const Vec3i& rhs);
};

#endif // HUGHCIRCLE_H
