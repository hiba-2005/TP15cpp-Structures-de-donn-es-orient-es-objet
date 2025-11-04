
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
using namespace std;

class TableHachage {
    vector<list<pair<int,string>>> buckets;
    size_t m;
    size_t h(int key) const { return static_cast<size_t>(key) % m; }
public:
    explicit TableHachage(size_t taille=8) : buckets(taille), m(taille) {}

    void inserer(int cle, const string& valeur) {
        auto& L = buckets[h(cle)];
        for (auto& kv : L) if (kv.first == cle) { kv.second = valeur; return; }
        L.emplace_back(cle, valeur);
    }
    string* rechercher(int cle) {
        auto& L = buckets[h(cle)];
        for (auto& kv : L) if (kv.first == cle) return &kv.second;
        return nullptr;
    }
    bool supprimer(int cle) {
        auto& L = buckets[h(cle)];
        for (auto it=L.begin(); it!=L.end(); ++it)
            if (it->first == cle) { L.erase(it); return true; }
        return false;
    }
    void afficher() const {
        for (size_t i=0;i<m;++i) {
            cout << i << ": ";
            for (auto const& kv : buckets[i]) cout << "("<<kv.first<<","<<kv.second<<") ";
            cout << "\n";
        }
    }
};

int main() {
    TableHachage T(5);
    T.inserer(10, "Ali");
    T.inserer(3,  "Sara");
    T.inserer(8,  "Yassine");
    T.inserer(15, "Nora");
    T.afficher();
    if (auto* v = T.rechercher(8))  cout << "cle 8 -> " << *v << "\n";
    cout << (T.supprimer(3) ? "supprime 3\n" : "introuvable\n");
    T.afficher();
    return 0;
}
