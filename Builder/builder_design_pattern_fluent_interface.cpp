#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <cstring>
using namespace std;

class HtmlBuilder;

class HtmlElement{
    
    friend class HtmlBuilder;
    string name, text;
    vector<HtmlElement> elements;
    
    const size_t indent_size = 2;
    
    HtmlElement(){}
    
public:
    HtmlElement(const string& name, const string& text): name(name), text(text){}
    
    string str(int indent=0) const{
        ostringstream oss;
        oss<<string(indent_size*indent, ' ')<<"<"<<name<<">"<<endl;
        if(text.size()>0){
            oss << string(indent_size*(indent+1), ' ')<<text<<endl;
        }
        
        for(const auto& e: elements){
            oss << e.str(indent + 1);
        }
        
        oss<<string(indent_size*indent, ' ')<<"</"<<name<<">"<<endl;
        return oss.str();
    }
    
    // usually we will prefer the reference api, 
    static HtmlBuilder build(string root_name);
    
    // static unique_ptr<HtmlBuilder> build(string root_name){
    //     return make_unique<HtmlBuilder>{root_name};
    // }

};

class HtmlBuilder{
    HtmlElement root;
    
public:
    HtmlBuilder(string root_name){
        root.name = root_name;
    }
    
    HtmlBuilder& add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return *this;
    }
    
    HtmlBuilder* add_child_2(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
        return this;
    }
    
    string str() const{
        return root.str();
    }
    
    HtmlElement build() {
        return root;
    }
    
    operator HtmlElement () const {
        return std::move(root);
    }
};

// we inplement the build function here because the HtmlBuilder class shoud be defined
HtmlBuilder HtmlElement::build(string root_name){
    return {root_name};
}

int main() {
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout<<builder.str()<<endl;
    
    auto builder2 = HtmlElement::build("ul").add_child("li", "hello1").add_child("li", "world1");
    
    cout<<builder2.str()<<endl;
    
    auto elem = HtmlElement::build("ul").add_child("hello2", "world2").build();

    return 0;
}


/**
The provided code demonstrates the idea of the Fluent Builder pattern, which is a creational design pattern used to construct complex objects step by step in a fluent and readable manner. Here's a summary of how the code implements the Fluent Builder pattern:

1. `HtmlElement` class:
   - Represents an HTML element with a name, text content, and a vector of child elements.
   - Provides a `str` method that generates a formatted string representation of the HTML element and its children.
   - Contains a `static` member function `build` that returns a `HtmlBuilder` object to start building an HTML element.

2. `HtmlBuilder` class:
   - Builds and constructs an HTML element.
   - Has a `root` member of type `HtmlElement` that represents the root HTML element being constructed.
   - Provides methods to add child elements to the root element, allowing chaining of method calls.
   - Offers a `str` method to generate a string representation of the constructed HTML element and its children.
   - Contains a `build` method that returns the constructed HTML element.
   - Overloads the conversion operator to convert the `HtmlBuilder` object to an `HtmlElement` object.

3. `main` function:
   - Creates an `HtmlBuilder` object named `builder` with the root name "ul" and adds two child elements.
   - Calls the `str` method on the `builder` object to print the string representation of the constructed HTML element.
   - Uses the `build` static function of `HtmlElement` to create a new `HtmlBuilder` object named `builder2` and adds two child elements.
   - Prints the string representation of the `builder2` object.
   - Uses the `build` static function of `HtmlElement` to create a new `HtmlBuilder` object and adds a child element.
   - Calls the `build` method to obtain the constructed HTML element and assigns it to `elem`.

The code demonstrates the fluent and readable style of constructing HTML elements using the `HtmlBuilder` class. Method chaining allows for concise and expressive code, resulting in code that closely resembles the structure of the desired HTML elements.
*/