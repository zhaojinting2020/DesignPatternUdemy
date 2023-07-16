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
    Contact(const Contact& other) : name(other.name), address(new Address{*other.address}){};

    friend ostream& operator<<(ostream& os, const Contact& contact){
        os<<"name "<<contact.name<<"street:"<<contact.address->street<<" city: "<<contact.address->city << " suite: "<<contact.address->suite;
        return os;
    }

};

struct EmployeeFactory{
    static unique_ptr<Contact> new_main_office_employee(const string& name, const int suite){
        static Contact p {"", new Address{"123 East Dr", "London", 0}}; // the address is default, name is not, 
                                                                        // this is a static prototype, we can keep using this prototype as
                                                                        // pre-defined contact
        return new_employee(name, suite, p); // then change the name, and the suite of the conract p
    }
private:
    static unique_ptr<Contact> new_employee(const string& name, int suite, const Contact& proto){
        auto result = make_unique<Contact>(proto);
        result->name = name;
        result->address->suite = suite;
        return result;
    }

};

int main(){
    auto john = EmployeeFactory::new_main_office_employee("john", 123);
    cout<<john<<endl;

}