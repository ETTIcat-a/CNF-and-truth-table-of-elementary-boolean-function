
#include <iostream>
#include "stack"
#include "vector"
using namespace std;

string Mfunctie;
vector<string> solutie;
/*
 *******SIMBOLURI*******
v = SAU
* = ORI
' = NEGATIE

 *******LIMITARI*********
 * DUBLA NEGATIE nu este implementata
 * DOAR functii boolene elementare cu 2 variabile(x;  x,y; )
*/

bool isCorrect(string sir){

    unsigned short openP = 0, closedP = 0;
    for(unsigned long i = 0; i < sir.size(); i++){
        if(sir[i] == 'z'){
            cout<<"Programul poate contine doar doua variabile"<<endl;
            return false;
        }
        if(!(sir[i] == 'x' || sir[i] == 'y' || sir[i] == '*' || sir[i] == 'v' || sir[i] == '\'' || sir[i] =='(' || sir[i] == ')')){
           cout<<"Termen necunoscut!"<<endl;

            return false;
        }
        //***************************VERIFICARE TERMENI VECINI********************
        if(sir[i] == sir[i + 1] && sir[i] != '(' && sir[i] != ')' ) {//ex: xx in loc de xvx SI sa nu ia cazul corect : x*((x*y)vy)
            cout << "Ati omis un semn!" << endl;
            return false;
        }
        //***************************VERIFICARE PARANTEZE************************ //verifica nr de paranteze deschise si inchise
        if(sir[i] == '('){
            openP++;
        }
        if(sir[i] == ')')
            closedP++;
        /*
        if(closedP > openP){
            cout<<"Ati introdus parantezele gresit!"<<endl;  TODO
            return false;
        }
         */
    }
    if(openP != closedP) {
        cout<<"Ati introdus parantezele gresit!"<<endl;
        return false;
    }

    return true;
}

unsigned short counter = 0;
//******************************************PRIORITIZARE*PARANTEZE****************************************
unsigned short foundP(string passS, unsigned short i){

    for(unsigned short j = i+1; j < passS.size(); j++) {
        if (passS[j] == '(') {
            counter++;
            return foundP(passS, j); //functie recursiva pana gaseste paranteza corespunzatoare
        }
        if(passS[j] == ')'){
            counter--;
            // return j;
        }
        if(passS[j] == ')' && counter == 0) {
            return j;
        }
    }
}
// f= ((xvx')*(x*yv(x'vy')')v(xvy'))
/* f = (x*xvx'*xvx'*yvx'*x')
 *
 x y xvy' x'vy'  x*yv(x'vy')  xvy'       f
 0 0   1    1      0v1=1        1   1*1v1=1v1=1                     // * are prioritate
 0 1
 1 0
 1 1

 */

class Termeni{
public: // fiind un proiect care nu contribuie intr-o mare masura la nota de la acesta disciplina, nu merita efortul de a scrie totul corect(sa fac variabilele private, geters, seters and so on).
    char coef = ' ';
    bool Cneg = false; //prezumtia de nevinovatie

    void reset(){
        coef = ' ';
        Cneg = false;
    }

    bool isEmpty() {
        if(coef == ' ')
            return true;
        return false;
    }

};
class Paranteza{
public:
    unsigned short Pstart; // inceputul si finalul parantezelor(pozitiile)
    unsigned short Pstop;
    bool isNegat;
    vector<Termeni> termen;
    Termeni Taux;

