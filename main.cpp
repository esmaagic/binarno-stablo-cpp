#include <iostream>
#include "stablo.h"
using namespace std;





int main() {

    Stablo<int> s;
    s = {50,20,30,10,15};


    cout<<"Iterator: "<<endl;
    for(auto it = s.Begin(); it != s.End(); it++)
        cout<<*it<<" ";
    cout<<endl;

    cout<<"Reverse iterator: "<<endl;
    for(auto it = s.RBegin(); it != s.REnd(); it++)
        cout<<*it<<" ";
    cout<<endl;

    cout<<endl;
    cout<<"Ispisi k-ti najmanji: ";
    cout<<s[1]<<endl;

    Stablo<int> s2;
    s2 = s;   //operator dodjele
    s2.Erase(10);
    //s2.Insert(5);


    cout<<endl;
    if(Stablo<int>::jePodskup(s,s2))
        cout<<"Jedno stablo je podskup drugog!"<<endl;
    else cout<<"Niti jedno stablo nije podskup drugog!"<<endl;


    Stablo<int> stablo;
    stablo = {100,50,20,60,70,30};


    cout<<endl;
    cout<<"konstruktor kopije:"<<endl;
    Stablo<int> s3 = stablo;

    for(auto it = s3.Begin(); it != s3.End(); it++)
        cout<<*it<<" ";

    cout<<endl;
    cout<<"pomjerajuci konstruktor kopije:"<<endl;
    Stablo<int> s4 = move(s2);

    for(auto it = s4.Begin(); it != s4.End(); it++)
        cout<<*it<<" ";

    cout<<endl;
    cout<<"pomjerajuci operator dodjele:"<<endl;
    Stablo<int> s5;
    s5 = move(s4);

    for(auto it = s5.Begin(); it != s5.End(); it++)
        cout<<*it<<" ";


}
