
#pragma once

#include <iostream>
#include <string>

using namespace std;

class PersonBuilder;

class Person{
    // address
    std::string street_address, post_code, city;
    
    // employment
    std::string company_name, position;
    int annual_income{0};

    Person(){
        cout<<"Person created\n";
    }

public:
    ~Person(){
        cout<<"Person destryed\n";
    }

    Person(Person&& other):
        street_address{move(other.street_address)},
        post_code{move(other.post_code)},
        city{move(other.city)},
        company_name{move(other.company_name)},
        position{move(other.position)},
        annual_income{move(other.annual_income)}{}

    Person& operator=(Person&& other){
        if(this==&other){
            return *this;
        }
        street_address=move(other.street_address);
        post_code=move(other.post_code);
        city=move(other.city);
        company_name=move(other.company_name);
        position=move(other.position);
        annual_income=move(other.annual_income);
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person);

    static PersonBuilder create();
    
    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};