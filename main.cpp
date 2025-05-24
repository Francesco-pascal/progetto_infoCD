#include <iostream>
#include <fstream>
#include <vector>
#include <map>


using namespace std;

struct studente{
    string matricola_studente, cognome_studente, nome_studente;
};

struct materia{
    string codice_materia, descrizione_materia;
};

struct desc_corso{
    string codice_corso, descrizione_corso;
};

map<string,string> corsi_per_matricola;
map<string,string> corsi_per_cognome;
map<string,vector<studente>> studenti_per_corso;
map<string,vector<materia>> esami_per_corso;


void menu(){
    cout<<"==============Gestione universitaria=============="<<endl;
    cout<<"=                                                ="<<endl;
    cout<<"=    0. Caricamento dati da un file              ="<<endl;
    cout<<"=    1. Cerca corsi di uno studente(matricola)   ="<<endl;
    cout<<"=    2. Cerca corsi di uno studente(cognome)     ="<<endl;
    cout<<"=    3. Elenca studenti iscritti ad un corso     ="<<endl;
    cout<<"=    4. Stampa dati esami di un corso            ="<<endl;
    cout<<"=    5. Numero di studenti per corso             ="<<endl;
    cout<<"=    6. Numero di materie per corso              ="<<endl;
    cout<<"=    7. Cerca materia per descrizione            ="<<endl;
    cout<<"=    8. Inserisci nuovo studente                 ="<<endl;
    cout<<"=    9. Salva i dati su file                     ="<<endl;
    cout<<"=    X. Esci                                     ="<<endl;
    cout<<"=                                                ="<<endl;
    cout<<"=================================================="<<endl;

}

bool studenteGiaPresente(vector<studente> &v, studente &stu) {
    for(auto& elem : v) {
        if(elem.matricola_studente == stu.matricola_studente) {
            return true;
        }
    }
    return false;
}

bool materiaGiaPresente(vector<materia> &v, materia &mat) {
    for(auto& elem : v) {
        if(elem.descrizione_materia == mat.descrizione_materia) {
            return true;
        }
    }
    return false;
}

void leggiCSV(vector<studente> &s, vector<materia> &m, vector<desc_corso> &dc){
    ifstream fin ("corsi_studenti.csv");

    studente stu;
    materia mat;
    desc_corso desc;
    string labels;

    getline(fin,labels);
    while(!fin.eof()){
        getline(fin,desc.codice_corso,',');
        if(desc.codice_corso=="")  break;
        getline(fin,desc.descrizione_corso,',');
        getline(fin,mat.codice_materia,',');
        getline(fin,mat.descrizione_materia,',');
        getline(fin,stu.matricola_studente,',');
        getline(fin,stu.cognome_studente,',');
        getline(fin,stu.nome_studente);

        s.push_back(stu);
        m.push_back(mat);
        dc.push_back(desc);

        //punto 1
        corsi_per_matricola[stu.matricola_studente]=desc.descrizione_corso; //chiedere a chat se si può fare corsi_per_matricola[stu]=desc.descrizione_corso; in modo da fare entrambi i punti

        //punto 2
        corsi_per_cognome[stu.cognome_studente]=desc.descrizione_corso;

        //punto 3
        if(!studenteGiaPresente(studenti_per_corso[desc.codice_corso], stu))    studenti_per_corso[desc.codice_corso].push_back(stu);

        //punto 4
        if(!materiaGiaPresente(esami_per_corso[desc.codice_corso], mat))    esami_per_corso[desc.codice_corso].push_back(mat);

    }
    fin.close();
}

int main()
{
    char scelta;
    menu();
    cout<<"Digita un'opzione: ";
    cin>>scelta;
    cout<<"----------------------------------------------------------------------------------------------"<<endl;

    vector<studente> stud;
    vector<materia> mat;
    vector<desc_corso> desc;


    while(scelta!='x' and scelta!='X'){
        switch(scelta){
            case '0':{
                leggiCSV(stud,mat,desc);
                break;
            }

            case '1':{
                string matricola;
                cout<<"Inserisci la matricola da cercare: ";
                cin>>matricola;
                cout<<matricola<<" : "<<corsi_per_matricola[matricola]<<endl<<endl;

                break;
            }
            case '2':{ //ricontrollare i cognomi, forse è da fare una map<string,vector<string>>
                string corso;
                cout<<"Inserisci il cognome da cercare: ";
                cin>>corso;
                cout<<corso<<" : "<<corsi_per_cognome[corso]<<endl<<endl;
                break;
            }
            case '3':{
                string corso;
                cout<<"Inserisci il corso: ";
                cin>>corso;

                    for(auto elem : studenti_per_corso[corso]){
                        cout<<corso<<" : "<< elem.matricola_studente << " " << elem.cognome_studente << " " << elem.nome_studente << endl;
                    }
                break;
            }
            case '4':{
                string corso;
                cout<<"Inserisci l'esame del corso: ";
                cin>>corso;

                for(auto elem : esami_per_corso[corso]){
                    cout<<corso<<" : "<< elem.descrizione_materia << endl;
                }
                break;
            }
            case '5':{
                string corso;
                cout<<"Inserisci il corso: ";
                cin>>corso;

                cout<<"il corso di "<<corso<<" ha "<<studenti_per_corso[corso].size()<<" studenti "<<endl;
                break;
            }
            case '6':{
                string corso;
                cout<<"Inserisci il corso: ";
                cin>>corso;

                cout<<"Il corso di "<<corso<<" ha "<<esami_per_corso[corso].size()<<" corsi "<<endl;
                break;
            }
            case '7':{

                break;
            }
            case '8':{
                studente s;
                materia m;
                desc_corso c;

                cout<<"Inserisci il codice del corso: "<<endl;
                cin>>c.codice_corso;
                cout<<"Inserisci la descizione del corso: "<<endl;
                cin>>c.descrizione_corso;
                desc.push_back(c);

                cout<<"Inserisci il codice della materia: "<<endl;
                cin>>m.codice_materia;
                cout<<"Inserisci la descrizione della materia: "<<endl;
                cin>>m.descrizione_materia;
                mat.push_back(m);

                cout<<"Inserisci la matricola: "<<endl;
                cin>>s.matricola_studente;
                cout<<"Inserisci il cognome: "<<endl;
                cin>>s.cognome_studente;
                cout<<"Inserisci il nome: "<<endl;
                cin>>s.nome_studente;
                stud.push_back(s);

                break;
            }
            case '9':{

                break;
            }
        }
        menu();
        cout<<"Digita un'opzione: ";
        cin>>scelta;
        cout<<"----------------------------------------------------------------------------------------------"<<endl;
    }
    return 0;
}