    Paranteza (unsigned short start, unsigned short stop) {
        isNegat = false;
        Pstart = start;
        Pstop = stop;
        //*******************************PARANTEZE*NEGATE*CHECK*******************************
        if(Mfunctie[stop + 1] == 39)
            isNegat = true;


        for (unsigned short i = start + 1; i < stop; i++) {//TODO nu baga in vector 0 si 1
            if (Mfunctie[i] == 'x' || Mfunctie[i] == 'y' || Mfunctie[i] == 'z' || Mfunctie[i] == '1' || Mfunctie[i] == '0') { // vedem ce avem pe poz curenta, daca este x,y sau z. Aici am adaugat si pt 1 si 0
                Taux.coef = Mfunctie[i]; // il bagam ca coeficient
                if (Mfunctie[i + 1] == 39) // daca dupa el are negatie,  i-o punem
                    Taux.Cneg = true;

                if (!Taux.isEmpty())
                    if (Taux.coef != ' ')
                        termen.push_back(Taux);
                Taux.reset();
            }
        }
    }



};

char operatie(char t1, char t2, char op){
    if(op == 'v'){
        if(t1 == '0' && t2 == '0')
            return '0';
        else
            return '1';
    }
    if(op == '*'){
        if(t1 == '1' && t2 == '1')
            return '1';
        else
            return '0';

    }
}


unsigned short checkComplexitate(string s) {
    unsigned short ok = 0;
    unsigned short maxok = ok;
    for (unsigned short i = 0; i < s.size(); i++) {
        if (s[i] == 'x' )
            ok = 1;

        else if (s[i] == 'y') {
            ok = 2;
            if(ok > maxok)
                maxok = ok;
        }
        else if (s[i] == 'z' ){
            ok = 3;
            if(ok > maxok)
                maxok = ok;
        }
    }
    return maxok;
    return 0;
}

char zero_zero(Termeni t){

    if(t.coef == '1')
        return '1';
    if(t.coef == '0')
        return '0';


    if((t.coef == 'x' || t.coef == '0') && !t.Cneg )
        return '0';
    else if((t.coef == 'x' || t.coef == '0') && t.Cneg )
        return '1';

    if((t.coef == 'y' || t.coef == '1') && !t.Cneg )
        return '0';
    else if((t.coef == 'y' || t.coef == '1') && t.Cneg )
        return '1';


}
char unu_unu(Termeni t){

    if(t.coef == '1')
        return '1';
    if(t.coef == '0')
        return '0';


    if(t.coef == 'x' && !t.Cneg )
        return '1';
    else if(t.coef == 'x' && t.Cneg )
        return '0';

    if(t.coef == 'y' && !t.Cneg )
        return '1';
    else if(t.coef == 'y' && t.Cneg )
        return '0';
}
char zero_unu(Termeni t){

    if(t.coef == '1')
        return '1';
    if(t.coef == '0')
        return '0';


    if(t.coef == 'x' && !t.Cneg )
        return '0';
    else if(t.coef == 'x' && t.Cneg )
        return '1';

    if(t.coef == 'y' && !t.Cneg )
        return '1';
    else if(t.coef == 'y' && t.Cneg )
        return '0';


}
char unu_zero(Termeni t){

    if(t.coef == '1')
        return '1';
    if(t.coef == '0')
        return '0';


    if(t.coef == 'x' && !t.Cneg )
        return '1';
    else if(t.coef == 'x' && t.Cneg )
        return '0';

    if(t.coef == 'y' && !t.Cneg )
        return '0';
    else if(t.coef == 'y' && t.Cneg )
        return '1';
}

void revenire(string& s){
    for(unsigned long i = 0; i < s.size(); i++)
        if(s[i] == '~')
            s[i] = ')';

}
void golire_stiva(stack<pair<unsigned short, unsigned short> > &stiva){
    while(!stiva.empty()){
        stiva.pop();
    }
}

char neaga_rezultat_paranteza(char rezultat, bool negatie_paranteza){
    if(negatie_paranteza && rezultat == '1')
        return '0';

    if(negatie_paranteza && rezultat == '0')
        return '1';

    return rezultat;
}

