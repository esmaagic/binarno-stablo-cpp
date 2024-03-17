#ifndef STABLO_H
#define STABLO_H
#include <utility>
#include <vector>
using namespace std;

template <typename Tip>
class Stablo {
    public:
    struct Cvor {
        Tip element;
        Cvor *ld, *dd, *rod;
        Cvor(Tip el, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr):element(el), rod(rod), ld(ld), dd(dd) {}
    };

    class Iterator {
         public:
            Cvor* pok;
            Stablo<Tip>* stablo;
            Iterator(Cvor* cvor, Stablo<Tip>* s):pok(cvor), stablo(s){}

            Tip operator*(){ return pok->element; }
            Iterator operator++(int) { Iterator zaVratit = *this; pok = stablo->Sljedbenik(pok); return zaVratit; }
            Iterator operator++() { pok = stablo->Sljedbenik(pok); return *this; }
            friend bool operator==(Iterator it1, Iterator it2) { return (it1.pok == it2.pok); }
            friend bool operator!=(Iterator it1, Iterator it2) { return !(it1 == it2); }

    };

    class Reverse_Iterator {
         public:
            Cvor* pok;
            Stablo<Tip>* stablo;
            Reverse_Iterator(Cvor* cvor, Stablo<Tip>* s):pok(cvor), stablo(s){}

            Tip operator*(){ return pok->element; }
            Reverse_Iterator operator++(int) { Reverse_Iterator zaVratit = *this; pok = stablo->Prethodnik(pok); return zaVratit; }
            Reverse_Iterator operator++() { pok = stablo->Prethodnik(pok); return *this; }
            friend bool operator==(Reverse_Iterator it1, Reverse_Iterator it2) { return (it1.pok == it2.pok); }
            friend bool operator!=(Reverse_Iterator it1, Reverse_Iterator it2) { return !(it1 == it2); }

    };


    private:
    int n;
    Cvor* korijen;
    Cvor* head;
    Cvor* tail;
    //pomocne funkcije:
    Cvor* Sljedbenik (Cvor* ) const;
    Cvor* Prethodnik(Cvor* ) const;
    Cvor* Pocetak(Cvor*) const;
    Cvor* Kraj(Cvor *) const;
    Cvor* kopirajStablo(const Cvor* src, Cvor* parent);


    public:
    Stablo():n(0),korijen(nullptr), head(nullptr), tail(nullptr) {}
    Stablo(Stablo<Tip>&& );
    Stablo(const Stablo<Tip>& );
    ~Stablo();

    void Ispis(Cvor*) const;
    void InOrder(Cvor*) const;
    int Visina(Cvor*) const;
    int Size() { return n;}
    bool Empty() { return n == 0; }
    Cvor* Find(const Tip vrijednost) const;
    pair<Cvor*, bool> Insert(const Tip vrijednost);
    void Erase(const Tip vrijednost);
    void Clear() { while(Size()>0) Erase(head->rod->element); };

    Iterator Begin()  { return Iterator(head->rod, this); }
    Iterator End()  { return Iterator(tail,this); }

    Reverse_Iterator RBegin()  { return Reverse_Iterator(tail->rod, this); }
    Reverse_Iterator REnd()  { return Reverse_Iterator(head, this); }

    static bool jePodskup(Stablo<Tip>&, Stablo<Tip>& );


    Tip operator[](int index) const;


    Stablo<Tip>& operator=(initializer_list<Tip> );
    Stablo<Tip>& operator=(Stablo<Tip>&& );
    Stablo<Tip>& operator=(Stablo<Tip>& );




};



#include "stablo.cpp"

#endif // STABLO_H
