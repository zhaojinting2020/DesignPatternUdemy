#include <string>
#include <ostream>
#include <vector>
using namespace std;

class Field{
public:
    string name;
    string type;
    
public:
    Field(const string& name, const string& type):name(name), type(type){}
};

class CodeBuilder
{
    
private:
    string class_name{""};
    string type{""};
    vector<Field> fields{};

public:
  CodeBuilder(const string& class_name):class_name(class_name)
  {
      
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    fields.push_back(Field(name, type));
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    os << "class " << obj.class_name << "\n";
    os << "{\n";
    for (const auto& field : obj.fields)
    {
        os << "  " << field.type << " " << field.name << ";\n";
    }
    os << "};\n";
    return os;
  }
};