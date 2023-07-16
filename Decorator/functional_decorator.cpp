#include <iostream>
#include <functional>
using namespace std;

struct Logger{
    function<void()> func;
    string name;

    Logger(const function<void()>& func, const string& name) : func(func), name(name){}

    void operator()() const{
        cout<<"Entering "<<name<<endl;
        func();
        cout<<"Exiting "<<name<<endl;
    }
};

template<typename Func>
struct Logger2{   
    Func func;
    string name;

    Logger2(const Func& func, const string& name) : func(func), name(name){}

    void operator()() const{
        cout<<"Entering "<<name<<endl;
        func();
        cout<<"Exiting "<<name<<endl;
    }
};

template<typename Func> 
auto make_logger2(Func func, const string& name){
    return Logger2<Func>{func, name};
}


double add(double a, double b){
    cout << a << "+" << b << " = " << (a+b) <<endl;
    return a+b;
}

template <typename> struct Logger3;

template <typename R, typename ...Args>
struct Logger3<R(Args...)>{
    function<R(Args...)> func;
    string name;

    Logger3(const function<R(Args...)>& func, const string& name) : func(func), name(name){
    }

    R operator()(Args ...args){
        cout << "Entering " << name << endl;
        R result = func(args ...);
        cout << "Exiting " << name <<endl;

        return result;
    }
};

/**
 the make_logger3 function template is designed to deduce the types of the function pointer's arguments (Args...) and 
 the return type (R) using template argument deduction. 
 However, the function pointer itself does not carry information about its argument types. 
 Hence, the template deduction cannot automatically deduce the argument types solely from the function pointer.
*/
template<typename R, typename ... Args>
auto make_logger3(R (*func)(Args...), const string& name){
    return Logger3<R(Args...)>(
        function<R(Args...)>(func), 
        name
    );
}

int main(){
    // Logger2 log([](){cout<<"Hello"<<endl;}, "HelloFunction");

    // auto log2 = make_logger2([](){cout<<"Hello"<<endl;}, "HelloFunction");
    // log2();

    // Logger3 log3(add, "Add"); will not work, cause add is not a std::function but a function pointer,
    // so we have to make a make_logger3 helper function to accept a function pointer and deduce the argument 
    // types from it

    auto logged_add = make_logger3(add, "Add");
    auto result = logged_add(2, 3);
    cout << "result = " << result << endl;
}

/**
 *In the given code, the concepts of functional decorators are demonstrated through the `Logger`, `Logger2`, and `Logger3` structures.

A functional decorator is a higher-order function or object that takes in a function (or callable) and extends or modifies its behavior without directly modifying the function itself. It wraps the original function with additional functionality.

In the code, the `Logger`, `Logger2`, and `Logger3` structures act as functional decorators. They take a function or callable object as input and add logging behavior around it.

Here's a breakdown of how each decorator works:

1. `Logger`:
   - It takes a `function<void()>` as input along with a name.
   - The `operator()` implementation acts as the decorated function.
   - When the decorated function is called (`operator()` is invoked), it first logs the entry message, then calls the original function, and finally logs the exit message.

2. `Logger2`:
   - Similar to `Logger`, it takes a callable object `Func` as input along with a name.
   - The `operator()` implementation acts as the decorated function.
   - When the decorated function is called (`operator()` is invoked), it logs the entry message, calls the original function, and logs the exit message.

3. `Logger3`:
   - It is a template struct that takes a function signature as a template parameter (`R(Args...)`).
   - It stores a `function<R(Args...)>` object and a name.
   - The `operator()` implementation acts as the decorated function.
   - When the decorated function is called (`operator()` is invoked), it logs the entry message, calls the original function with the provided arguments, logs the exit message, and returns the result.

The `make_logger2` and `make_logger3` functions provide a convenient way to create instances of the `Logger2` and `Logger3` decorators, respectively. They encapsulate the deduction of template arguments and create the corresponding decorator objects.

By using these decorators, you can add logging functionality to existing functions without modifying their implementation. This demonstrates the concept of functional decorators, where the decorators enhance the behavior of the original functions by wrapping them with additional functionality.
*/