#define _USE_MATH_DEFINES

#include <tuple>
#include <cmath>
#include <memory>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

class Database{
public:
    virtual int get_population(const string& name) = 0;
};

class SingletonDatabase : public Database{
    SingletonDatabase(){
        cout<<"Initialzing database"<<endl;
        ifstream ifs("capitals.txt");

        string s, s2;

        while(getline(ifs, s)){
            getline(ifs, s2);
            int pop = lexical_cast<int>(s2);
            capitals[s] = pop;
        }
    }
    map<string, int> capitals;

public:
    SingletonDatabase(SingletonDatabase const&) = delete; // singleton
    void operator=(SingletonDatabase const&) = delete; // singleton

    static SingletonDatabase& get(){
        static SingletonDatabase db; // ensures only one instance of the SingletonDatabase will be created during the execution
        return db;
    }

    int get_population(const string& name){
        return capitals[name];
    }
    
};

class DummyDatabase: public Database{
    map<string, int> capitals;
public:
    DummyDatabase(){
        capitals["alpha"] = 1;
        capitals["beta"] = 2;
        capitals["gamma"] = 3;
    }
    int get_population(const string& name) override{
        return capitals[name];
    }
};

struct SingletonRecordFinder{
    int total_population(vector<string> names){
        int result{0};
        for(auto& name: names){
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};

struct ConfigurableRecordFinder{
    Database& db;
    ConfigurableRecordFinder(Database& db) : db(db) {}
};

TEST(RecordFinderTests, SingletonTotalPopulationTest){
    SingletonRecordFinder rf;
    vector<string> names{"Seoul", "Mexico City"};
    int tp = rf.total_population(names);
    cout<<"tp="<<tp<<endl;
    EXPECT_EQ(1750+1740, tp);
}

TEST(RecordFinderTests, DependantTotalPopulationTest){
    DummyDatabase db;
    ConfigurableRecordFinder rf{db};
    EXPECT_EQ(4, rf.total_population(vector<string>{"alpha", "gamma"}));
}

int main(int ac, char* av[]){
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}

/**
 * The first time the get function is called, the db variable is initialized by invoking the private constructor of the SingletonDatabase class. 
 * This constructor initializes the database by reading data from the "capitals.txt" file and populating the capitals map.
 * Subsequent calls to the get function simply return the existing db instance, which was created during the first call. This ensures that the same instance of the SingletonDatabase object is always returned.
*/