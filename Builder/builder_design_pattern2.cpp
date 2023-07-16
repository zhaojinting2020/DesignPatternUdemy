#include <string>
using namespace std;

class House {
public:
    void setRoof(const string& roof) { /* Set roof */ }
    void setRooms(int numRooms) { /* Set number of rooms */ }
    void setGarage(bool hasGarage) { /* Set presence of a garage */ }
    // ... Other methods and properties of House
};

class HouseBuilder {
public:
    virtual void buildRoof() = 0;
    virtual void buildRooms() = 0;
    virtual void buildGarage() = 0;
    virtual House* getHouse() = 0;
};

class ConcreteHouseBuilder : public HouseBuilder {
private:
    House* house;

public:
    ConcreteHouseBuilder() {
        house = new House();
    }

    void buildRoof() override {
        house->setRoof("Concrete roof");
    }

    void buildRooms() override {
        house->setRooms(4);
    }

    void buildGarage() override {
        house->setGarage(true);
    }

    House* getHouse() override {
        return house;
    }
};

class WoodenHouseBuilder : public HouseBuilder {
private:
    House* house;

public:
    WoodenHouseBuilder() {
        house = new House();
    }

    void buildRoof() override {
        house->setRoof("Wooden roof");
    }

    void buildRooms() override {
        house->setRooms(2);
    }

    void buildGarage() override {
        house->setGarage(false);
    }

    House* getHouse() override {
        return house;
    }
};


class HouseDirector {
public:
    House* constructHouse(HouseBuilder* builder) {
        builder->buildRoof();
        builder->buildRooms();
        builder->buildGarage();
        return builder->getHouse();
    }
};

int main() {
    HouseDirector director;
    
    ConcreteHouseBuilder concreteBuilder;
    House* concreteHouse = director.constructHouse(&concreteBuilder);

    WoodenHouseBuilder woodenBuilder;
    House* woodenHouse = director.constructHouse(&woodenBuilder);

    // Use the constructed houses
    // ...

    delete concreteHouse;
    delete woodenHouse;

    return 0;
}
