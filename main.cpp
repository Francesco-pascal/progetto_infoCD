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

struct descrizione {
    string matricola_studente;
    string codice_materia;
    string codice_corso;
    string descrizione_corso;
};

map<string,string> corsi_per_matricola;
map<string,vector<string>> corsi_per_cognome;
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

bool studenteGiaPresente(vector<studente> v, studente stu) {
    for(auto elem : v) {
        if(elem.matricola_studente == stu.matricola_studente) {
            return true;
        }
    }
    return false;
}

bool materiaGiaPresente(vector<materia> v, materia mat) {
    for(auto elem : v) {
        if(elem.descrizione_materia == mat.descrizione_materia) {
            return true;
        }
    }
    return false;
}

bool corsoGiaPresente(vector<string> v, const string codice_corso) {
    for (auto &elem : v) {
        if (elem == codice_corso) {
            return true;
        }
    }
    return false;
}

void leggiCSV(vector<studente> &s, vector<materia> &m, vector<desc_corso> &dc, vector<descrizione> &de){
    ifstream fin ("corsi_studenti.csv");

    studente stu;
    materia mat;
    desc_corso desc;
    descrizione d;
    string labels;

    getline(fin,labels);
    while(!fin.eof()){
        getline(fin,desc.codice_corso,',');
        if(desc.codice_corso=="")  break;
        d.codice_corso=desc.codice_corso;
        getline(fin,desc.descrizione_corso,',');
        d.descrizione_corso=desc.descrizione_corso;
        getline(fin,mat.codice_materia,',');
        d.codice_materia=mat.codice_materia;
        getline(fin,mat.descrizione_materia,',');
        getline(fin,stu.matricola_studente,',');
        d.matricola_studente=stu.matricola_studente;
        getline(fin,stu.cognome_studente,',');
        getline(fin,stu.nome_studente);

        s.push_back(stu);
        m.push_back(mat);
        dc.push_back(desc);
        de.push_back(d);


        //punto 1
        corsi_per_matricola[stu.matricola_studente]=desc.descrizione_corso; //chiedere a chat se si può fare corsi_per_matricola[stu]=desc.descrizione_corso; in modo da fare entrambi i punti

        //punto 2
        if(!corsoGiaPresente(corsi_per_cognome[stu.cognome_studente], desc.codice_corso))    corsi_per_cognome[stu.cognome_studente].push_back(desc.codice_corso);

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
    vector<descrizione>d;


    while(scelta!='x' and scelta!='X'){
        switch(scelta){
            case '0':{
                leggiCSV(stud,mat,desc,d);
                break;
            }

            case '1':{
                string matricola;
                cout<<"Inserisci la matricola da cercare: ";
                cin>>matricola;
                cout<<matricola<<" : "<<corsi_per_matricola[matricola]<<endl<<endl;

                break;
            }
            case '2':{
                string corso;
                cout<<"Inserisci il cognome da cercare: ";
                cin>>corso;
                for(auto elem : corsi_per_cognome[corso]){
                   cout<<corso<<" : "<<elem<<endl;
                }

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

            case '8': {
                string matricola, nome, cognome, codice_materia, desc_materia;

                cout << "Inserisci matricola: ";
                cin >> matricola;

                // Verifica che la matricola non sia già presente
                bool esiste = false;
                for (auto elem : stud) {
                    if (elem.matricola_studente == matricola) {
                        esiste = true;
                        break;
                    }
                }

                if(esiste==true) {
                    cout << "Studente gia' esistente con questa matricola" << endl;
                    break;
                }

                cout << "Inserisci nome: ";
                cin >> nome;
                cout << "Inserisci cognome: ";
                cin >> cognome;
                cout << "Inserisci codice materia: ";
                cin >> codice_materia;
                cout << "Descrizione materia: ";
                cin >> desc_materia;

                // Verifica che la materia esista
                bool materia_trovata=false;
                string codice_corso_associato="";
                string descrizione_corso_associato="";

                for (auto elem : d) {
                    if (elem.codice_materia==codice_materia) {
                        codice_corso_associato=elem.codice_corso;
                        descrizione_corso_associato = elem.descrizione_corso;
                        materia_trovata=true;
                        break;
                    }
                }

                if (materia_trovata==false) {
                    cout << "Codice materia non trovato nei corsi." << endl;
                    break;
                }

                // Aggiunta dello studente
                stud.push_back({matricola, cognome, nome});

                // Aggiunta della descrizione
                desc.push_back({codice_corso_associato, descrizione_corso_associato});

                //aggiunta della materia
                mat.push_back({codice_materia,desc_materia});

                studente box_s={matricola, cognome, nome};
                materia box_m={codice_materia,desc_materia};

                //ricarica mappe
                corsi_per_matricola[matricola]=descrizione_corso_associato;

                if(!corsoGiaPresente(corsi_per_cognome[cognome], codice_corso_associato))    corsi_per_cognome[cognome].push_back(codice_corso_associato);

                if(!studenteGiaPresente(studenti_per_corso[codice_corso_associato], box_s))    studenti_per_corso[codice_corso_associato].push_back(box_s);

                if(!materiaGiaPresente(esami_per_corso[codice_corso_associato], box_m))    esami_per_corso[codice_corso_associato].push_back(box_m);

                cout << "Studente inserito con successo!" << endl;

                break;
            }
            case '9':{

                break;
            }
        }
        menu();
        cout<<"Digita un'opzione: ";
        cin>>scelta;
        cout<<endl;
        cout<<"----------------------------------------------------------------------------------------------"<<endl;
    }
    return 0;
}
