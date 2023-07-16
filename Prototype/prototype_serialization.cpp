#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>
#include <iostream>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>


using namespace std;
using namespace boost::archive;

struct Address{
    string street, city;
    int suite;

    Address(const string& street, const string& city, int suite) : street(street), city(city), suite(suite){}
};

struct Contact{
    string name;
    Address* address;

    Contact(){}
    Contact(const string& name, Address* address):name(name), address(address){}
    Contact(const Contact& other) : name(other.name), address(new Address{*other.address}){};

    ~Contact(){delete address;}

    friend ostream& operator<<(ostream& os, const Contact& contact){
        os<<"name "<<contact.name<<"street:"<<contact.address->street<<" city: "<<contact.address->city << " suite: "<<contact.address->suite;
        return os;
    }

    private:
    friend class serialization::access;

    template <class archive>
    void serialize(archive& ar, const unsigned version){
        ar& street;
        ar& city;
        ar& suite;
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
    auto clone = [](const Contact& contact){
        ostringstream oss;
        archive::text_oarchive oa(oss);
        oa << contact;
        string s = oss.str();
        cout<<s<<endl;

        istringstream iss(s);
        archive::text_iarchive ia(iss);

        ia >> result;

        return result;
    };

    auto john = EmployeeFactory::new_main_office_employee("John", 123);
    auto jane = clone(*john);

    /**
     * The deserialized Contact object will have its own distinct memory addresses for both the Contact instance and the Address instance. 
     * The deserialized Contact object is a separate object in memory from the original object.
    */

    cout<<*john << endl << jane << endl;

}

/**
 * basically there are two kinds of way to clone a prototype, 
 * one is to implement your own deep copy functionality
 * 
 * second is to serialize and deserialize, this way can avoid a lot of self defined construction function, so it's a better solution
*/