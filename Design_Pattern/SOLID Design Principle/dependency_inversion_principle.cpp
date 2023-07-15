/**
The given code demonstrates the Dependency Inversion Principle by decoupling high-level and low-level modules through the use of an abstract interface.

In this code, we have two modules: the low-level module (`Relationships`) and the high-level module (`Research`). The high-level module depends on the abstraction (`RelationshipBrowser`) rather than concrete implementations.

The `RelationshipBrowser` is an abstract interface that defines a contract for finding relationships between people. It declares a single method `find_all_children_of` that takes a person's name as input and returns a vector of all their children.

The `Relationships` class represents the low-level module. It implements the `RelationshipBrowser` interface and maintains a collection of relationships as tuples in its `relations` vector. It provides methods to add parent-child relationships to the collection and implements the `find_all_children_of` method to retrieve all the children of a given person.

The `Research` class represents the high-level module. It takes a reference to a `RelationshipBrowser` object in its constructor. This allows it to work with any object that implements the `RelationshipBrowser` interface. In the constructor, it uses the `find_all_children_of` method to find all the children of a person named "John" and outputs the results.

By depending on the abstract interface `RelationshipBrowser`, the `Research` class is not tightly coupled to the specific implementation details of the low-level module. It can work with any implementation of `RelationshipBrowser`, promoting flexibility, extensibility, and easier testing.

This adherence to the Dependency Inversion Principle allows for loose coupling and facilitates the swapping of different implementations of the `RelationshipBrowser` interface without affecting the high-level module. It enables the code to be more modular, maintainable, and adaptable to future changes or additions.
*/


#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
using namespace  std;

enum class Relationship{
    parent,
    child,
    sibling,
};

struct Person{
    string name;
};

struct RelationshipBrowser{ // abstraction
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser{ // low-level
    vector<tuple<Person, Relationship, Person>> relations;
    
    void add_parent_and_child( const Person& parent, const Person& child){
        relations.push_back(std::make_tuple(parent, Relationship::parent, child));
        relations.push_back(std::make_tuple(child, Relationship::child, parent));
    }
    
    vector<Person> find_all_children_of(const string& name) override{
        vector<Person> result;
        for (auto&& [first, rel, second]: relations){
            if(first.name == name && rel == Relationship::parent){
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research{ // high-level

    Research(RelationshipBrowser& browser){

        for( auto& child : browser.find_all_children_of("John")){
            cout<<"John has a child named "<<child.name<<endl;
        }
    }
    // Research(Relationships& relationships){
    //     auto& relations = relationships.relations;
        
    //     for( auto&& [first, rel, second] : relations){
    //         if(first.name == "John" && rel == Relationship::parent){
    //             cout<<"John has a child named "<<second.name<<endl;
    //         }
    //     }
    // }
};

int main() {
    // Write C++ code here
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};
    
    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);
    
    Research _(relationships);


    return 0;
}

/**
Deciding which module is low level and which is high level depends on the specific context and the perspective of the system design. However, there are a few general guidelines that can help in making this determination:

1. Abstraction Level: Low-level modules typically deal with specific implementation details, such as data storage, hardware interaction, or low-level algorithms. They operate at a lower level of abstraction and focus on the inner workings of the system.

2. Complexity: Low-level modules often have a higher degree of complexity due to their involvement in detailed operations. They may require precise management of resources, handle low-level optimizations, or have intricate data structures.

3. Reusability: High-level modules tend to be more reusable and independent of specific implementations. They provide higher-level functionalities and encapsulate complex operations, making them easier to integrate into different contexts or switch between implementations.

4. Dependencies: High-level modules typically depend on low-level modules for their implementation details. They rely on the services or functionalities provided by low-level modules without needing to know the intricate details of their implementation.

5. System Perspective: The perspective from which the system is viewed can also influence the categorization. For example, a module that is considered low level from a higher-level system's perspective might be considered high level in the context of a lower-level subsystem.

It's important to note that the classification of modules as low level or high level is not absolute and can vary based on the specific requirements, design goals, and architectural choices of a system. The goal is to establish a clear separation of concerns and create modular components that are cohesive, reusable, and maintainable.
*/