#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct dati{
    string codice_corso;
    string descrizione_corso;
    string codice_materia;
    string descrizione_materia;
    string matricola_studente;
    string cognome_studente;
    string nome_studente;

};

map<string,vector<string>> corsi_per_matricola;
map<string,vector<string>> corsi_per_cognome;
map<string,vector<dati>> studenti_per_corso; // oppure map<string,vector<dati>> studenti_per_corso; e sovrascrivere l'operatore cout<< in modo da caricare tutta la struct per poi dare in output solo quella che serve-
map<string,vector<dati>> esami_per_corso;
map<string,int> num_studenti_per_corso; //map<string,map<string,int>> num_studenti_per_corso; però non so se si può
map<string,int> num_materie_per_corso;
map<string,vector<string>> materie_per_descrizione;

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

void leggiCSV(vector<dati> &vet){
    ifstream fin ("corsi_studenti.csv");
    dati x;
    string labels;
    getline(fin,labels);
    while(!fin.eof()){
        getline(fin,x.codice_corso,',');
        if(x.codice_corso=="")  break;
        getline(fin,x.descrizione_corso,',');
        getline(fin,x.codice_materia,',');
        getline(fin,x.descrizione_materia,',');
        getline(fin,x.matricola_studente,',');
        getline(fin,x.cognome_studente,',');
        getline(fin,x.nome_studente);
        vet.push_back(x);
    }
    fin.close();
}


void carica_map(vector<dati> vet){
    for(int i=0; i<vet.size();i++){
        corsi_per_matricola[vet[i].matricola_studente].push_back(vet[i].descrizione_corso);
        corsi_per_cognome[vet[i].cognome_studente].push_back(vet[i].descrizione_corso);
        studenti_per_corso[vet[i].descrizione_corso].push_back(vet[i]);
        esami_per_corso[vet[i].descrizione_corso].push_back(vet[i]);

    }
}

int main()
{
    char scelta;
    menu();
    cout<<"Digita un'opzione: ";
    cin>>scelta;
    cout<<"----------------------------------------------------------------------------------------------"<<endl;

    vector<dati> vet;

    while(scelta!='x'){
        switch(scelta){
            case '0':{
                leggiCSV(vet);
                carica_map(vet);
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
        menu();
        cout<<"Digita un'opzione: ";
        cin>>scelta;
        cout<<"----------------------------------------------------------------------------------------------"<<endl;
    }
    return 0;
}
