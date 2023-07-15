#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>

using namespace std;

enum class PointType{
    cartesian,
    polar,
};

struct Point{
    float x, y;
    
    Point(float a, float b, PointType type = PointType::cartesian){
        if (type == PointType::cartesian){
            x=a;
            y=b;
        }else{
            x=a*cos(b);
            y=a*sin(b);
        }
    }
};