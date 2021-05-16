#include "szescianrubika.h"
#include "kolorywyswietlane.h"
using std::cout;
using std::cin;
using std::endl;
int interpretujRozbij(string &nap);
void rubic::operator=(const rubic & org)
{
    resizeme(org.N);
    for(int i=0;i<6;i++)
        for(int j=0;j<N;j++)
            for(int k=0;k<N;k++)
                sciana[i][j][k]=org.sciana[i][j][k];
}

void rubic::U2(int ile)
{
    if(ile>=N){y2();return;}
    if(ile<=0)return;
    for(int i=0;i<3;i++)U(ile);
}
void rubic::freeplay(int x,int y)
{
    string polecenie;
    cout<<"Wybierz wielkosc kostki:\n";
    int newN;
    cin>>newN;
    resizeme(newN);
    reset();
    for(int i=0;i<10;i++)
    {
        randomise();//10 prob przetasowania kostki, jesli po 10 ciagle jest ulozona, to albo masz super szczescie, albo cos sie spierdolilo
        if(!isSolved())break;
        if(i==9)
        {
            cout<<"nie udalo sie pomieszac kostki\n";
            return;//todolist
        }
    }
    while(!isSolved())
    {
        system("cls");
        wyswietl(x,y);
        cin>>polecenie;//todolist
        interpretuj(polecenie);
    }
    system("cls");
    wyswietl();
    cout<<endl<<"Gratulacje! Ulozyl*s kostke "<<N<<"x"<<N<<"x"<<N<<"!\n";
}
void rubic::randomise()
{
    if(N<=1)return;
    for(int i=0;i<N*100;i++)
    {
        switch(rand()%6)//losuje ruch jedna z 6 scianek
        {
        case 0:
            U(1+rand()%(N-1));//losuje iloma rzedami ruszyc od najbardziej zewnetrznej. liczby mniejsze niz 1, ani wieksze niz N-1 nie mialyby sensu
            break;
        case 1:
            F(1+rand()%(N-1));
            break;
        case 2:
            R(1+rand()%(N-1));
            break;
        case 3:
            L(1+rand()%(N-1));
            break;
        case 4:
            B(1+rand()%(N-1));
            break;
        case 5:
            D(1+rand()%(N-1));
            break;

        }
    }
}
bool rubic::isSolved() const
{
    //uznalem ze gdyby wszystkie pola na kazdej scianie mialy taki sam kolor, ale dany kolor powtarzalby sie na wiecej niz jednej scianie (np 2 zolte papieskie sciany) to kostka nie jest ulozona poprawnie bo nie ma jednoznacznosci. w tej wersji programu nie ma to znaczenia ale byc moze w przyszlosci zaimplementuje wczytywanie kostki z klawiatury
    int itemp;//zmienna tymczasowa, przechowuje kolor z lewego gornego wierzcholka kazdej sciany i sprawdza go z ta sciana oraz wierzcholkami na innych scianach
    for(int i=0;i<6;i++)//na kazdej scianie
    {
        itemp=sciana[i][0][0];
        for(int j=0;j<N;j++)//sprawdz wierzcholek z calym rzedem, czyli
        {
            for(int k=0;k<N;k++)//kazdym polu w tym rzedzie
            {
                if(sciana[i][j][k]!=itemp)return false;//jak kolory sie roznia, nie jest ulozone
            }
        }
        for(int j=i+1;j<6;j++)if(sciana[j][0][0]==itemp)return false;//jesli kolor na aktualnej scianie i ktorejkolwiek kolejnej jest taki sam, nie jest ulozona poprawnie

    }
    return true;//jak nie wyszlo wczesniej, znaczy ze jest ulozona
}
int interpretujRozbij(string &nap)
{
    if(nap.length()==2)if(nap[1]=='\'')return 1;
    if(nap.length()==1)return 1;

    int itemp=0;
    for(unsigned int i=1;i<nap.length();i++)
    {
        if(nap[i]<'0'||nap[i]>'9')continue;
        itemp*=10;
        itemp+=(nap[i]-48);
    }

    return itemp;
}

