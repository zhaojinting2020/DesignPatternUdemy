
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

// mixin inheritance
// perfect forwarding


// to make sure that T is derivated from Shape
template <typename T> 
concept IsAShape = std::is_base_of<Shape, T>::value;

// this makes sure that the base class can not only be Shape, but also a derivated class of Shape
template <IsAShape T> 
struct ColorShape2 : T{
    string color;

    ColorShape2(){}

    template<typename ...Args>
    ColorShape2(const string& color, Args ...args) : T(std::forward<Args>(args)...), color(color){

    }

    string str() const override{
        ostringstream oss;
        oss << T::str() << " has the color " << color;
        return oss.str();
    }

};

template <IsAShape T> 
struct TransparentShape2 : T{
    uint8_t transparency;

    TransparentShape2(){}

    template<typename ...Args>
    TransparentShape2(const uint8_t transparency, Args ...args) : T(std::forward<Args>(args)...), transparency(transparency){

    }

    string str() const override{
        ostringstream oss;
        oss << T::str() << " has "  
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";
        return oss.str();
    }
};

int main(){
    ColorShape2<Circle> green_circle{"green", 5};
    cout<<green_circle.str()<<endl;

    TransparentShape2<ColorShape2<Square>> bis{0, "blue", 10};
    bis.color = "light blue";
    bis.side = 21;
    cout<< bis.str() <<endl;

    return 0;
}



