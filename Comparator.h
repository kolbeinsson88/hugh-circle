#ifndef COMPARATOR_H
#define COMPARATOR_H
#include <string>

using namespace cv;

// This class is used by our sort function, they "teach" our compiler how to compare two Vec3f circles.
// All the circles we find in the input images will be sorted in ascending order by x coordinate of the circle before the are
// written to the output/output.txt file
class Comparator
{
    public:
        Comparator(){}

        struct compXCoord
        {
            bool operator() (Vec3f i, Vec3f j)
            {
                return ((i[0]) < (j[0]));
            }
        }compX;
};

#endif
