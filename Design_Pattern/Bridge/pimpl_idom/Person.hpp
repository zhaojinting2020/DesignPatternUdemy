// also known as the "Pointer to Implementation" idom
// to hide the implementation details of a class from its users by seperating the 
// public interface from the privare implementation

// benefit: achieve information hiding and encapsulation
//          minimize compile-time dependencies and reduce the impact of changes
//          to the implementation on the users of the class

#include <string>

class Person{
    public:
    std::string name;

    class PersonImpl;
    PersonImpl* impl;

    Person();
    ~Person();

    void greet();

    private:
};

