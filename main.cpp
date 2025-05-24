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
map<string,vector<studente>> esami_per_corso;
/*map<string,map<string,int>> num_studenti_per_corso;
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

bool studenteGiaPresente(vector<studente> &v, studente &stu) {
    for(auto& s : v) {
        if(s.matricola_studente == stu.matricola_studente) {
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
        esami_per_corso[mat.codice_materia].push_back(stu);



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
                    string esame;
                    cout<<"Inserisci l'esame del corso: ";
                    cin>>esame;

                    for(auto elem : esami_per_corso[esame]){
                        cout<<esame<<" : "<< elem.matricola_studente << " " << elem.cognome_studente << " " << elem.nome_studente << endl;
                    }
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
