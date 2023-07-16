
#pragma once


using namespace std;

#include "Person.hpp"

class PersonJobBuilder;
class PersonAddressBuilder;


class PersonBuilderBase{
    
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person) : person{person}{}
public:
    operator Person () const{
        // allow inplicit conversion from PersonBuilderBase object to Person object
        return std::move(person);
    }
    
    PersonAddressBuilder lives() const; // create two kinds of builders to handle different type of input information
    PersonJobBuilder works() const; // build the job information
};


class PersonBuilder : public PersonBuilderBase{
    Person p;
    public:
    PersonBuilder(): PersonBuilderBase(p){}
};
