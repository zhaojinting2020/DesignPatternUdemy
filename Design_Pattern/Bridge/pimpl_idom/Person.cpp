#include "Person.hpp"
#include <iostream>

//cause these implementations are in cpp file, so 
//we never expose them to the API 

//Implementation
class Person::PersonImpl{
    public:
    void greet(Person* p);
};

Person::Person() : impl(new PersonImpl){}

Person::~Person(){
    delete impl;
}

void Person::greet(){
    impl->greet(this);
}