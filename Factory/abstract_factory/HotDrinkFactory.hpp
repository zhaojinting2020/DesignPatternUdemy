#include <memory>
#include <vector>
#include <map>
#include <functional>

#include "HotDrink.hpp"

struct HotDrinkFactory{ // abstract factory
    virtual unique_ptr<HotDrink> make() const=0;
};

struct TeaFactory : HotDrinkFactory{
    unique_ptr<HotDrink> make() const override{
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory{
    unique_ptr<HotDrink> make() const override{
        return make_unique<Coffee>();
    }
};


class DrinkFactory{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;

    public:
    DrinkFactory(){
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name){
        auto drink = hot_factories[name]->make();
        drink->prepare(200); // set volumn to 200 by default
        return drink;
    }
};

class DrinkWithVolumnFactory{
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumnFactory(){
        factories["tea"] = []{
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };
        factories["coffee"] = []{
            auto coffee = make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
    }

    unique_ptr<HotDrink> make_drink(const string& name){
        return factories[name]();
    }
};

int main(){
    DrinkFactory df;
    auto c = df.make_drink("coffee");

    return 0;
}
