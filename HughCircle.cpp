#include "HughCircle.h"

HughCircle::HughCircle()
{
    _imageName = "";
    _originalImg = Mat::zeros(3,3, CV_8UC1);
    _ProcessedImg = Mat::zeros(3,3, CV_8UC1);
}

HughCircle::~HughCircle()
{
    destroyAllWindows();
}

void HughCircle::loadImage(string filePath)
{
    // Loads a colored .png image. The images may contain multiple circles
    _originalImg = imread(filePath, CV_LOAD_IMAGE_COLOR);
    _ProcessedImg = imread(filePath, CV_LOAD_IMAGE_COLOR);

    if (_ProcessedImg.empty() || _originalImg.empty())
    {
        cout << "Image not found!" << endl;
        return exit(1);
    }

    // We want the image name, but without the file path and the file extension so we use the getImageName() function.
    // The function can take as a parameter a string such as C:\\Users\\kolbeinsson\\Desktop\\img2.png and returns img2, the name of the image
    _imageName = getImageName(filePath);

    // will process the image we just loaded. Filter it and scan it for incomplete circles
    processImage();
}

string HughCircle::getImageName(string filePath)
{
    string name = filePath;
    // Remove the file path from the string/image name
    size_t foundSlash = name.find_last_of("\\/");
    if (string::npos != foundSlash)
    {
        name.erase(0, foundSlash + 1);
    }

    // Separate the file extension from the image name and returns it without directory file path/extension.
    size_t indexOfExt = name.find_last_of(".");
    string imgName = name.substr(0, indexOfExt);

    return imgName;
}

void HughCircle::processImage()
{
    // Convert image to grayscale
    Mat gray;
    cvtColor(_ProcessedImg, gray, CV_BGR2GRAY);

    // We use Hugh transform to identify the circles in the image
    // We use Gaussian blur to "smooth" the image, to avoid noise, and reduce probability of false circle detection.
    // The key parameter is parameter 2 or the accumulator threshold (param2 = 30),
    // the smaller it is the more false circles will be detected. If it is too high then to few circles are detected.
    GaussianBlur(gray, gray, Size(5, 5), 0);
    HoughCircles(gray, _allCircles, HOUGH_GRADIENT, 1, gray.rows/8, 100, 30, 0, 0);

    // The identified circles are put into the circle vector (sorted in ascending order by x coordinate)
    sort(_allCircles.begin(), _allCircles.end(), _sortCoordinates.compX);

    // Once we have found incomplete circles and their coordinates and radius, we can draw the overlay of a completed circle
    drawCircleOverlay();
}

void HughCircle::drawCircleOverlay()
{
    // The for loop iterates through each circle stored in our vector.
    // The scalar color is green
    // The line thickness is 1, which is to say, small thickness
    // LINE_AA corresponds to an Anti-Aliased line
    int it = 1;
    cout << "***** Completing partial circles in  " << _imageName << " *****" << endl << endl;
    for(size_t i = 0; i < _allCircles.size(); i++)
    {
        Vec3i currCircle = _allCircles[i];
        Point center;

        // x and y coordinates of the center
        center.x = currCircle[0];
        center.y = currCircle[1];

        // radius
        int radius = currCircle[2];

        // Draws the overlay for the original circle in green
        circle(_ProcessedImg, center, radius, Scalar(0,255,0), 1, LINE_AA);

        // The line below draws the center of the circle, you can uncomment it if you want to include it
        // circle(image, center, 2, Scalar(0,255,0), 1, LINE_AA);

        // Write results to screen (x, y coordinates along with radius)
        cout << "Circle " << it++ << endl;
        cout << "x coordinate : " << center.x << endl;
        cout << "y coordinate : " << center.y << endl;
        cout << "radius : " << radius << endl << endl;
    }
    outputResults();
}

void HughCircle::outputResults()
{
    // This code converts the image to bitmap then saves it in the output folder.
    // The saved photo shows the original circle with a overlay of completed circle in a different color
    Mat bitmap;
    _ProcessedImg.convertTo(bitmap, CV_8UC3);
    string outputFile = "output/" + _imageName + "-output.bmp";
    imwrite(outputFile, bitmap);

    // writes results, containing x, y coordinates and radius (sorted by x coordinates asc) to a output.txt file, in the output folder.
    writeToFile();

    // Show the image with the circle overlay and also the original image in console window
    cvNamedWindow("Original Image", CV_WINDOW_NORMAL);
    imshow("Original Image", _originalImg);
    cvNamedWindow("Circle Overlay", CV_WINDOW_NORMAL);
    imshow("Circle Overlay", _ProcessedImg);
    waitKey(0);
}

ostream& operator << (ostream& lhs, const Vec3i& rhs)
{
    lhs << rhs[0] << "\t";
    lhs << rhs[1] << "\t";
    lhs << rhs[2] << endl;
    return lhs;
}

void HughCircle::writeToFile()
{
    ofstream textFile;
    string outputFile = "output/" + _imageName + "-output.txt";
    textFile.open(outputFile);
    for (size_t i = 0; i < _allCircles.size(); i++)
    {
        if(textFile)
        {
            Vec3i currentCircle = _allCircles[i];
            textFile << currentCircle;
        }
    }
    textFile.close();
}
