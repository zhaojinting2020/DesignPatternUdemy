#pragma once
#include <string>

using namespace std;


class PersonAddressBuilder: public PersonBuilderBase{
    typedef PersonAddressBuilder Self;

    public:
    PersonAddressBuilder(Person& person) : PersonBuilderBase(person){}

    Self& at(std::string street_address){
        person.street_address = street_address;
        return *this; // the core of the builder pattern is to return *this after build some element of the main class
    }

    Self& with_postcode(std::string post_code){
        person.post_code = post_code;
        return *this;
    }

    Self& in(std::string city){
        person.city = city;
        return *this;
    }

};

/**
 * The Builder pattern is useful when the construction of an object involves multiple steps or when the object creation process needs to be flexible. 
 * By separating the construction logic from the actual object creation, the Builder pattern promotes a clear and intuitive way to construct objects.
*/