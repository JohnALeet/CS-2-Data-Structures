#include "point.h"

//Constructor
points::Point::Point(int X, int Y, points::Point* closestPoint)
{

    x = X;
    y = Y;    
    nearestPoint = closestPoint;

}
//Destructor
points::Point::~Point()
{
    //Not needed for this lab

}

//Getters
int points::Point::getX()
{


    return x;
}

int points::Point::getY()
{
    return y;
}

points::Point* points::Point::getNearestPoint()
{
    return nearestPoint;
}

points::Point* points::Point::calcNearestPoint(Point* pointList[], unsigned long arrSize)
{
    if (arrSize== 0){return nullptr;}
    
    Point* minNeighbor = nullptr;
    double minDistance = 0.0;

    //Find first valid neighbor.
    for (unsigned long i = 0; i < arrSize; i++)
    {
        if (pointList[i] != nullptr && pointList[i] != this)
        {
            minNeighbor = pointList[i];
            minDistance = distPoints(*minNeighbor);
            break;
        }
    } 
    //Looks at all neighbors, find the closest one and update nearestPoint.
    if (minNeighbor == nullptr)
    {
        nearestPoint = nullptr;
        return nullptr;
    }
    //Visits all indices from 0 to arrSize - 1.
    for (unsigned long i = 0; i < arrSize; i++){
        //Skips null and itself.
        if (pointList[i] != nullptr && pointList[i] != this)
        {
            double d = distPoints(*pointList[i]); // double d lol
            //Compares the distance to the current minimum.
            if (d < minDistance){

                minDistance = d;
                minNeighbor = pointList[i];

            }

        }


    }
    
    nearestPoint = minNeighbor;
    return minNeighbor;
}

//Setters
void points::Point::setX(int newVal)
{
    x = newVal;
}

void points::Point::setY(int newVal)
{
    y = newVal;
}

void points::Point::setNearestPoint(Point* newNearestPoint)
{
    nearestPoint = newNearestPoint;
}

double points::Point::distPoints(Point& point)
{
    int dx = x - point.getX();
    int dy = y - point.getY();

    int dxSquared = dx * dx;
    int dySquared = dy * dy;

    double sum = dxSquared + dySquared;
    double dist = sqrt(sum);

    return dist;
}