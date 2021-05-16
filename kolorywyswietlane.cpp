#include "kolorywyswietlane.h"
#include<windows.h>
using namespace std;
void zie(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),160);
}
void zol(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),224);
}
void bia(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
}
void nie(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),144);
}
void cze(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),64);
}
void roz(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),208);
}
void kol(int a){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a*16);
}
void czar(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}
