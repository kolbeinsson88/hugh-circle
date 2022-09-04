#include <iostream>
#include <string>
#include "HughCircle.h"

using namespace std;

///   ***** List of reference material used *****
///   http://docs.opencv.org/2.4/genindex.html
///   [Samples from the OpenCV library], opencv_source_code/samples/cpp/
///   http://www.cplusplus.com/reference/algorithm/sort/
///   http://www.cplusplus.com/reference/string/string/find/

int main()
{
    HughCircle img1, img2, img3, img4, img5, img6, img7, img8;

    // Loading images from the input folder located inside the project folder.
    // Once the images are loaded they will be processed and the results
    // stored in the output folder located inside our project folder.
    img1.loadImage("input/img1.PNG");

    img2.loadImage("input/img2.PNG");

    img3.loadImage("input/test1.PNG");

    img4.loadImage("input/test2.PNG");

    img5.loadImage("input/test3.PNG");

    img6.loadImage("input/test4.PNG");

    img7.loadImage("input/test5.PNG");

    img8.loadImage("input/test6.PNG");

    return 0;
}
