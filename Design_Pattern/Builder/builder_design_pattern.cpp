// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <cstring>
using namespace std;

struct HtmlElement{
    string name, text;
    vector<HtmlElement> elements;
    
    const size_t indent_size = 2;
    
    HtmlElement(){}
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
};

struct HtmlBuilder{
    HtmlElement root;
    HtmlBuilder(string root_name){
        root.name = root_name;
    }
    
    void add_child(string child_name, string child_text){
        HtmlElement e{child_name, child_text};
        root.elements.emplace_back(e);
    }
    
    string str() const{
        return root.str();
    }
};

int main() {
    // Write C++ code here
    // auto text = "hello";
    // string output;
    // output += "<p>";
    // output += text;
    // output += "<p>";
    
    // string words[] = {"hello", "world"};
    // ostringstream oss;
    // oss <<"<ul>";
    // for(auto w:words){
    //     oss<<" <li>"<<w<<"</li>";
    // }
    // oss<<"</ul>";
    // cout<<oss.str()<<endl;
    
    
    // cout<<output<<endl;
    
    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    cout<<builder.str()<<endl;

    return 0;
}

/**
 Certainly! The code you provided demonstrates the implementation of the Builder pattern. Here's a summary of the Builder pattern based on the code:

1. Purpose: The Builder pattern is a creational design pattern that allows for the construction of complex objects step by step. It separates the construction of an object from its representation, allowing the same construction process to create different representations.

2. Structure:
   - `HtmlBuilder`: This is the builder class that provides a higher-level interface for constructing HTML documents. It contains methods such as `add_child` to add child elements to the document and `str` to retrieve the HTML string representation of the document.
   - `HtmlElement`: This is the product class that represents an HTML element. It has properties such as `name`, `text`, and `elements`. It also provides a method `str` to convert the HTML element and its child elements into an HTML-formatted string.

3. Usage:
   - Create an instance of the builder class, `HtmlBuilder`, providing the necessary initial information, such as the root element name.
   - Use the builder's methods, such as `add_child`, to add child elements to the document.
   - Once all the elements are added, call the builder's `str` method to retrieve the HTML string representation of the document.

4. Benefits:
   - Allows the step-by-step construction of complex objects.
   - Provides a clear separation between the construction logic and the representation of the object.
   - Supports the creation of different representations of the same object construction process.

In your specific example, the `HtmlBuilder` class is responsible for constructing an HTML document using the builder pattern. It allows you to add child elements to the root element and retrieve the HTML string representation of the document. 
The `HtmlElement` struct represents an HTML element and provides a method to convert it and its child elements into an HTML-formatted string.
*/