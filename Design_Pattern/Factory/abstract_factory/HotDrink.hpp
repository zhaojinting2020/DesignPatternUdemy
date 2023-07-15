#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>
#include <iostream>

using namespace std;

// produce different kinds of derivated class

struct HotDrink{
    virtual ~HotDrink() = default;
    virtual void prepare(int volumn) = 0;
};

struct Tea : HotDrink{
    void prepare(int volumn) override{
        cout<<"Take a tea bag, boil water, pour"<<volumn<<"ml, add some lemon\n";
    }
};

struct Coffee : HotDrink{
    void prepare(int volumn) override{
        cout<<"Grind some beans, boil water, pour"<<volumn<<"ml, enjoy\n";
    }
};


