#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void menu(char &scelta){
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

    cout<<"Digita un'opzione: ";
    cin>>scelta;
    cout<<"----------------------------------------------------------------------------------------------"<<endl;
}

struct dati{
    string codice_corso;
    string descrizione_corso;
    string codice_materia;
    string descrizione_materia;
    string matricola_studente;
    string cognome_studente;
    string nome_studente;
};
void leggiCSV(vector<dati> &vet){
    ifstream fin ("corsi_studenti.csv");
    dati x;
    string labels;
    getline(fin,labels);
    while(!fin.eof()){
        getline(fin,x.codice_corso,',');
        if(cc=="")  break;
        getline(fin,dc,',');
        getline(fin,cm,',');
        getline(fin,dm,',');
        getline(fin,ms,',');
        getline(fin,cs,',');
        getline(fin,ns);
        v.push_back(elem);
        }
    fin.close();
}
void aggiungi(vector<dati> &v, dati elem){
    v.push_back(elem);
}

int main()
{
    char scelta;
    menu(scelta);

    vector<dati> vet;

    while(scelta!='x'){
        switch(scelta){
            case '0':{
                leggiCSV(vet);
                break;
            }

            case '1':{

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
        menu(scelta);
    }
    return 0;
}
