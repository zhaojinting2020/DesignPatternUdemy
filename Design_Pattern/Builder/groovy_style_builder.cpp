// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <cstring>
using namespace std;

struct Tag{
    string name, text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;
    
    friend std::ostream& operator<<(std::ostream& os, const Tag& tag){
        os <<"<" <<tag.name;
        
        for(const auto& att: tag.attributes){
            os<<" "<<att.first<<" = "<<att.second<<"/";
        }
        
        if (tag.children.size() == 0 && tag.text.length()==0){
            os<<"/>"<<std::endl;
        }else{
            os<<">"<<std::endl;
            if(tag.text.length()){
                os<<tag.text<<std::endl;
            }
            for(const auto& child : tag.children){
                os<<child;
            }
            os<<"</"<<tag.name<<">"<<std::endl;
        }
        
        return os;
    }
    
    protected:
    public:
    Tag(const string& name, const string& text) : name(name), text(text){}
    Tag(const string& name, const vector<Tag>& children):name(name), children(children){}
};
    
struct P : Tag{
    P(const string& text) : Tag("P", text){}
    P(initializer_list<Tag> children):Tag("p", children){}
};

struct IMG : Tag{
    // prevent automatical convertion during object initialization
    explicit IMG(const string& url) : Tag{"img", ""}{
        attributes.emplace_back(make_pair("src", url));
    }
};


int main() {
    cout<<P{IMG{"http"}}<<endl;

    return 0;
}

/**
The provided code demonstrates the usage of a Groovy-style builder pattern in C++. The code defines a hierarchy of classes representing HTML tags and demonstrates their construction using a fluent and expressive syntax.

The code includes the following structures:

1. `Tag`: Represents an HTML tag with a name, text content, child tags, and attributes. It overloads the `<<` operator to enable printing the tag's contents.

2. `P`: Represents a paragraph tag (`<p>`) and is derived from `Tag`. It provides constructors for initializing the tag with text content or a list of child tags.

3. `ING`: Represents an image tag (`<img>`) and is derived from `Tag`. It has an explicit constructor that takes a URL and sets the `src` attribute.

In the `main` function, an instance of `P` is created with an `ING` tag as its child, representing a paragraph containing an image tag. The code then prints the constructed tag using `cout`.

The code follows the Groovy-style builder pattern by using a combination of constructors, operator overloading (`<<`), and inheritance to create a readable and expressive syntax for constructing HTML tags. 
It demonstrates how the classes can be composed together to form complex structures using a fluid and intuitive style.

The Groovy-style builder pattern is a design pattern commonly used in dynamically-typed languages like Groovy, which provides a concise and expressive syntax for constructing complex objects or data structures. It aims to improve code readability and maintainability by enabling a fluent and natural language-like approach to object creation.




The key characteristics of the Groovy-style builder pattern include:

1. Method Chaining: Builders allow method chaining, where each method call returns a reference to the builder itself. This enables a sequence of method calls to be written in a fluent and readable manner.

2. Named Parameters: Builders often use named parameters or setters to specify different properties or attributes of the object being built. This approach allows for clear and self-descriptive code, as the names of the parameters indicate their purpose.

3. Hierarchical Structure: Builders can support a hierarchical structure, where objects can have child objects or nested elements. This allows for the creation of complex structures in a natural and intuitive way.

4. Declarative Syntax: Builders provide a declarative syntax that resembles a domain-specific language (DSL) specific to the problem domain. This DSL-like syntax enables code to read like a set of instructions or configuration statements, making it easier to understand and modify.

The Groovy-style builder pattern focuses on creating a simple and readable syntax for object construction, promoting code that is easy to understand, modify, and maintain. 
It allows developers to express complex object creation logic in a way that closely resembles natural language and reduces the verbosity often associated with traditional object creation approaches.
*/