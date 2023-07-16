#ifndef __DYNAMIC_DECORATOR_H__
#define __DYNAMIC_DECORATOR_H__

#include <string> 
#include <sstream>
#include <iostream>

using namespace std;


struct Shape{
    virtual string str() const=0;
};

struct Circle : Shape{
    float radius;
    Circle() {}

    Circle(float radius) : radius(radius){}

    void resize(float factor){
        radius = radius*factor;
    }

    string str() const override{
        ostringstream oss;
        oss<<"A circle of radius "<<radius;
        return oss.str();
    }
};

struct Square : Shape{
    float side;

    Square(){}
    Square(float side) : side(side){}

    string str() const override{
        ostringstream oss;

        oss<<"A Square with side "<<side;
        return oss.str();
    }
};

struct ColorShape : Shape{
    Shape& shape;       
    string color;

    ColorShape(Shape& shape, const string& color):shape(shape), color(color){}

    string str() const override{
        ostringstream oss;
        oss << shape.str() <<" has the color "<<color;
        return oss.str();
    }

};

struct TransparentShape : Shape{
    Shape& shape;
    uint8_t transparency;


    TransparentShape(Shape& shape, uint8_t transparency) : shape(shape), transparency(transparency){}

    string str() const override{
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency)/255.f * 100.f
            << "% transparency";

        return oss.str();
    }
};


int main(){

    Square square{5};
    ColorShape red_square{square, "red"};
    cout << square.str() << endl << red_square.str() << endl;

    TransparentShape my_square{red_square, 51};
    cout<<my_square.str()<<endl;

    Circle circle{5};
    ColorShape red_circle{circle, "red"};
    cout << circle.str() << endl << red_circle.str() << endl;

    // red_circle can not be resized anymore cause class Shape doesn't have that interface
    return 0;
}
#endif // __DYNAMIC_DECORATOR_H__