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
/*map<string,vector<string>> corsi_per_cognome;
map<string,vector<dati>> studenti_per_corso;
map<string,vector<dati>> esami_per_corso;
map<string,int> num_studenti_per_corso;
map<string,int> num_materie_per_corso;
map<string,vector<string>> materie_per_descrizione;*/


void menu(){
    cout<<"=====Gestione universitaria====="<<endl;
    cout<<"0.Caricamento dati da un file"<<endl;
    cout<<"1.Cerca corsi di uno studente(matricola)"<<endl;
    cout<<"2.Cerca corsi di uno studente(cognome)"<<endl;
    cout<<"3.Elenca studenti iscritti ad un corso"<<endl;
    cout<<"4.Stampa dati esami di un corso"<<endl;
    cout<<"5.Numero di studenti per corso"<<endl;
    cout<<"6.Numero di materie per corso"<<endl;
    cout<<"7.Cerca materia per descrizione"<<endl;
    cout<<"8.Inserisci nuovo studente"<<endl;
    cout<<"9.Salva i dati su file"<<endl;
    cout<<"X.Esci"<<endl;

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

        corsi_per_matricola[stu.matricola_studente]=desc.descrizione_corso;


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


    while(scelta!='x'){
        switch(scelta){
            case '0':{
                leggiCSV(stud,mat,desc);
                break;
            }

            case '1':{
                string m;
                cout<<"Inserisci la matricola da cercare: ";
                cin>>m;
                cout<<m<<" : "<<corsi_per_matricola[m]<<endl<<endl;

                break;
            }
            case '2':{

                break;
            }
            case '3':{

                break;
            }
            case '4':{

                break;
            }
            case '5':{

                break;
            }
            case '6':{

                break;
            }
            case '7':{

                break;
            }
            case '8':{

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
