/**

class Creature{
    int strength;
    int intelligence;
    int agility;

    public:
    
    int get_strength(int strength){
        return strength;
    }

    void set_strength(int strength){
        this->strength = strength;
    }

    int get_agility() const{
        return agility;
    }

    void set_agility(int agility){
        this->agility = agility;
    }

    int get_intelligence() const{
        return intelligence;
    }

    void set_intelligence(int intelligence){
        this->intelligence = intelligence;
    }

    double sum() const{
        return strength+agility+intelligence;
    }

    double average() const{
        return sum()/3.0;
    }



};

**/

#include <array>
#include <numeric>
#include <algorithm>
#include <iostream>

using namespace std;

class Creature{
    enum Abilities{str, agl, intl, count};
    array<int, count> abilities;

public:
    int get_strength() const{return abilities[str];}
    void set_strength(int value) {abilities[str] = value;}

    int get_agility() const{return abilities[agl];}
    void set_agility(int value) {abilities[agl] = value;}

    int get_intelligence() const{return abilities[intl];}
    void set_intelligence(int value) {abilities[intl] = value;}

    int sum() const{
        return accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const{
        return sum() / (double)count;
    }

    int max() const{
        return *max_element(abilities.begin(), abilities.end());
    }

    int main(int ac, char* av[]){
        Creature orc;
        orc.set_intelligence(9);
        orc.set_strength(16);
        orc.set_agility(11);

        cout<<"average="<<orc.average()<<" max="<<orc.max()<<endl;
    }
};

