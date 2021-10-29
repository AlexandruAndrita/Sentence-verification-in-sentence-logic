#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ifstream fin("citire.in");

char s[256];
char caractere[] = {"QWERTYUIOPASDFGHJKLZXCVBNM&~|-=() "};
char conectori[]= {"&~|-=()"};
char conectoriFaraParanteze[]={"&~|-="};
char propatomice[]= {"QWERTYUIOPASDFGHJKLZXCVBNM"};

void instructiuni()
{
    cout<<"Cateva reguli de utilizare:\n";
    cout<<"-pentru AND se va citi '&';\n";
    cout<<"-pentru NOT se va citi '~';\n";
    cout<<"-pentru OR se va citi '|';\n";
    cout<<"-pentru IMPLICA se va citi '-';\n";
    cout<<"-pentru ECVHIVALENT se va citi '=';\n";
    cout<<"-pentru PARANTEZA DESCHISA se va citi '(';\n";
    cout<<"-pentru PARANTEZA INCHISA se va citi ')';\n";
    cout<<"-pentru PROPOZITIILE ATOMICE se vor folosi litere simple (mari sau mici), NU litere cu indecsi, NU litere dublate.\n";
    cout<<"\n\n\n";
}

void citire()
{
    cout<<"Introduceti expresia dorita:\n\n";
    cin.get(s,256);
    cout<<"\n\n";
}

void validareInput()
{
    int n=strlen(s),deschise=0,inchise=0,operatori=0,propozitii=0;
    for(int i=0; i<n; i++)
    {
        if(s[i]>='a' && s[i]<='z')
        {
            cout<<"Expresia introdusa nu este formula propozitionala\n";
            cout<<"Au fost introduse caractere mici "<<s[i]<<" ;acestea nu sunt considerate propozitii atomice";
            exit(0);
        }
        if(strchr(conectoriFaraParanteze,s[i]))
            operatori++;
        if(strchr(propatomice,s[i]))
            propozitii++;
        if(s[i]=='(')
        {
            deschise++;
        }
        if(s[i]==')')
        {
            ///daca expresia nu are paranteze deschide inainte de cele inchise, nu este valida
            if(deschise==0)
            {
                cout<<"Expresia introdusa nu este formula propozitionala\n";
                cout<<"A fost introdusa o paranteza inchisa inainte de una deschisa\n";
                exit(0);
            }
            inchise++;
        }
        ///daca sunt introduse caractere neacceptate, expresia nu este valida
        if(strchr(caractere,s[i])==0)
        {
            cout<<"Expresia introdusa nu este formula propozitionala\n";
            cout<<"Caracterul "<<s[i]<<" nu este permis in expresie\n";
            exit(0);
        }
    }
    ///daca numarul de paranteze deschise nu corespunde cu cele inchise, expresia nu este valida
    if(inchise!=deschise)
    {
        cout<<"Expresia introdusa nu este formula propozitionala\n";
        cout<<"Numarul de paranteze inchise si numarul de paranteze deschise nu coincide\n";
        exit(0);
    }
    //else
    //{
        //if(deschise!=operatori && inchise==deschise)
        //{
            //cout<<"Expresia introdusa nu este formula propozitionala\n";
            //cout<<"Expresia nu are destule paranteze astfel incat sa indeplineasca forma strica\n";
            //exit(0);
        //}
    //}
    ///daca expresia are propoziitii si nu are operatori sau invers, nu este valida
    if(propozitii!=0 && operatori==0)
    {
        cout<<"Expresia introdusa nu este formula propozitionala\n";
        cout<<"Expresia nu contine conectori logici\n";
        exit(0);
    }
    if(propozitii==0 && operatori!=0)
    {
        cout<<"Expresia introdusa nu este formula propozitionala\n";
        cout<<"Expresia nu contine propozitii atomice\n";
        exit(0);
    }
    if(inchise==deschise && propozitii==1 && operatori==0)
    {
        cout<<"Expresia introdusa nu este formula propozitionala\n";
        cout<<"Expresia este de forma: ( P ), iar aceasta forma nu este considerata formula bine formata.\n";
        exit(0);
    }

    ///daca s[i] este paranteza deschisa, cobor in arbore, altfel la paranteza inchisa urc;
    ///daca s[i] este propozitie atomica urc in arbore;
    ///daca s[i] este conector cobor in arbore;
    ///daca s[i] este conector, poate fi urmat doar de paranteza deschisa sau de propozitie atomica
    ///daca s[i] este propozitie atomica poate fi urmat doar de un conector sau de o paranteza inchisa

    for(int i=0; i<n; i++)
    {
        if(s[i]=='(')
        {
            if(s[i+1]==')' && strchr("&|-=",s[i+1])==0 && strchr(propatomice,s[i+1])==0)
            {
                cout<<"Expresia nu este formula propozitionala\n";
                exit(0);
            }
        }
        if(strchr("&|-=",s[i]))
        {
            if(strchr(propatomice,s[i+1])==0 && s[i+1]!='(')
            {
                cout<<"Expresia nu este formula propozitionala\n";
                exit(0);
            }
        }
        if(s[i]=='~')
        {
            if(strchr(propatomice,s[i+1])==0 && s[i+1]!='(')
            {
                cout<<"Expresia nu este formula propozitionala\n";
                exit(0);
            }
        }
        if(strchr(propatomice,s[i]))
        {
            if(strchr("&|-=",s[i+1])==0 && s[i+1]!=')')
            {
                cout<<"Expresia nu este formula propozitionala\n";
                exit(0);
            }
        }
    }
    cout<<"Expresia este formula propozitionala\n";
}

int main()
{
    instructiuni();
    citire();
    validareInput();
    return 0;
}