void rubic::interpretuj(string nap)//podana komenda ma postac X'1 gdzie X to jedna z liter F(ront),B(ack),U(p),D(own),L(eft),R(ight), apostrof moze, ale nie musi wystepowac i oznacza ruch w strone przeciwna,1 oznacza liczbe, iloma rzedami nalezy poruszyc, przy braku argumentu, rusza tylko najbardziej skrajnym (1)
{
    int itemp=interpretujRozbij(nap);//wyluskuje liczbe z napisu
    switch(nap[0])
    {
    case 'u':
    case 'U':
        if(nap.length()==1)U();
        else if(nap[1]=='\'')U2(itemp);
        else U(itemp);
        return;
        case 'd':
    case 'D':
        if(nap.length()==1)D();
        else if(nap[1]=='\'')D2(itemp);
        else D(itemp);
        return;
        case 'r':
    case 'R':
        if(nap.length()==1)R();
        else if(nap[1]=='\'')R2(itemp);
        else R(itemp);
        return;
        case 'l':
    case 'L':
        if(nap.length()==1)L();
        else if(nap[1]=='\'')L2(itemp);
        else L(itemp);
        return;
        case 'f':
    case 'F':
        if(nap.length()==1)F();
        else if(nap[1]=='\'')F2(itemp);
        else F(itemp);
        return;
        case 'b':
    case 'B':
        if(nap.length()==1)B();
        else if(nap[1]=='\'')B2(itemp);
        else B(itemp);
        return;
    case 'x':
    case 'X':
        if(nap.length()==1)x();
        else x2();
        return;
    case 'y':
    case 'Y':
        if(nap.length()==1)y();
        else y2();
        return;
    case 'z':
    case 'Z':
        if(nap.length()==1)z();
        else z2();
        return;

    default:
        //todolist
        return;


    }
}
void rubic::F(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){z();return;}
    x();
    U(ile);
    x2();
}
void rubic::F2(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){z2();return;}
    for(int i=0;i<3;i++)F(ile);
}
void rubic::R(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){x();return;}
    z2();
    U(ile);
    z();
}
void rubic::R2(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){x2();return;}
    for(int i=0;i<3;i++)R(ile);
}
void rubic::L(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){x2();return;}
    z();
    U(ile);
    z2();
}
void rubic::L2(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){x();return;}
    for(int i=0;i<3;i++)L(ile);
}
void rubic::B(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){z2();return;}
    x2();
    U(ile);
    x();
}
void rubic::B2(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){z();return;}
    for(int i=0;i<3;i++)B(ile);
}
void rubic::D(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){y2();return;}
    x();
    x();
    U(ile);
    x();
    x();
}
void rubic::D2(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){y();return;}
    for(int i=0;i<3;i++)D(ile);
}
void rubic::x()
{//wszystkie skladowe sa zabezpieczone przed N<=0
    int itemp;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
    {
        itemp=sciana[0][i][j];
        sciana[0][i][j]=sciana[1][i][j];
        sciana[1][i][j]=sciana[5][i][j];
        sciana[5][i][j]=sciana[4][i][j];
        sciana[4][i][j]=itemp;
    }
    scianaClockwise(2);
    scianaCounterClockwise(3);


    scianaClockwise(4);//orientacja tylniej i dolnej sciany, bo po zwyczajnym przypisaniu sa do gory nogami
    scianaClockwise(4);
    scianaClockwise(5);
    scianaClockwise(5);

}
void rubic::x2()
{//wszystkie skladowe sa zabezpieczone przed N<=0
    for(int i=0;i<3;i++)x();
}
void rubic::y()
{//wszystkie skladowe sa zabezpieczone przed N<=0
    int itemp;
    scianaClockwise(0);
    scianaCounterClockwise(5);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
    {
        itemp=sciana[1][i][j];
        sciana[1][i][j]=sciana[2][i][j];
        sciana[2][i][j]=sciana[4][i][j];
        sciana[4][i][j]=sciana[3][i][j];
        sciana[3][i][j]=itemp;
    }
}
void rubic::y2()
{//wszystkie skladowe sa zabezpieczone przed N<=0
    for(int i=0;i<3;i++)y();
}
void rubic::z()
{//wszystkie skladowe sa zabezpieczone przed N<=0
    int itemp;
    scianaClockwise(1);
    scianaCounterClockwise(4);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
    {
        itemp=sciana[0][i][j];
        sciana[0][i][j]=sciana[3][i][j];
        sciana[3][i][j]=sciana[5][i][j];
        sciana[5][i][j]=sciana[2][i][j];
        sciana[2][i][j]=itemp;
    }
    scianaClockwise(0);//orientacja
    scianaClockwise(2);
    scianaClockwise(3);
    scianaClockwise(5);

}
void rubic::z2()
{//wszystkie skladowe sa zabezpieczone przed N<=0
    for(int i=0;i<3;i++)z();
}
void rubic::U(int ile)
{
    if(ile<=0)return;//todolist
    if(ile>=N){y();return;}
    int itemp;
    scianaClockwise(0);
    for(int i=0;i<N;i++)
        for(int j=0;j<ile;j++)
        {
            itemp=sciana[1][j][i];
            sciana[1][j][i]=sciana[2][j][i];
            sciana[2][j][i]=sciana[4][j][i];
            sciana[4][j][i]=sciana[3][j][i];
            sciana[3][j][i]=itemp;
        }
}
void rubic::scianaCounterClockwise(int nr)
{
    if(nr<0||nr>6)return;//todolist
    for(int i=0;i<3;i++)scianaClockwise(nr);
}
void rubic::scianaClockwise(int nr)
{
    if(nr<0||nr>6)return;//todolist
    if(N<=1)return;
    int itemp;
    for(int i=0;i<N/2;i++)
        for(int j=i;j<N-1-i;j++)
    {
        itemp=sciana[nr][i][j];
        sciana[nr][i][j]=sciana[nr][N-j-1][i];
        sciana[nr][N-1-j][i]=sciana[nr][N-1-i][N-1-j];
        sciana[nr][N-1-i][N-1-j]=sciana[nr][j][N-1-i];
        sciana[nr][j][N-1-i]=itemp;
    }

}
void rubic::reset()
{
    if(N<=0)return;//todolist
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            {
                 sciana[0][i][j]=14;//zolta gora
                  sciana[1][i][j]=9;//nieb przod
                   sciana[2][i][j]=13;//fiol prawo
                    sciana[3][i][j]=4;//czer lew
                     sciana[4][i][j]=10;//ziel tyl
                      sciana[5][i][j]=15;//bia dol
            }

}
void rubic::wyswietlLinie(int sciana,int nr,int X) const
{//N moze byc mniejsze niz 1, wtedy po prostu nic sie nie wyswietli
    for(int i=0;i<N;i++)
    {
        kol(this->sciana[sciana][nr][i]);
        for(int j=0;j<X;j++)cout<<" ";
    }
    czar();
}
void rubic::wyswietl(int x,int y) const
{
    if(N<=0)return;//todolist
    if(x==0)x=std::max(1,8/N);//skaluje szerokosc obrazu, domyslnie 4 razy prz 2x2x2, 2 razy przy N=3 i 4, bez skalowania dla 5 i wiecej
    if(y==0)y=std::max(1,8/N);//jak wyzej, ale na wysokosc

    for(int i=0;i<N;i++)
        {
            for(int j=0;j<y;j++){
                for(int i=0;i<N*x;i++)cout<<" ";
                wyswietlLinie(0,i,x);
                cout<<endl;}//sciana 0
        }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<y;j++){
        wyswietlLinie(3,i,x);//sciana 3 (lewa)
        wyswietlLinie(1,i,x);//sciana 1 (przod)
        wyswietlLinie(2,i,x);//sciana 2 (prawa)
        wyswietlLinie(4,i,x);//sciana 4 (tyl)
        cout<<endl;}
    }
    for(int i=0;i<N;i++)
        {
            for(int j=0;j<y;j++){
            for(int i=0;i<N*x;i++)cout<<" ";
            wyswietlLinie(5,i,x);//sciana 5 (dolna)
            cout<<endl;}
        }
}
rubic::rubic(int wielkosc)
{

resizeme(wielkosc);

reset();
}
rubic::rubic(rubic &wzor)
{
    resizeme(wzor.N);
    if(N>0)
    {
        for(int i=0;i<6;i++)
            for(int j=0;j<N;j++)
                for(int k=0;k<N;k++)
                    sciana[i][j][k]=wzor.sciana[i][j][k];
    }
}
void rubic::resizeme(int newN)
{
    if(N==newN) return;
    if(N>0)
    {
        for(int i=0;i<6;i++)
            {
                for(int j=0;j<N;j++)
                    delete [] sciana[i][j];
                delete [] sciana[i];

            }
            delete [] sciana;
    }
    N=newN;
    if(N<1){sciana=nullptr;return;}

    sciana=new int** [6];
    for(int i=0;i<6;i++)
    {
        sciana[i]=new int*[N];
        for(int j=0;j<N;j++) sciana[i][j]=new int [N];
    }
    return;
}
rubic::~rubic()
{
    if(N>0) resizeme(0);
}
