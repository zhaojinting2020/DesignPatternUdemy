#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>
#include <iostream>


using namespace std;

struct Address{
    string street, city;
    int suite;

    Address(const string& street, const string& city, int suite) : street(street), city(city), suite(suite){}
};

struct Contact{
    string name;
    Address* address;
    Contact(const string& name, Address* address):name(name), address(address){}
    Contact(const Contact& other) : name(other.name), address{new Address{*other.address}};

    friend ostream& operator<<(ostream& os, const Contact& contact){
        os<<"name "<<contact.name<<"street:"<<contact.address->street<<" city: "<<contact.address->city << " suite: "<<contact.address->suite;
        return os;
    }

};

int main(){
    Contact john{"John Doe", new Address{"123 East Dr", "London", 123}};
    // Contact jane{"Jane Smith", Address{"123 East Dr", "London", 103}};
    Contact jane = john;
    jane.name = "Jane Smith";
    jane.address.suite = 103;

    cout<<john<<"\n"<<jane<<endl;
}