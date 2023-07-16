// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <fstream>
using namespace  std;

struct Document{
    string content = "content";
};

// struct IMachine{
//     virtual void print(Document& doc) = 0;
//     virtual void scan(Document& doc) = 0;
//     virtual void fax(Document& doc) = 0;
    
// };

// struct MFP : IMachine{
//     virtual void print(Document& doc) override{
        
//     }
//     virtual void scan(Document& doc) override{
        
//     }
//     virtual void fax(Document& doc) override{
        
//     }
// };

// struct Scanner : IMachine{
//      virtual void print(Document& doc) override{
        
//     }
//     virtual void scan(Document& doc) override{
//         // ok
//     }
//     virtual void fax(Document& doc) override{
        
//     }
// };

struct IPrinter{
    virtual void print(Document& doc)=0;
};
struct IScanner{
    virtual void scan (Document& doc)=0;
};
struct IFaxer{
    virtual void fax(Document& doc)=0;
};

struct Printer : IPrinter{
    void print(Document& doc) override{
        cout<<"Printer print"<<endl;
    }
};

struct Scanner : IScanner{
    void scan(Document& doc) override{
        cout<<"Scanner scan"<<endl;
    }
};

struct Faxer : IFaxer{
    void fax(Document& doc) override{
        cout<<"Faxer fax"<<endl;
    }
};

struct IMachine : IPrinter, IScanner, IFaxer{};

struct Machine : IMachine{
    
    IPrinter& printer;
    IScanner& scanner;
    IFaxer& faxer;
    
    Machine(IPrinter& printer, IScanner& scanner, IFaxer& faxer): printer(printer), scanner(scanner), faxer(faxer){}
    
    void print(Document& doc) override{
        printer.print(doc);
    }
    void scan(Document& doc) override{
        scanner.scan(doc);
    }
    void fax(Document& doc) override{
        faxer.fax(doc);
    }
    
};

int main() {
    // Write C++ code here
    Printer printer;
    Scanner scanner;
    Faxer faxer;
    Machine machine(printer, scanner, faxer);
    
    Document doc;
    
    machine.print(doc);
    machine.scan(doc);
    machine.fax(doc);

    return 0;
}

/**
 * The provided code demonstrates the interface segregation principle (ISP) in C++. The interface segregation principle states that clients should not be forced to depend on interfaces they do not use. It promotes the idea of designing cohesive and focused interfaces.

In the code, the following interfaces are defined:

1. `IPrinter`: Defines the `print()` function.
2. `IScanner`: Defines the `scan()` function.
3. `IFaxer`: Defines the `fax()` function.

These interfaces represent specific functionalities related to printing, scanning, and faxing.

Next, concrete implementations of these interfaces are provided:

1. `Printer`: Implements the `print()` function and prints a document.
2. `Scanner`: Implements the `scan()` function and performs a document scanning operation.
3. `Faxer`: Implements the `fax()` function and performs a document faxing operation.

The `Machine` struct is defined as an implementation of the `IMachine` interface. It aggregates instances of `IPrinter`, `IScanner`, and `IFaxer` interfaces. The `Machine` struct acts as a unified interface that internally delegates the operations to the respective printer, scanner, and faxer instances.

In the `main()` function, an instance of `Machine` is created, composed of a `Printer`, `Scanner`, and `Faxer`. The `Machine` object is used to print, scan, and fax a `Document` object.

By segregating the interfaces and using composition, the code adheres to the interface segregation principle, allowing clients to depend only on the interfaces they require and avoiding unnecessary dependencies.
*/