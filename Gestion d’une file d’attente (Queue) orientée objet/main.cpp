#include <iostream>
#include <stdexcept>
using namespace std;

struct Node {
    int v; Node* next;
    explicit Node(int x) : v(x), next(nullptr) {}
};

class File {
    Node* head{};
    Node* tail{};
    size_t n{};
    size_t capacite;
public:
    explicit File(size_t cap=0) : capacite(cap) {}
    ~File() { while (!estVide()) defiler(); }

    bool estVide()  const { return n == 0; }
    bool estPleine() const { return capacite && n >= capacite; }

    void enfiler(int x) {
        if (estPleine()) throw runtime_error("File pleine");
        Node* nd = new Node(x);
        if (!tail) head = tail = nd;
        else { tail->next = nd; tail = nd; }
        ++n;
    }
    int defiler() {
        if (estVide()) throw runtime_error("File vide");
        Node* nd = head; int val = nd->v;
        head = head->next; if (!head) tail = nullptr;
        delete nd; --n; return val;
    }
    void afficher() const {
        cout << "< ";
        for (Node* p = head; p; p = p->next) cout << p->v << " ";
        cout << ">\n";
    }
};

int main() {
    File Q(5);
    int choix = -1;
    while (choix != 0) {
        cout << "1) enfiler  2) defiler  3) afficher  0) quitter : ";
        if (!(cin >> choix)) return 0;
        try {
            if (choix == 1) {
                int x; cout << "valeur : "; cin >> x; Q.enfiler(x);
            } else if (choix == 2) {
                cout << "defile -> " << Q.defiler() << "\n";
            } else if (choix == 3) {
                Q.afficher();
                cout << (Q.estVide() ? "vide" : "non vide")
                     << ", " << (Q.estPleine() ? "pleine" : "non pleine") << "\n";
            }
        } catch (const exception& e) { cerr << "Erreur: " << e.what() << "\n"; }
    }
    return 0;
}
