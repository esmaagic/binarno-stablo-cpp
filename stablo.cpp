#ifndef STABLO_CPP
#define STABLO_CPP
#include "stablo.h"
#include <iostream>


//konstruktor kopije
template <typename Tip>
Stablo<Tip>::Stablo(const Stablo<Tip>& kopija) : n(0), korijen(nullptr), head(kopija.head), tail(kopija.tail) {
    korijen = kopirajStablo(kopija.korijen, nullptr); //rekurzivno kreira sve elemente
    auto minimalni = Pocetak(korijen);
    auto maksimalni = Kraj(korijen);
    head = new Cvor(Tip{},minimalni ); //postavi head
    minimalni->ld = head;
    tail = new Cvor(Tip{}, maksimalni);// postavi tail
    maksimalni->dd = tail;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::kopirajStablo(const Cvor* trenutni, Cvor* roditelj) {
    if (trenutni == nullptr || trenutni == head || trenutni == tail )
        return nullptr;

    Cvor* noviCvor = new Cvor(trenutni->element, roditelj);
    n++;

    noviCvor->ld = kopirajStablo(trenutni->ld, noviCvor);
    noviCvor->dd = kopirajStablo(trenutni->dd, noviCvor);
    return noviCvor;
}


//pomjerajuci konstruktor kopije
template <typename Tip>
Stablo<Tip>::Stablo(Stablo<Tip>&& moveStablo) : n(moveStablo.n), korijen(moveStablo.korijen), head(moveStablo.head), tail(moveStablo.tail) {
    moveStablo.n = 0;
    moveStablo.korijen = nullptr;
    moveStablo.head = nullptr;
    moveStablo.tail = nullptr;
}


template <typename Tip>
Stablo<Tip>::~Stablo(){
    Clear();
    delete head;
    delete tail;
    delete korijen;
}




template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Find(const Tip vrijednost) const {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr && trenutni != head && trenutni != tail) {
       if(trenutni->element == vrijednost)
         return trenutni;
       if(vrijednost < trenutni->element)
            trenutni = trenutni->ld;
       else trenutni = trenutni->dd;
    }
    return nullptr;
}


template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Pocetak(Cvor* cvor) const {
    if(cvor == nullptr)
        return cvor;
    Cvor *trenutni = cvor;
    while(trenutni->ld != head && trenutni->ld != nullptr)
        trenutni = trenutni->ld;
    return trenutni;

}


template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Kraj(Cvor* cvor) const {
    if(cvor == nullptr)
        return cvor;
    Cvor *trenutni = cvor;
    while(trenutni->dd != tail && trenutni->dd != nullptr)
        trenutni = trenutni->dd;
    return trenutni;

}


template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Sljedbenik(Stablo<Tip>::Cvor* cvor) const {
    if(cvor->dd != nullptr && cvor->dd != tail) {
        Cvor *trenutni = cvor->dd;
        while(trenutni->ld != nullptr && trenutni->ld != head)
            trenutni = trenutni->ld;
        return trenutni;
    }else if(cvor->dd == tail)
        return tail;

    Cvor* trenutni = cvor;

    while(trenutni->rod != nullptr) {
        if(trenutni->rod->ld == trenutni)
            return trenutni->rod;
        if(trenutni->rod->dd == trenutni)
            trenutni = trenutni->rod;
    }

}


template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::Prethodnik(Stablo<Tip>::Cvor* cvor) const {

    Cvor* trenutni = cvor;
    if(trenutni->ld != nullptr && trenutni->ld != head){
        trenutni = trenutni->ld;
        while(trenutni->dd != nullptr && trenutni->dd != tail)
            trenutni = trenutni->dd;
        return trenutni;
    }else{
        if(trenutni->ld == head)//najmanji element nema prethodnika
            return head;
        while(trenutni->rod != nullptr && trenutni->rod->ld == trenutni){
            trenutni = trenutni->rod;
        }
        return trenutni->rod;
    }

}


