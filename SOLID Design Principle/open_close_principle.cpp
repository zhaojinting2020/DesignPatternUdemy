// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
using namespace  std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product{
    string name;
    Color color;
    Size size;
};

struct ProductFilter{
    vector<Product*> by_color(vector<Product*> items, Color color){
        vector<Product*> result;
        for (auto& i : items){
            if(i->color == color){
                result.push_back(i);
            }
        }
        return result;
    }
    
    vector<Product*> by_size(vector<Product*> items, Size size){
        vector<Product*> result;
        for (auto& i : items){
            if(i->size == size){
                result.push_back(i);
            }
        }
        return result;
    }
};

template<typename T> struct AndSpecification;

template<typename T> struct Specification{
    virtual bool is_satisfied(T* item)=0;
    
    AndSpecification<T> operator&&(Specification<T> && other){
        return AndSpecification<T>(*this, other);
    }
};

template<typename T> struct AndSpecification: Specification<T>{
    Specification<T>& first;
    Specification<T>& second;
    
    AndSpecification(Specification<T>& first, Specification<T>& second):first(first), second(second){}
    bool is_satisfied(T* item) override{
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template<typename T> struct Filter{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec)=0;
};

struct BetterFilter : Filter<Product>{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override{
        vector<Product*> result;
        for(auto& item : items){
            if(spec.is_satisfied(item)){
                result.push_back(item);
            }
        }
        return result;
    }
};

template<typename T> struct ColorSpecification : Specification<T>{
    Color color;
    ColorSpecification(Color color):color(color){}
    
    bool is_satisfied(Product *item) override{
        return item->color == color;
    }
};

template<typename T> struct SizeSpecification : Specification<T>{
    Size size;
    SizeSpecification(Size size):size(size){}
    
    bool is_satisfied(Product *item) override{
        return item->size == size;
    }
};



int main() {
    // Write C++ code here
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};
    
    vector<Product*> items{&apple, &tree, &house};

    ColorSpecification<Product> green(Color::green);
    SizeSpecification<Product> large(Size::large);
    
    AndSpecification<Product> green_and_large(green, large); // the type of the AndSpecification is deductted by color and size
    
    auto spec = ColorSpecification<Product>(Color::green) && SizeSpecification<Product>(Size::large);
    
    BetterFilter bf;
    
    
    for (auto& item : bf.filter(items, spec)){
        std::cout<<" is green and large"<<std::endl;
    }

    return 0;
}

/**
The code demonstrates the Open-Closed Principle by providing an extensible framework for filtering products without modifying the existing code. Here's how it achieves this principle:

1. **ProductFilter**: The `ProductFilter` struct provides filtering methods for products based on color and size. Initially, it satisfies the "closed" part of the principle because it is a specific implementation of filtering criteria. However, it violates the "open" part because if new filtering criteria are introduced, such as filtering by weight or price, the `ProductFilter` class would need to be modified.

2. **Specification Pattern**: To address the violation of the Open-Closed Principle, the code introduces the Specification design pattern. The `Specification` struct defines a generic interface for filtering objects based on certain criteria. It is open for extension because new specifications can be added by implementing the `is_satisfied` method in derived classes.

3. **Filter Interface**: The `Filter` struct provides a generic interface for filtering a collection of objects based on a specification. It is open for extension because new filters can be added by implementing the `filter` method in derived classes.

4. **BetterFilter**: The `BetterFilter` struct is an implementation of the `Filter` interface specifically for `Product` objects. It takes advantage of the Specification pattern by filtering products based on a given specification. It satisfies the "closed" part of the principle because it is a specific implementation of the filtering logic. However, it also satisfies the "open" part because new filtering criteria can be added by creating new specifications and implementing the `is_satisfied` method accordingly, without modifying the `BetterFilter` class.

5. **Combining Specifications**: The code demonstrates the flexibility of the Specification pattern by allowing specifications to be combined. This is shown through the creation of an `AndSpecification` object that combines multiple specifications using the logical "AND" operator. By combining specifications, new filtering criteria can be created without modifying existing classes or introducing complex conditional logic.

By separating the filtering logic into specifications and filters, and allowing for the composition of specifications, the code adheres to the Open-Closed Principle. It allows for new filtering criteria to be added without modifying existing code, promoting extensibility and maintainability.
*/