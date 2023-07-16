#include <string>
using namespace std;

struct Renderer{
    virtual string what_to_render_as() const = 0;
};

struct VectorRenderer : Renderer{
    string what_to_render_as() const{
        return "lines";
    }
};

struct RasterRenderer : Renderer{
    string what_to_render_as() const{
        return "pixels";
    }
};

struct Shape
{
    string name;
    Renderer& renderer;
    Shape(Renderer& renderer) : renderer(renderer){}
    virtual string str() const = 0;
};

struct Triangle : Shape
{
    Triangle(Renderer& renderer):Shape(renderer)
    {
        name = "Triangle";
    }
    
    string str() const{
        return "Drawing " + name + " as " + renderer.what_to_render_as();
    }
    
};

struct Square : Shape
{
    Square(Renderer& renderer) : Shape(renderer)
    {
        name = "Square";
    }
    
    string str() const{
        return "Drawing " + name + " as " + renderer.what_to_render_as();
    }
};

struct VectorSquare : Square
{
    string str() const
    {
        return "Drawing " + name + " as lines";
    }
};

struct RasterSquare : Square
{
    string str() const
    {
        return "Drawing " + name + " as pixels";
    }
};

/**
Yes, in the Bridge design pattern, there will always be an "Implementor" component, which represents the implementation of the abstraction. The Implementor provides the specific operations or behaviors that are delegated by the Abstraction.

The Bridge pattern separates the abstraction and implementation into separate class hierarchies, allowing them to vary independently. The Abstraction defines the high-level interface and relies on the Implementor to provide the lower-level implementation details.

The Implementor is typically an abstract base class or interface that declares the common operations that the concrete implementations must provide. It acts as a bridge between the Abstraction and the concrete implementation classes.

By introducing the Implementor, the Bridge pattern allows the Abstraction and Implementor to evolve and vary independently. You can have multiple Implementor classes that provide different implementations of the operations defined by the Implementor interface. The Abstraction can then delegate the implementation details to the appropriate Implementor at runtime.

So, to summarize, the Implementor is an essential component in the Bridge design pattern, facilitating the decoupling and separation of abstraction and implementation.
**/

/**
 * To clarify, the Abstraction and its derived classes should have constructors that accept a reference to the Implementor as a parameter. 
 * This ensures that the reference is initialized during object creation. 
 * Without proper initialization, the Abstraction would not be able to delegate operations to the Implementor, which would break the Bridge pattern.
*/