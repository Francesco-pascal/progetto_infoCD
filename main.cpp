#include <iostream>
#include <fstream>
#include <vector>
#include <map>



using namespace std;

// Struttura che rappresenta uno studente
struct studente{
    string matricola_studente, cognome_studente, nome_studente;
};

// Struttura che rappresenta una materia
struct materia{
    string codice_materia, descrizione_materia;
};

// Struttura che rappresenta un corso
struct desc_corso{
    string codice_corso, descrizione_corso;
};

// Struttura per legare insieme uno studente, una materia e un corso
struct descrizione {
    string matricola_studente;
    string codice_materia;
    string codice_corso;
    string descrizione_corso;
};

// Strutture dati per supportare le varie ricerche richieste
map<string,string> corsi_per_matricola;
map<string,vector<desc_corso>> corsi_per_cognome;
map<string,vector<studente>> studenti_per_corso;
map<string,vector<materia>> esami_per_corso;

// Funzione per visualizzare il menu
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

// Controlla se uno studente è già presente in una lista
bool studenteGiaPresente(vector<studente> v, studente stu) {
    for(auto &elem : v) {
        if(elem.matricola_studente == stu.matricola_studente) {
            return true;
        }
    }
    return false;
}

// Controlla se una materia è già presente in una lista
bool materiaGiaPresente(vector<materia> v, materia mat) {
    for(auto &elem : v) {
        if(elem.descrizione_materia == mat.descrizione_materia) {
            return true;
        }
    }
    return false;
}

// Controlla se un corso è già presente in una lista
bool corsoGiaPresente(vector<desc_corso> v, desc_corso c) {
    for (auto &elem : v) {
        if (elem.codice_corso == c.codice_corso) {
            return true;
        }
    }
    return false;
}

// Legge i dati dal file CSV e popola le strutture dati
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

        // Inserisce i dati nelle rispettive strutture
        s.push_back(stu);
        m.push_back(mat);
        dc.push_back(desc);
        de.push_back(d);


        //punto 1
        corsi_per_matricola[stu.matricola_studente]=desc.descrizione_corso;

        //punto 2
        if(!corsoGiaPresente(corsi_per_cognome[stu.cognome_studente], desc))    corsi_per_cognome[stu.cognome_studente].push_back(desc);

        //punto 3
        if(!studenteGiaPresente(studenti_per_corso[desc.codice_corso], stu))    studenti_per_corso[desc.codice_corso].push_back(stu);

        //punto 4
        if(!materiaGiaPresente(esami_per_corso[desc.codice_corso], mat))    esami_per_corso[desc.codice_corso].push_back(mat);

    }
    fin.close();
}

// Converte una stringa in minuscolo
string toLower(string s) {
    for (char &c : s){
        c = tolower(c);
    }
    return s;
}

// Converte una stringa in maiuscolo
string toUpper(string s) {
    for (char &c : s){
        c = toupper(c);
    }
    return s;
}