int main() {
    while(true){

        cout<<"Introduceti functia booleana:"<<endl;
        cout<<"f(x,y)=";
        vector<Paranteza> paran;
        string functie, copie_functie; // este mai usor lucrul pe string-uri chiar daca la prelucrare trebuie convertit fiecare element
        stack<pair<unsigned short, unsigned short> > paranteze;
        pair<unsigned short, unsigned short> aux;

        cin >> functie;
        cout<<endl;
        while(isCorrect(functie) == false){
            cout<<"f(x,y)=";
            cin>>functie;
            cout<<endl;
        }

        functie.insert(0,1,'(');
        functie.insert(functie.size(),1,')'); // incadram toata functia un paranteze ca sa poata fi vazut ca paranteza finala si sa se execute calcule pe ea
        unsigned short as = 0;

//************************************************CREARE*OBIECTE*PARANTEZE**********************************
        Mfunctie = functie;
        copie_functie = functie;
        for (unsigned long i = 0; i < functie.size(); i++) {

            if (functie[i] == '(') {
                counter++;
                aux.first = i;
                aux.second = foundP(functie, i);
                functie[aux.second] = '~';
                paranteze.push(aux);
            }

        }
        revenire(functie);


        stack<pair<unsigned short, unsigned short> > Scopy = paranteze;
        while (!Scopy.empty()) {
            Paranteza Paux(Scopy.top().first, Scopy.top().second);

            paran.push_back(Paux);

            Scopy.pop();
        }
//************************************************CREARE*OBIECTE*PARANTEZE**********************************
        char firsT;
        char seconT;
        if(2 >=  checkComplexitate(functie)){ // daca exista doar doi termeni
            for(unsigned short q = 0; q < 4; q++) {

//vom lua combinatia x = 0, y = 0
//luam toate parantezele
                for (unsigned long i = 0; i < paran.size(); i++) {
                    i = 0;
                    //*******************************COMBINATIILE**************************

// TODO sunt sanse ca asta sa poata fi mutat in for, mai jos, check it later

                    unsigned long j = paran[i].Pstart;
                    while (functie.size() > 1 || paran[i].termen.size() > 2) {





                        if(q == 0)
                            firsT = zero_zero(paran[i].termen[0]);
                        else if(q == 1)
                            firsT = zero_unu(paran[i].termen[0]);
                        else if(q == 2)
                            firsT = unu_zero(paran[i].termen[0]);
                        else if(q == 3)
                            firsT = unu_unu(paran[i].termen[0]);






                        if (functie[j] == 'v' || functie[j] == '*') {
                            char Moperator = functie[j]; // A SE FOLOSI ACESTA VARIABILA SI NU DIRECT functie[j] pentru ca acesta valore se va schimba dupa linia 388
                            //*******************************COMBINATIILE**************************
                            if(q == 0)
                                seconT = zero_zero(paran[i].termen[1]);
                            else if(q == 1)
                                seconT = zero_unu(paran[i].termen[1]);
                            else if(q == 2)
                                seconT = unu_zero(paran[i].termen[1]);
                            else if(q == 3)
                                seconT = unu_unu(paran[i].termen[1]);
                            char Maux = operatie(firsT, seconT, Moperator);

                            if (paran[i].termen.size() > 2) {
                                if (paran[i].termen[0].Cneg && paran[i].termen[1].Cneg){
                                    functie.erase(2, 1); // prima negatie
                                    functie.erase(4, 1); // a doua negatie

                                    functie.erase(1, 3); // termenii + semn
                                    functie.insert(1, 1, Maux);
                                }
                                else {
                                    if (paran[i].termen[0].Cneg) //stergem negatia primului termen
                                        functie.erase(j - 2, 1);

                                    if (paran[i].termen[1].Cneg)//stergem negatia celui de-al doilea termen
                                        functie.erase(j + 2, 1);


                                    functie.erase(j - 1, 3);

                                    functie.insert(j - 1, 1, Maux);
                                }


                                Maux = operatie(firsT, seconT, Moperator);
                            }
                            if (paran[i].termen.size() == 2) { // a gasit prima operatie dar trb sa vedem daca sunt mai multi termeni in pqranteza respectiva pt ca la final vom sterge parantezele dupa prima operatie, ceilalti termeni fiind stersi!!

                                Maux = neaga_rezultat_paranteza(Maux, paran[i].isNegat);

                                if (paran[i].isNegat)
                                    functie.erase(paran[i].Pstart, paran[i].Pstop - paran[i].Pstart + 2);
                                else
                                    functie.erase(paran[i].Pstart, paran[i].Pstop - paran[i].Pstart +
                                                                   1); // daca paranteza este negata, sa ii stearga si negatia


                                functie.insert(paran[i].Pstart, 1, Maux);
                            }
                            firsT = Maux;
                            //************************************************CREARE*OBIECTE*PARANTEZE**********************************
                            paran.clear();
                            golire_stiva(paranteze);

                            for (as = 0; as < functie.size(); as++) {

                                if (functie[as] == '(') {
                                    counter++;
                                    aux.first = as;
                                    aux.second = foundP(functie, as);
                                    functie[aux.second] = '~';
                                    paranteze.push(aux);
                                }

                            }
                            Mfunctie.clear();
                            revenire(functie);
                            Mfunctie = functie;
                            //   cout << functie << endl << Mfunctie << endl << endl; //for debugging
                            Scopy = paranteze;

                            while (!Scopy.empty()) {
                                Paranteza Paux(Scopy.top().first, Scopy.top().second);

                                paran.push_back(Paux);

                                Scopy.pop();
                            }
                            j = paran[i].Pstart;
                        }
                        j++;
                        if(functie.size() == 1)
                            solutie.push_back(functie);
                    }
                }
                functie = copie_functie;

                //************************************************CREARE*OBIECTE*PARANTEZE**********************************
                paran.clear();
                golire_stiva(paranteze);

                for (as = 0; as < functie.size(); as++) {

                    if (functie[as] == '(') {
                        counter++;
                        aux.first = as;
                        aux.second = foundP(functie, as);
                        functie[aux.second] = '~';
                        paranteze.push(aux);
                    }

                }
                Mfunctie.clear();
                revenire(functie);
                Mfunctie = functie;
                //  cout << functie << endl << Mfunctie << endl << endl; //debugging
                Scopy = paranteze;

                while (!Scopy.empty()) {
                    Paranteza Paux(Scopy.top().first, Scopy.top().second);

                    paran.push_back(Paux);

                    Scopy.pop();
                }
            }
        }
        copie_functie.erase(0,1);
        copie_functie.erase(copie_functie.size() - 1,1);

        if(checkComplexitate(functie) == 2) {
            cout << "x    |    y    |    f   |" << endl;

            cout << "0    |    0    |    " << solutie[0] << "   |" << endl;

            cout << "0    |    1    |    " << solutie[1] << "   |" << endl;

            cout << "1    |    0    |    " << solutie[2] << "   |" << endl;

            cout << "1    |    1    |    " << solutie[3] << "   |" << endl;

            // (xvx')*(x*yv(x'vy')')v(xvy')
//    x*xvx'*xvx'*yvx'*x'
//    x'*y'vx'*yvx*y'vx*y

            cout << endl << "Forma canonica disjunctiva este:  ";
            bool isSolo = false;
            for (unsigned short i = 0; i < 4; i++) {
               // cout<<solutie[i];
              // if(solutie[i] == "1" && solutie[i-1] == "1")
                 //  cout<<" v ";

                if (solutie[i] == "1") {
                    if(isSolo)
                        cout<<" v ";

                    isSolo = true;

                    if (i == 0)
                        cout << "x * y";

                    if (i == 1)
                        cout << "x * y'";

                    if (i == 2)
                        cout << "x' * y";

                    if (i == 3)
                        cout << "x' * y'";

                }
            }
           // return 0;
            cout << endl << endl << "Introduceti ala functie" << endl;
            solutie.clear();
        }

//(xvx')*(x*yv(x'vy')')v(xvy')'
    }
    return 0;
}
