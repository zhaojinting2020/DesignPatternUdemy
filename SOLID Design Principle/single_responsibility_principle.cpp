// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace  std;

struct Journal{
    string title;
    vector<string> entries;
    
    Journal(const string& title):title(title){}
    void add_entry(const string& entry){
        static int count=1;
        entries.push_back(count++ + ":" + entry);
    }
    
    void save(const string& filename){
        ofstream ofs(filename);
        for( auto& e: entries){
            ofs<<e<<endl;
        }
    }
};

struct PersistenceManager{
    static void save(const Journal& j, const string& filename){
        ofstream ofs(filename);
        for(auto& e: j.entries){
            ofs<<e<<endl;
        }
    }
};

int main() {
    // Write C++ code here
    cout << "Hello world!";
    Journal journal{"Dear  Diary"};
    journal.add_entry("I ate a bug");
    
    PersistenceManager::save(journal, "diary.txt");

    return 0;
}

/**
The code provided demonstrates the Single Responsibility Principle (SRP) in action. SRP states that a class should have only one reason to change, meaning it should have a single responsibility or purpose. Let's summarize the code:

1. The code includes the necessary header files for input/output (`iostream`), vectors (`vector`), file stream (`fstream`), and strings (`string`).

2. The code defines a `Journal` struct, representing a journal with a title and a collection of entries. The `Journal` struct has the following members:
   - `title`: A string representing the title of the journal.
   - `entries`: A vector of strings containing the journal entries.
   - `Journal(const string& title)`: A constructor that initializes the journal with a given title.
   - `add_entry(const string& entry)`: A method that adds a new entry to the journal by appending it to the `entries` vector.
   - `save(const string& filename)`: A method that saves the journal entries to a file with the specified filename. It opens an output file stream (`ofstream`) and writes each entry to the file.

3. The code defines a `PersistenceManager` struct, which provides a static method called `save`. This struct is responsible for persisting the journal entries to a file. The `save` method takes a `Journal` object and a filename as parameters, opens an output file stream (`ofstream`), and writes each entry of the journal to the file.

Overall, the code demonstrates the separation of concerns by having the `Journal` struct responsible for managing the journal entries and saving them to a file, while the `PersistenceManager` struct handles the persistence aspect by providing a static method for saving a `Journal` object to a file. This adheres to the Single Responsibility Principle, as each struct has a clear and distinct responsibility.
**/