template <typename Tip>
void Stablo<Tip>::Erase(const Tip vrijednost) {
    Cvor* cvor = Find(vrijednost);
    if(cvor == nullptr) return;



    if(cvor->ld == nullptr || cvor->ld == head && cvor->dd == nullptr || cvor->dd == tail ) { //ako je list
        if(cvor->rod == nullptr){//ako je korijen
            korijen = nullptr;
            tail->rod= korijen;
            head->rod= korijen;
        }
        else if(cvor->dd == tail){ //ako je najveci el
            cvor->rod->dd = tail;
            tail->rod = cvor->rod;
        }
        else if(cvor->ld == head){ //ako je najmanji el
            cvor->rod->ld = head;
            head->rod = cvor->rod;
        }
        else if (cvor->dd == nullptr && cvor->ld == nullptr) { //ako je samo list
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = nullptr;
            else cvor->rod->dd = nullptr;
        }

    }
    else if(cvor->ld == nullptr || cvor->ld == head) { //ako nema lijevo dijete
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr && cvor->ld == head){//ako je korijen
           korijen = cvor->dd;
           Cvor* noviNajmanji = Pocetak(cvor->dd);
           head->rod = noviNajmanji;
           noviNajmanji->ld = head;
        }
        else {
            if(cvor->ld == nullptr){ //ako nema lijevo dijete
                if(cvor->rod->ld == cvor)
                    cvor->rod->ld = cvor->dd;
                else cvor->rod->dd = cvor->dd;
            }else if(cvor->ld == head){ //ako je najmanji
                cvor->rod->ld = cvor->dd;
                Cvor *noviNajmanji = Pocetak(cvor->dd);
                head->rod = noviNajmanji;
                noviNajmanji->ld = head;
            }
        }
    }
    else if(cvor->dd == nullptr || cvor->dd == tail) { //ako nema desno dijete
        cvor->ld->rod = cvor->rod;
        if(cvor->rod == nullptr && cvor->dd == tail){//ako je korijen
            korijen = cvor->ld;
            Cvor* noviNajveci = Kraj(cvor->ld);
            noviNajveci->dd = tail;
            tail->rod = noviNajveci;
        }
        else {
            if(cvor->dd == nullptr){ //nema desno dijete
                if(cvor->rod->ld == cvor)
                    cvor->rod->ld = cvor->ld;
                else cvor->rod->dd = cvor->ld;
            }else if(cvor->dd == tail){ // najveci je
                cvor->rod->dd = cvor->ld;
                Cvor* noviNajveci = Kraj(cvor->ld);
                noviNajveci->dd = tail;
                tail->rod = noviNajveci;
            }

        }
    }
    else { //ako ima oba djeteta
        Cvor* sljedbenik = Sljedbenik(cvor);
        sljedbenik->ld = cvor->ld;
        cvor->ld->rod = sljedbenik;
        cvor->dd->rod = cvor->rod;
        if(cvor->rod == nullptr) //ako je korijen
           korijen = cvor->dd;
        else {
            if(cvor->rod->ld == cvor)
                cvor->rod->ld = cvor->dd;
            else cvor->rod->dd = cvor->dd;
        }
    }

    delete cvor;
 n--;
}


template <typename Tip>
pair<typename Stablo<Tip>::Cvor*, bool> Stablo<Tip>::Insert(const Tip vrijednost) {

    Cvor *trenutni = korijen, *prethodni = nullptr;
    while(trenutni != nullptr && trenutni != head && trenutni != tail) {
       if(trenutni->element == vrijednost)
         return {trenutni, false};
       prethodni = trenutni;
       if(vrijednost < trenutni->element)
            trenutni = trenutni->ld;
       else trenutni = trenutni->dd;
    }

    Cvor *novi = new Cvor(vrijednost, prethodni);

    if(korijen == nullptr) { //ako je prvi element u stablu
        head = new Cvor(Tip{}, novi);
        tail = new Cvor(Tip{}, novi);
        novi->ld = head;
        novi->dd = tail;
        korijen = novi;
    }
    else if(prethodni->ld == head && prethodni->dd == tail){ //ako je list i korijen
        if(prethodni->element < vrijednost ){
            prethodni->dd = novi;
            tail->rod = novi;
            novi->dd = tail;
        }else{
            prethodni->ld = novi;
            head->rod = novi;
            novi->ld = head;
        }
    }
    else if(trenutni == head){ //ako je novi najmanji
        novi->ld = head;
        head->rod = novi;
        prethodni->ld = novi;
    }else if(trenutni == tail){ // ako je novi najveci
        novi->dd = tail;
        tail->rod = novi;
        prethodni->dd = novi;
    }
    else if(prethodni ->element < novi->element){
        prethodni->dd = novi;
    }
    else prethodni->ld = novi;

    n++;
    return {novi, true};
}





template <typename Tip>
bool Stablo<Tip>::jePodskup( Stablo<Tip>& s1, Stablo<Tip>& s2){
    auto manjeStablo = (s1.Size() <= s2.Size()) ? s1 : s2;
    auto veceStablo = (s1.Size() <= s2.Size()) ? s2 : s1;

    auto itVece = veceStablo.Begin();
    for ( auto itManje = manjeStablo.Begin(); itManje !=manjeStablo.End(); itManje++) {
        while (itVece != veceStablo.End() && *itVece < *itManje)
            itVece++;
        if (itVece == veceStablo.End() || *itVece != *itManje)
            return false;
    }
    return true;

}

template <typename Tip>
Tip Stablo<Tip>::operator[](int i) const {
    if (i < 0 || i >= n)
        return Tip{};

    Cvor* trenutni = Pocetak(korijen);
    for(int j = 0; j<i; j++)
        trenutni = Sljedbenik(trenutni);

    return trenutni->element;
}


template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(initializer_list<Tip> dodjeliEl) {
    Clear();

    for (const Tip& element : dodjeliEl)
        Insert(element);

    return *this;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(Stablo<Tip>&& moveKopija) {
    if (this != &moveKopija) {
        Clear();

        n = moveKopija.n;
        korijen = moveKopija.korijen;
        head = moveKopija.head;
        tail = moveKopija.tail;

        moveKopija.n = 0;
        moveKopija.korijen = nullptr;
        moveKopija.head = nullptr;
        moveKopija.tail = nullptr;
    }
    return *this;
}

template <typename Tip>
Stablo<Tip>& Stablo<Tip>::operator=(Stablo<Tip>& kopija){
    if (this != &kopija) {
    Clear();
    n = 0;
    korijen = nullptr;
    head = kopija.head;
    tail = kopija.tail;

    korijen = kopirajStablo(kopija.korijen, nullptr);

    auto minimalni = Pocetak(korijen);
    auto maksimalni = Kraj(korijen);

    head = new Cvor(Tip{},minimalni );
    minimalni->ld = head;
    tail = new Cvor(Tip{}, maksimalni);
    maksimalni->dd = tail;
    }
    return *this;
}



#endif // STABLO_CPP
