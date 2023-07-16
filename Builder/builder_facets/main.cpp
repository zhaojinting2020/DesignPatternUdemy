#include <iostream>
#include <cstring>
#include <memory>
#include <string>

#include "Person.hpp"
#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"

using namespace std;

int main(){
    Person p = Person::create()
    .lives().at("123 London Road").with_postcode("SW1 1GB").in("London")
    .works().at("PragmaSoft").as_a("Consultant").earning(10e6); //implict conversion from personBuilderBase to Person


    cout<<p<<endl;

    return 0;
}