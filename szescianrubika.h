#ifndef kosteczka
#define kosteczka
#include <iostream>
using std::string;


class rubic
{
private:
    int ***sciana;// w kolejnosci: {gora,przod,prawo,lewo,tyl,dol,} {1rzad,2rzad... n-ty rzad,}   {1 element w rzedzie,2 element w rzedzie... n-ty element w rzedzie}
    void wyswietlLinie(int sciana,int nrLini, int mnoznikX=0) const;
    void interpretuj(string polecenie);
public:
    rubic(int wielkosc=0);//konstruktor dla braku argumentow lub samej wielkosci kostki
    rubic(rubic &wzor);//konstruktor kopiujacy
    ~rubic();//upewnia sie ze ***sciana jest usunieta i ustawiona na nullptr
    int N=0;//aktualny rozmiar kostki
    void resizeme(int newN);
    void wyswietl(int mnoznikX=0,int mnoznikY=0) const;
    void reset();
    void scianaClockwise(int nrSciany);
    void scianaCounterClockwise(int nrSciany);
    void U(int ile=1);
    void x();
    void y();
    void z();
    void x2();
    void y2();
    void z2();
    void U2(int ile=1);
    void F(int ile=1);
    void F2(int ile=1);
    void B(int ile=1);
    void B2(int ile=1);
    void R(int ile=1);
    void R2(int ile=1);
    void L(int ile=1);
    void L2(int ile=1);
    void D(int ile=1);
    void D2(int ile=1);
    bool isSolved() const;
    void randomise();
    void freeplay(int x=0,int y=0);
    void operator =(const rubic & oryginal);
};
#endif // kosteczka
