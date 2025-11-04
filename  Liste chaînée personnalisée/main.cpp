
#include <iostream>
#include <stdexcept>
using namespace std;

struct Noeud {
    int valeur;
    Noeud* suivant;
    explicit Noeud(int v, Noeud* s=nullptr) : valeur(v), suivant(s) {}
};

class ListeChainee {
    Noeud* tete{};
    size_t n{};
public:
    ListeChainee() = default;
    ~ListeChainee() { vider(); }

    void ajouterDebut(int v) {
        tete = new Noeud(v, tete);
        ++n;
    }
    void ajouterFin(int v) {
        if (!tete) { ajouterDebut(v); return; }
        Noeud* cur = tete;
        while (cur->suivant) cur = cur->suivant;
        cur->suivant = new Noeud(v);
        ++n;
    }
    bool supprimer(int v) {
        Noeud* cur = tete; Noeud* prev = nullptr;
        while (cur) {
            if (cur->valeur == v) {
                if (prev) prev->suivant = cur->suivant; else tete = cur->suivant;
                delete cur; --n; return true;
            }
            prev = cur; cur = cur->suivant;
        }
        return false;
    }
    void afficher() const {
        cout << "[ ";
        for (Noeud* cur = tete; cur; cur = cur->suivant) cout << cur->valeur << " ";
        cout << "]\n";
    }
    size_t taille() const { return n; }

    void vider() {
        while (tete) { Noeud* tmp = tete; tete = tete->suivant; delete tmp; }
        n = 0;
    }



    class const_iterator {
        const Noeud* p{};
    public:
        explicit const_iterator(const Noeud* n=nullptr) : p(n) {}
        const int& operator*() const { return p->valeur; }
        const_iterator& operator++() { p = p->suivant; return *this; }
        bool operator!=(const const_iterator& other) const { return p != other.p; }
    };
    const_iterator begin() const { return const_iterator(tete); }
    const_iterator end()   const { return const_iterator(nullptr); }
};

int main() {
    ListeChainee L;
    L.ajouterDebut(3);
    L.ajouterFin(5);
    L.ajouterDebut(1);
    L.afficher();
    L.supprimer(3);
    L.afficher();
    cout << "taille = " << L.taille() << "\n";

    cout << "parcours (iterateur): ";
    for (int x : L) cout << x << " ";
    cout << "\n";
    return 0;
}
