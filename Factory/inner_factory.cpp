#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>
#include <iostream>

using namespace std;

// different method, but produce the same class

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
public:
    friend ostream& operator<<(ostream& os, const Point& point){
        os<<"x: "<<point.x<<" y: "<<point.y; // call the private Constructor
        return os;
    }

    class PointFactory{
        PointFactory(){}
        public:
        static Point NewCartesian(float x, float y){
            return {x, y}; // benefit of the inner PointFactory: can access the private constructor of the Point class
        }
        static Point NewPolar(float r, float theta){
            return {r*cos(theta), r*sin(theta)}; // call the private Constructor
        }
    };

private:
    float x, y;
};



int main(){
    auto p1 = Point::PointFactory::NewCartesian(3,4);
    auto p2 = Point::PointFactory::NewPolar(3,4);

    cout<<p1<<" "<<p2<<endl;
}

/**
The use of an inner factory, also known as a nested factory or a factory within a class, offers several benefits:
Encapsulation: By placing the factory inside the class it constructs, you encapsulate the creation logic within the class itself. 
This helps maintain a clear separation of concerns and keeps the creation logic closely tied to the class it creates. 
Other parts of the codebase don't need to be aware of the factory's existence or interact with it directly.

Access to private members: An inner factory has access to the private members of the enclosing class. 
This allows the factory to create instances using private constructors or access private initialization methods, providing more control over the construction process. 
This is particularly useful when certain construction logic or validation needs to be performed within the class itself.
**/