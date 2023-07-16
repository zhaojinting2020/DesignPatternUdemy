#include <string>
using namespace std;

struct Person
{
  int id;
  string name;
  
  Person(int id, string name):id(id), name(name){}
};

class PersonFactory
{
private:
    int count{0};
public:
  Person create_person(const string& name)
  {
    Person p(count++, name);
    return p;
  }
};
