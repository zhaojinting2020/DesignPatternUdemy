#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>
#include <iostream>

using namespace std;

enum class PointType{
    cartesian,
    polar,
};

class Point{
public:
    //friend class PointFactory; // violate the Open Close Principle, for example, 
                               // if the NewPolar function changes, if will affect the result of the << function, 
                               // and affect the result of the output
    Point(float x, float y):x(x), y(y){}

    friend ostream& operator<<(ostream& os, const Point& point){
        os<<"x: "<<point.x<<" y: "<<point.y; // call the private Constructor
        return os;
    }

private:
    float x, y;
};

class PointFactory{
    PointFactory(){}
    public:
    static Point NewCartesian(float x, float y){
        return {x, y};
    }
    static Point NewPolar(float r, float theta){
        return {r*cos(theta), r*sin(theta)}; // call the private Constructor
    }
};


int main(){
    auto p1 = PointFactory::NewCartesian(3,4);
    auto p2 = PointFactory::NewPolar(3,4);

    cout<<p1<<" "<<p2<<endl;
}