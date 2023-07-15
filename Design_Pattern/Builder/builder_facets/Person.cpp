// Online C++ compiler to run C++ program online

using namespace std;

#include "Person.hpp"
#include "PersonBuilder.hpp"

PersonBuilder Person::create(){
    return PersonBuilder();
}

ostream& operator <<(ostream& os, const Person& person){
        os  <<person.street_address<<" "
            <<person.post_code<<" "
            <<person.city<<" "
            <<person.company_name<<" "
            <<person.position<<" "
            <<person.annual_income<<endl;
        return os;
    }