#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;


#define GRAF vector<map<char,vector<int> > >

ifstream fin("test3.in");
ofstream fout("test.out");

int is_valid=0; //TODO: scapa cumva de acest global

void adauga_arc(GRAF &graf, int q1, int q2, char c) {
    /// adauga nodului de start(q1) faptul ca litera "c" il trimite in nodul end(q2) //
    graf[q1][c].push_back(q2);
}

void afiseaza_graf(GRAF graf, int nr_stari) {
    //itereaza prin noduri
    for(int i=0;i<=nr_stari;i++) {
        // ia map-ul asociat nodului si itereaza-i prin chei
        cout<<"pentru "<<i<<"::\n";
        for(auto mp = graf[i].begin(); mp!= graf[i].end();++mp) {
            cout<<mp->first<<":{ ";
            //pentru fiecare cheie, iterez prin elem. din vectorul lui
            for(auto ends=mp->second.begin();ends!=mp->second.end();++ends) {
                cout<<*ends<<" ";
            }
            cout<<"}\n";

        }
    }
}

/**
 * Functie recursiva care traverseaza graful
 * word: cuvantul in sine
 * nod_curent: nodul la care a ajuns functia
 * i_char_curent: indicele caracterului la care a ajuns functia
 * i_char_final: indicele caracterului final
 * graF: graful automatului
 * stari_finale: vectorul de stari finale
 * */
void verify(string& word, int nod_curent, int i_char_curent, const int i_char_final, GRAF& graf, int current_lg, vector<int>& stari_finale, vector<vector<bool>>& matrice_vizitati) {
    ///daca nu s-a mai ajuns aici cu lungimea asta, mergi pe aici///
	/*cout<<"\n\n";
	for(vector<bool> &v:matrice_vizitati) {
    		v.resize(word.length()+1);
    		for (auto x:v){
    			cout<<x<<' ';
    		}
    		cout<<'\n';
    	}*/

	//cout<<"\n\n";

	if(matrice_vizitati[nod_curent][current_lg] == false && is_valid == 0) {
    	//matrice_vizitati[nod_curent][current_lg] = true;
        //cout<<"stare curenta:"<<nod_curent<<'\n';

        /*
         * Conditie de iesire!!
         * Daca am ajuns intr-un nod marcat ca nod final si la ultimul caracter din cuvant
         * => cuvant acceptat de automat
         * */
        //cout<<i_char_curent<<" "<<i_char_final<<" "<<(find(stari_finale.begin(), stari_finale.end(), nod_curent) != stari_finale.end())<<'\n';
        if( i_char_curent == i_char_final)
            if(find(stari_finale.begin(), stari_finale.end(), nod_curent) != stari_finale.end())
            {
                ///Cuvant acceptat de automat!///
            	is_valid=1;
            }




        /// Verifica de unde poti pleca din nodul nod_curent cu caracterul word[i_char_curent] ///
        /// itereaza prin vectorul dat de graf[nod_curent][word[i_char_curent]] si reapeleaza functia cu caracterul urmator ///
        char c = word[i_char_curent];
        cout<<"Din litera "<<c<<" si nodul "<<nod_curent<<" ajungi in:";
        for(int &ends : graf[nod_curent][c]) {
            cout<< ends<<' ';
        }
        cout<<'\n';

        cout<<graf[nod_curent][c].size()<<"        ";
      //  if (graf[nod_curent][c].size()>0){
            for(auto &ends : graf[nod_curent][c]) {
                //cout<<"graf[nod_curent][c] e "<<matrice_vizitati[nod_curent][current_lg];
                if(matrice_vizitati[nod_curent][current_lg] == false){
                    cout<<"Plec pe "<<c<<" "<<ends<<endl;
                    matrice_vizitati[nod_curent][current_lg] = true;
                    verify(word, ends,i_char_curent+1, i_char_final, graf,current_lg+1, stari_finale, matrice_vizitati);
                    matrice_vizitati[nod_curent][current_lg] = false;
                }

            }
      //  }


        /// Daca trece prin tot graful si nu reuseste sa gaseasca un drum care sa accepte cuvantul, atunci e neacceptat ///


        // ia pe rand fiecare caracter din cuvant
        // for(char& c : word) {
        // verifica in ce directie te poti duce cu caracterul



        // vezi daca de la nodul unde am ajuns in mod curent se poate pleca in vreo directie cu caracterul c
        /* vector<int> directions =

         for(auto ends=graf[nod_curent][c].begin(); ends!=graf[nod_curent][c].end();++ends) {
             cout<< *ends<<' ';
         }
         cout<<"\n";
         */

        //return "err";


   // }

}
}




