#include <iostream>

using namespace std;

struct Renderer{
    virtual void render_circle(float x, float y, float radius)=0;
};

struct RasterRenderer : Renderer{
    void render_circle(float x, float y, float radius) override{
        cout<<"Rasterizing a circle of radius "<<radius<<endl;
    }
};

struct VectorRenderer : Renderer{
    void render_circle(float x, float y, float radius) override{
        cout<<"Drawing a vector circle of radius "<<radius<<endl;
    }
};

struct Shape{
    protected:
    Renderer& renderer;
    Shape(Renderer& renderer) : renderer(renderer){}
    public:
    virtual void draw()=0;
    virtual void resize(float factor) = 0;

};

struct Circle : Shape{
    Circle(Renderer& renderer, float x, float y, float radius):Shape(renderer), x(x), y(y), radius(radius){}
    float x, y, radius;

    void draw() override{
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override{
        radius *= factor;
    }
};


int main(){

    RasterRenderer rr;
    Circle raster_circle{rr, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();

}