// Verifica se una materia esiste
void materia_trovata(string &cc, string &dc, bool &m, vector<descrizione> d, string cod){
    m=false;
    cc="";
    dc="";
    for (auto &elem : d) {
        if (elem.codice_materia==cod) {
            cc=elem.codice_corso;
            dc=elem.descrizione_corso;
            m=true;
            break;
        }
    }

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
            case '0':{  // Caricamento dati da file
                leggiCSV(stud,mat,desc,d);
                break;
            }

            case '1':{ // Cerca corsi per matricola
                string matricola;
                cout<<"Inserisci la matricola da cercare: ";
                cin>>matricola;
                cout<<matricola<<" : "<<corsi_per_matricola[matricola]<<endl<<endl;

                break;
            }
            case '2':{ // Cerca corsi per cognome
                string cognome;
                cout<<"Inserisci il cognome da cercare: ";
                cin>>cognome;
                for(auto elem : corsi_per_cognome[cognome]){
                   cout<<cognome<<" : "<<elem.descrizione_corso<<endl;
                }

                break;
            }
            case '3':{ // Elenca studenti iscritti ad un corso
                string corso;
                cout<<"Inserisci il codice corso: ";
                cin>>corso;
                corso=toUpper(corso);

                    for(auto elem : studenti_per_corso[corso]){
                        cout<<corso<<" : "<< elem.matricola_studente << " " << elem.cognome_studente << " " << elem.nome_studente << endl;
                    }
                break;
            }
            case '4':{ // Stampa dati esami di un corso
                string corso;
                cout<<"Inserisci il codice del corso: ";
                cin>>corso;
                corso=toUpper(corso);

                for (int i = 0; i < desc.size(); i++) {
                    if (desc[i].codice_corso == corso) {
                        cout << desc[i].codice_corso<<","<< desc[i].descrizione_corso<<","<< mat[i].codice_materia<<","<< mat[i].descrizione_materia<<","<< stud[i].matricola_studente<<","<< stud[i].cognome_studente<<","<< stud[i].nome_studente<<endl;
                    }
                }
                break;
            }
            case '5':{ // Conta studenti per corso
                string corso;
                cout<<"Inserisci il codice corso: ";
                cin>>corso;
                corso=toUpper(corso);

                cout<<"il corso di "<<corso<<" ha "<<studenti_per_corso[corso].size()<<" studenti "<<endl;
                break;
            }
            case '6':{ // Conta materie per corso
                string corso;
                cout<<"Inserisci il codice corso: ";
                cin>>corso;
                corso=toUpper(corso);

                cout<<"Il corso di "<<corso<<" ha "<<esami_per_corso[corso].size()<<" corsi "<<endl;
                break;
            }

            case '7':{ // Cerca materia per descrizione
                string str;
                cout<<"Inserisci un testo "<<endl;
                cin>>str;
                str=toLower(str);
                for(auto elem : mat){
                    if(toLower(elem.descrizione_materia).find(str)!=string::npos){
                        cout<<elem.descrizione_materia<<endl;
                    }
                }

                break;
            }

            case '8': { // Inserisci nuovo studente
                string codice_materia, desc_materia;
                studente matricola;

                cout << "Inserisci matricola: ";
                cin >> matricola.matricola_studente;

                //verifica che non ci sia già questa matricola
                while(studenteGiaPresente(stud,matricola)==true) {
                    cout << "Studente gia' esistente con questa matricola, ridigita:" << endl;
                    cin >> matricola.matricola_studente;
                }

                cout << "Inserisci nome: ";
                cin >> matricola.nome_studente;
                cout << "Inserisci cognome: ";
                cin >> matricola.cognome_studente;
                cout << "Inserisci codice materia: ";
                cin >> codice_materia;
                codice_materia=toUpper(codice_materia);
                cout << "Descrizione materia: ";
                cin >> desc_materia;

                // Verifica che la materia esista
                bool materia_trov;
                string codice_corso_associato;
                string descrizione_corso_associato;

                materia_trovata(codice_corso_associato,descrizione_corso_associato,materia_trov,d, codice_materia);

                while(materia_trov==false) {
                    cout<<"Codice materia non trovato nei corsi"<<endl;
                    cout << "Inserisci codice materia: ";
                    cin >> codice_materia;
                    codice_materia=toUpper(codice_materia);
                    cout << "Descrizione materia: ";
                    cin >> desc_materia;
                    materia_trovata(codice_corso_associato,descrizione_corso_associato,materia_trov,d, codice_materia);

                }

                // Aggiunta dello studente
                stud.push_back({matricola.matricola_studente, matricola.cognome_studente, matricola.nome_studente});

                // Aggiunta della descrizione
                desc.push_back({codice_corso_associato, descrizione_corso_associato});

                //aggiunta della materia
                mat.push_back({codice_materia,desc_materia});

                studente box_s={matricola.matricola_studente, matricola.cognome_studente, matricola.nome_studente};
                materia box_m={codice_materia,desc_materia};
                desc_corso box_ds={codice_corso_associato, descrizione_corso_associato};

                //ricarica mappe
                corsi_per_matricola[matricola.matricola_studente]=descrizione_corso_associato;

                if(!corsoGiaPresente(corsi_per_cognome[matricola.cognome_studente], box_ds))    corsi_per_cognome[matricola.cognome_studente].push_back(box_ds);

                if(!studenteGiaPresente(studenti_per_corso[codice_corso_associato], box_s))    studenti_per_corso[codice_corso_associato].push_back(box_s);

                if(!materiaGiaPresente(esami_per_corso[codice_corso_associato], box_m))    esami_per_corso[codice_corso_associato].push_back(box_m);

                cout << "Studente inserito con successo!" << endl;

                break;
            }
            case '9':{ // Salva i dati su file
                ofstream fout("output.csv");
                fout<<"codice_corso,descrizione_corso,codice_materia,descrizione_materia,matricola_studente,cognome_studente,nome_studente"<<endl;
                for(int i=0; i<stud.size(); i++){
                    fout<<desc[i].codice_corso<<","<<desc[i].descrizione_corso<<","<<mat[i].codice_materia<<","<<mat[i].descrizione_materia<<","<<stud[i].matricola_studente<<","<<stud[i].cognome_studente<<","<<stud[i].nome_studente<<endl;
                }
                fout.close();
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
