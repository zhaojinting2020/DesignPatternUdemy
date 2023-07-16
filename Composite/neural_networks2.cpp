#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

// composite operation, allowing connection between neuron & layer / layer & layer

template <typename T1, typename T2>
void connect_to(T1& from_set, T2& to_set) {
    for (auto& from : from_set) {
        for (auto& to : to_set) {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}

struct Neuron {
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int id_counter = 1;
        id = id_counter++;
    }

    Neuron* begin() {return this;}
    Neuron* end() {return this+1;}
    
    friend ostream& operator<<(ostream& os, const Neuron& obj) {
        for (Neuron* n : obj.in) {
            os << n->id << "\t-->\t[" << obj.id << "]" << endl;
        }

        for (Neuron* n : obj.out) {
            os << "[" << obj.id << "]\t-->\t" << n->id << endl;
        }

        return os;
    }
};

struct NeuronLayer : vector<Neuron> {
    NeuronLayer(int count) {
        while (count-- > 0) {
            emplace_back(Neuron{});
        }
    }

    friend ostream& operator<<(ostream& os, const NeuronLayer& obj) {
        for (auto& n : obj) {
            os << n;
        }
        return os;
    }
};

int main() {
    Neuron n1, n2;
    
    cout<<"layer connection"<<endl;

    NeuronLayer layer1{ 2 }, layer2{ 3 };
    connect_to(n1, layer1);
    connect_to(layer2, n2);
    connect_to(layer1, layer2);
    
    cout << n1 << endl;

    cout << layer1 << layer2 << endl;
    
    cout << n2 << endl;

    return 0;
}
