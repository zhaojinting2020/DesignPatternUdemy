#include <iostream>
#include <vector>

using namespace std;

struct Neuron;

// don't have to implement the connect_to function inside each class
// https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/

// The CRTP consists in:

// inheriting from a template class,
// use the derived class itself as a template parameter of the base class.

// The purpose of doing this is using the derived class in the base class.

template <typename Self>
struct SomeNeurons {
    template <typename T>
    void connect_to(T& other) {
        for (Neuron& from : *static_cast<Self*>(this)) {
            for (Neuron& to : other) {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

struct Neuron : SomeNeurons<Neuron> {
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron() {
        static int id{1};
        this->id = id++;
    }

    // a single object can masquerade as a collection
    // duck typing
    Neuron* begin() { return this; }
    Neuron* end() { return this + 1; }

    

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

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer> {
    NeuronLayer(int count) {
        while (count-- > 0) {
            emplace_back(Neuron{});
        }
    }

    friend ostream& operator<<(ostream& os, const NeuronLayer& obj) {
        for (const auto& n : obj) {
            os << n;
        }
        return os;
    }
};

int main() {
    Neuron n1, n2;
    n1.connect_to(n2);
    cout << n1 << endl;
    cout << n2 << endl;

    NeuronLayer layer1{2}, layer2{3};
    layer1.connect_to(n2);
    layer1.connect_to(layer2);
    cout << layer1 << layer2 << endl;

    return 0;
}