void load_from_file(GRAF &graf, int &nr_stari, int &nr_tranzitii, int &stare_initiala, int &nr_stari_finale, vector<int>& stari_finale) {
/// citire automat ///
    //cout<<"Nr. stari:";
    fin>>nr_tranzitii;
    cout<<nr_stari<<nr_tranzitii;
    for(int i=0;i<nr_tranzitii;i++) {
        //cout<<"Introdu tranzitia "<<i<<". [format:q1 q2 ch]\n";
        int q1, q2; char c;
        fin>>q1>>q2>>c;
        adauga_arc(graf, q1,q2,c);
    }

    fin>>stare_initiala;
    fin>>nr_stari_finale;

    stari_finale.resize(nr_stari_finale);
    for(int i=0;i<nr_stari_finale;i++) {
        fin>>stari_finale[i];
    }
    cout<<"\nstari finale:";
    for(int i=0;i<nr_stari_finale;i++) {
        cout<<stari_finale[i]<<' ';
    }
    cout<<'\n';


}

void load_big(GRAF &graf, int &nr_stari, int &nr_tranzitii, int &stare_initiala, int &nr_stari_finale, vector<int>& stari_finale){
    nr_stari = 3004;
    graf.resize(nr_stari+1);
    stare_initiala = 3001;
    nr_tranzitii = 0;
    nr_stari_finale=1;
    stari_finale.resize(nr_stari_finale);
    stari_finale[0] = 3004;
    //adaug muchii 3001 - [1..1000] 'a' (1000)
    for(int i=1;i<=1000;i++) {
        nr_tranzitii++;
        adauga_arc(graf, 3001, i, 'a');
    }
    //adaug muchii [1...1000] -> [1001...2000] (1mil)
    for(int i=1;i<=1000;i++)
        for (int j=1001;j<=2000;j++) {
            nr_tranzitii++;
            adauga_arc(graf,i,j,'b');
        }
    //adaug muchii [1001-2000]...[2001-3000] (1mil)
    for(int i=1001;i<=2000;i++)
        for (int j=2001;j<=3000;j++) {
            nr_tranzitii++;
            adauga_arc(graf,i,j,'c');
        }
    //adaug muchii [2001-3000] - 3002 'd' (1000)
    for(int i=2001;i<=3000;i++) {
        nr_tranzitii++;
        adauga_arc(graf, i, 3002, 'd');
    }
    nr_tranzitii++;
    adauga_arc(graf,3000,3003,'d');
    nr_tranzitii++;
    adauga_arc(graf,3003,3004,'e');


}

int main()
{
    vector<int>stari_finale;
    vector<vector<bool>> matrice_vizitati;
    int nr_stari, nr_tranzitii, stare_initiala, nr_stari_finale;
    int choice=-1;
    GRAF graf;
    while(choice==-1){
        cout<<"Alege o optune:\n1.Incarca graf custom din fisier\n2.Incarca graful mare din cod (cel cu 3000 noduri si 2002002 muchii)\n\nScrie numarul optiunii alese:";
        cin>>choice;
        if (choice == 1) {
            fin>>nr_stari;
            graf.resize(nr_stari+1);
            load_from_file(graf, nr_stari, nr_tranzitii,stare_initiala,nr_stari_finale, stari_finale);
        }
        else if (choice == 2)
            load_big(graf, nr_stari, nr_tranzitii,stare_initiala,nr_stari_finale, stari_finale);
        else choice = -1;
    }




    string word;
    cout<<"Automat incarcat din fisier cu succes! :)"<<endl;
    cout<<nr_stari_finale<<' '<<stari_finale[0];
    while (true) {
    	cout<<"Introdu cuvantul de verificat:[sau EXIT pentru a iesi]"<<endl;
    	cin>>word;
    	if(word == "EXIT" || word =="exit")
            break;
        cout<<"Working on it...\n";

    	//creez matrice vizitati pt cuv asta
    	//lungimea max = lungimea cuvantului

    	matrice_vizitati.resize(nr_stari+1);
    	for(vector<bool> &v:matrice_vizitati) {
    		v.resize(word.length()+1);
    		for (auto&& x:v){
    			x=false;
    		}

    	}
        verify(word,stare_initiala,0,word.length(),graf,0,stari_finale,matrice_vizitati);
    	if(is_valid)
    		cout<<"Cuvant acceptat de automat!\n";
    	else cout<<"Cuvant neacceptat de automat!\n";
    	is_valid=0;

    	}
    	cout<<"Goodbye!";

}
