
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template<typename T>
class Pile {
    vector<T> data;
public:
    void empiler(const T& e) { data.push_back(e); }
    T depiler() {
        if (estVide()) throw runtime_error("Pile vide");
        T v = data.back(); data.pop_back(); return v;
    }
    const T& sommet() const {
        if (estVide()) throw runtime_error("Pile vide");
        return data.back();
    }
    bool estVide() const { return data.empty(); }

    void inverser() {
        size_t i=0, j=data.size()?data.size()-1:0;
        while (i<j) { std::swap(data[i], data[j]); ++i; --j; }
    }

    void afficher() const {
        cout << "[ ";
        for (auto const& x : data) cout << x << " ";
        cout << "]\n";
    }
};

int main() {
    Pile<int>    P1; P1.empiler(1); P1.empiler(2); P1.empiler(3); P1.afficher(); P1.inverser(); P1.afficher();
    Pile<string> P2; P2.empiler("Anti-Atlas"); P2.empiler("Akyote"); P2.empiler("Amnayo"); P2.afficher();
    cout << "sommet P2 = " << P2.sommet() << "\n";
    try { Pile<double> P3; cout << P3.depiler() << "\n"; }
    catch (const exception& e) { cerr << "Erreur: " << e.what() << "\n"; }
    return 0;
}
