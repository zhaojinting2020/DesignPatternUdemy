// should be able to substitue any derivated class into any location where a base class is being used.
// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <fstream>
using namespace  std;

class Rectangle{
    protected:
    int width, height;
    public:
    Rectangle(int width, int height):width(width), height(height){
    }
    int getwidth() const{
        return width;
    }
    int getheight() const{
        return height;
    }
    virtual void setwidth(int width){
        Rectangle::width = width;
    }
    virtual void setheight(int height){
        Rectangle::height = height;
    }
    
    int area() const{
        return width*height;
    }
    
};

class Square : public Rectangle {
    public:
    Square(int size):Rectangle(size, size){}
    
    void setwidth(int width) override{
        this->width = this->height = width;
    }
    void setheight(int height) override{
        this->width = this->height = height;
    }
};
// break the liskov substitution principle 
// solution: use a factory to create rectangle or square
struct RectangleFactory{
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};

void process(Rectangle& r){
    int w = r.getwidth();
    r.setheight(10);
    cout<<"expected area = " << (w*10)
        <<", got " << r.area() << endl;
}

int main() {
    // Write C++ code here
    Rectangle r(3, 4);
    Square s(3);
    
    process(r);
    process(s);

    return 0;
}

/**
 * The code provided demonstrates the violation of the Liskov Substitution Principle and proposes a solution using a factory to address the issue. Let's break down the code and explain how a factory can help:

1. **Rectangle and Square Classes**: The code defines two classes, `Rectangle` and `Square`. `Rectangle` is a base class that represents a rectangle with a width and height, while `Square` is a derived class that represents a square with equal sides. The `Square` class inherits from `Rectangle`, which is a violation of the Liskov Substitution Principle because substituting a `Rectangle` object with a `Square` object can lead to unexpected behavior.

2. **Liskov Substitution Principle Violation**: The `Square` class overrides the `setwidth` and `setheight` methods of the base `Rectangle` class to ensure that both the width and height of a `Square` object are always the same. However, this violates the Liskov Substitution Principle because it changes the behavior of the base class. In the base class, modifying the width and height independently is allowed, but in the derived class, modifying one side affects the other side.

3. **RectangleFactory**: To solve the Liskov Substitution Principle violation, the code introduces a `RectangleFactory` struct that serves as a factory to create instances of `Rectangle` or `Square`. By using a factory, the responsibility of creating objects is separated from the client code.

4. **Factory Methods**: The `RectangleFactory` struct provides two static methods: `create_rectangle` and `create_square`. These methods are responsible for creating `Rectangle` and `Square` objects, respectively. By encapsulating the object creation logic in the factory, the client code no longer directly instantiates `Rectangle` or `Square` objects.

5. **process Function**: The `process` function takes a reference to a `Rectangle` object and demonstrates the Liskov Substitution Principle violation. It assumes that the height of the rectangle is set to 10, regardless of the original width. It calculates the expected area based on the original width and height of the rectangle and compares it with the actual area. However, when a `Square` object is passed to this function, the overridden behavior in the `Square` class leads to incorrect results.

By using a factory, the code aims to solve the Liskov Substitution Principle violation by centralizing the creation of objects. The factory provides methods that create the appropriate objects (`Rectangle` or `Square`) based on the desired dimensions. This way, the client code can work with the base `Rectangle` class and rely on the factory to ensure correct object creation, maintaining the expected behavior of the base class and its derived classes.
*/