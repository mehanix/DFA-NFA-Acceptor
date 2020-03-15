#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;


typedef vector<map<char,vector<int> > > GRAF;

ifstream fin("test2.in");
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
	if(matrice_vizitati[nod_curent][current_lg] == false && is_valid == 0) {

        ///Daca am ajuns intr-un nod marcat ca nod final si la ultimul caracter din cuvant=> cuvant acceptat de automat
        if( i_char_curent == i_char_final )
            if(find(stari_finale.begin(), stari_finale.end(), nod_curent) != stari_finale.end())
            {
            	is_valid=1;
            }


        /// Verifica de unde poti pleca din nodul nod_curent cu caracterul word[i_char_curent] ///
        /// itereaza prin vectorul dat de graf[nod_curent][word[i_char_curent]] si reapeleaza functia cu caracterul urmator ///
        char c = word[i_char_curent];
        /*cout<<"Din litera "<<c<<" si nodul "<<nod_curent<<" ajungi in:";
        for(int &ends : graf[nod_curent][c]) {
            cout<< ends<<' ';
        }
        cout<<'\n';
        */

            for(auto &ends : graf[nod_curent][c]) {
                if(matrice_vizitati[ends][current_lg] == false){
                   // cout<<"Plec pe "<<c<<" "<<ends<<endl;
                    matrice_vizitati[ends][current_lg] = true;
                    verify(word, ends,i_char_curent+1, i_char_final, graf,current_lg+1, stari_finale, matrice_vizitati);
                }

            }

        /// Daca trece prin tot graful si nu reuseste sa gaseasca un drum care sa accepte cuvantul, atunci e neacceptat ///
    }
}

bool is_accepting_state(int nod, vector<int>& stari_finale){
    return find(stari_finale.begin(), stari_finale.end(),nod)!=stari_finale.end();
}
/*
struct deque_gen{
    deque<pair<int,char>> q;
    int len=0;

    public:
    void add(pair<int,char> val, bool is_accepting){
    ///daca e accepting state, il pun in fata cu orice pret. altfel, doar daca mai e loc de el, si la sfarsit.
        if(is_accepting){
            if(len>=100){
                    q.pop_back();
                    len--;
                }
            q.push_front(val);
            len++;
        }
        else if(len<100){
            q.push_back(val);
            len++;
        }

    }
    void remove_front(){
        q.pop_front();
        len--;
    }
};

vector<string> results;
void generate(GRAF& graf, int nod_start, vector<int>& stari_finale, vector<vector<bool>>& matrice_vizitati, int max_length){
    string word="";
    deque_gen current_level;
    deque_gen next_level;
    current_level.add(make_pair(nod_start,'w'),is_accepting_state(nod_start,stari_finale));
    pair<int,char> current;
    do {
        cout<<"current level:";
        for(auto i:current_level.q){
            cout<<i.first<<' '<<i.second<<' ';
        } cout<<'\n';

        current = current_level.q.front();
        //cout<<current.first<<' '<<current.second;
        int current_state = current.first;
        char c = current.second;
        current_level.remove_front();
        word.push_back(c);
        //if(is_accepting_state(current.first,stari_finale))
            cout<<word<<'\n';
            //results.push_back(word);
        ///ia toate nodurile care pleaca din current_node
        for(auto mp = graf[current_state].begin(); mp!= graf[current_state].end();++mp) {
            cout<<mp->first<<":{ ";
            //pentru fiecare cheie, iterez prin elem. din vectorul lui
            for(auto node=mp->second.begin();node!=mp->second.end();++node) {
                cout<<*node<<" ";
                current_level.add(make_pair(*node,mp->first), is_accepting_state(current.first,stari_finale));
            }
            cout<<"}\n";

        }
           int b;
            cin>>b;
    } while(current_level.len!=0 || next_level.len!=0);


}*/

/*
vector<string> results;
void generate(string word, int nod_curent, GRAF& graf, int current_lg, vector<int>& stari_finale, vector<vector<bool>>& matrice_vizitati,int max_length) {
    if(results.size()<=100){

    if(matrice_vizitati[nod_curent][current_lg] == false && word.length() <= max_length) {
        //cout<<"sunt la:"<<word<<' '<<nod_curent<<'\n';
        ///ia mapul asociat nodului
        ///itereaza prin litere
        for(auto mp = graf[nod_curent].begin(); mp!= graf[nod_curent].end();++mp) {
            ///adauga litera la cuvant
            //cout<<mp->first;

            ///Daca am ajuns intr-un nod marcat ca nod final => cuvant acceptat de automat

                /// Verifica de unde poti pleca din nodul nod_curent cu orice caracter ///
                /// itereaza prin vectorul dat de graf[nod_curent][char_curent] si reapeleaza functia cu caracterul urmator ///
                char c = mp->first;
                if(current_lg<=100) {
                for(auto &ends : graf[nod_curent][c]) {
                    word.push_back(c);

                        if(matrice_vizitati[ends][current_lg] == false){
                            cout<<"Plec pe "<<c<<" "<<ends<<endl;
                            matrice_vizitati[ends][current_lg] = true;
                            if(find(stari_finale.begin(), stari_finale.end(), ends) != stari_finale.end())
                                {
                                    cout<<"GASIT "<<":"<<word<<'\n';
                                    results.push_back(word);
                                }
                            generate(word, ends,graf,current_lg+1, stari_finale, matrice_vizitati,max_length);
                            matrice_vizitati[ends][current_lg] = false;
                            word.pop_back();
                        }
                    }


        }
    }

}
}
}
*/

vector<vector<pair<int,char>>> results;
void generate(GRAF& graf,int stare_initiala,vector<int>& stari_finale, vector<vector<bool>>& matrice_vizitati,int max_length){
      queue<vector<pair<int,char>> > q;
    vector<pair<int,char>> path;
    path.push_back(make_pair(stare_initiala,' '));

    q.push(path);
    path.clear();
    while (!q.empty()) {
        path = q.front();
        q.pop();
        pair<int,char> elem_p = path.back();
        int elem = elem_p.first;
        if(is_accepting_state(elem,stari_finale))
            results.push_back(path);
        if(matrice_vizitati[elem][path.size()] == false){
            for (auto &mp: graf[elem]) {
                for(auto ends=mp.second.begin();ends!=mp.second.end();++ends) {
                    vector<pair<int,char>>new_path(path);
                    if (results.size() < 100){
                        new_path.push_back(make_pair(*ends, mp.first));
                        q.push(new_path);
                        }
                }
            matrice_vizitati[elem][path.size()] = true;
            }
            }


    }


}




bool load_from_file(GRAF &graf, int &nr_stari, int &nr_tranzitii, int &stare_initiala, int &nr_stari_finale, vector<int>& stari_finale) {
        /// citire automat ///

    if(fin.good()) {
        fin>>nr_tranzitii;
        for(int i=0;i<nr_tranzitii;i++) {
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
    }
    else
        return false;
    return true;


}

bool load_big(GRAF &graf, int &nr_stari, int &nr_tranzitii, int &stare_initiala, int &nr_stari_finale, vector<int>& stari_finale){
    try {
        ///setup
        nr_stari = 3004;
        graf.resize(nr_stari+1);
        stare_initiala = 3001;
        nr_tranzitii = 0;
        nr_stari_finale=1;
        stari_finale.resize(nr_stari_finale);
        stari_finale[0] = 3004;
        ///adaug muchii 3001 - [1..1000] 'a' (1000)
        for(int i=1;i<=1000;i++) {
            nr_tranzitii++;
            adauga_arc(graf, 3001, i, 'a');
        }
        ///adaug muchii [1...1000] -> [1001...2000] 'b' (1mil)
        for(int i=1;i<=1000;i++)
            for (int j=1001;j<=2000;j++) {
                nr_tranzitii++;
                adauga_arc(graf,i,j,'b');
            }
        ///adaug muchii [1001-2000]...[2001-3000]'c' (1mil)
        for(int i=1001;i<=2000;i++)
            for (int j=2001;j<=3000;j++) {
                nr_tranzitii++;
                adauga_arc(graf,i,j,'c');
            }
        ///adaug muchii [2001-3000] - 3002 'd' (1000)
        for(int i=2001;i<=3000;i++) {
            nr_tranzitii++;
            adauga_arc(graf, i, 3002, 'd');
        }
        nr_tranzitii++;
        adauga_arc(graf,3000,3003,'d');
        nr_tranzitii++;
        adauga_arc(graf,3003,3004,'e');
    }
    catch (...) {
        return false;
    }
    return true;



}


int main()
{
    vector<int>stari_finale;
    vector<vector<bool>> matrice_vizitati;
    int nr_stari, nr_tranzitii, stare_initiala, nr_stari_finale;
    int choice=-1;
    bool status;
    GRAF graf;
    while(choice==-1){
        cout<<"Alege o optune:\n1.Incarca graf custom din fisier\n2.Incarca graful mare din cod (cel cu 3000 noduri si 2002002 muchii)\n\nScrie numarul optiunii alese:";
        cin>>choice;
        if (choice == 1) {
            fin>>nr_stari;
            graf.resize(nr_stari+1);
            status = load_from_file(graf, nr_stari, nr_tranzitii,stare_initiala,nr_stari_finale, stari_finale);
        }
        else if (choice == 2)
            status = load_big(graf, nr_stari, nr_tranzitii,stare_initiala,nr_stari_finale, stari_finale);
        else choice = -1;
    }




    string word;
    if (status == true) {
            cout<<"\nAutomat incarcat cu succes! :)"<<endl;
            choice=-1;
            while (choice == -1){
                cout<<"\nAlege o optiune:\n1.Testeaza apartenenta cuvintelor in automat\n2.Genereaza primele 100 cuvinte acceptate de automat\n\nScrie numarul optiunii alese:";
                cin>>choice;
                if (choice == 1){

                while (true) {
                    cout<<"Introdu cuvantul de verificat:[sau EXIT pentru a iesi]"<<endl;
                    cin>>word;
                    if(word == "EXIT" || word =="exit")
                        break;
                    cout<<"Working on it...\n";

                    ///creez matrice vizitati pt cuv asta
                    ///lungimea max = lungimea cuvantului
                    matrice_vizitati.resize(nr_stari+1);
                    for(vector<bool> &v:matrice_vizitati) {
                        v.resize(word.length()+1);
                        for (auto&& x:v)
                            x=false;
                    }
                    verify(word,stare_initiala,0,word.length(),graf,0,stari_finale,matrice_vizitati);

                    if(is_valid)
                        cout<<"Cuvant acceptat de automat!\n";
                    else cout<<"Cuvant neacceptat de automat!\n";
                    is_valid=0;

                    }

                }
                else if (choice==2) {

                    /// reset matrice vizitati
                    matrice_vizitati.resize(nr_stari+1);
                    for(vector<bool> &v:matrice_vizitati) {
                        v.resize(100);
                        for (auto&& x:v)
                            x=false;
                    }
                    cout<<"Generez cuvintele acceptate...\n";

                    generate(graf,stare_initiala,stari_finale,matrice_vizitati,100);
                    int cnt = 0;
                    for(auto x = results.begin();x< results.end(); x++){
                        if(cnt<100) {
                            cout<<"("<<++cnt<<"):";
                            for(auto &i:*x)
                                cout<<i.second;
                            cout<<'\n';
                        }

                    }


                 /*   ///incerc lungimi maxime pana gasesc una care imi genereaza ~ 100 elemente
                    ///daca nu exista, afisez toate cuvintele posibile
                    for(int i=1;i<=100 && results.size()<100; i++){
                        results.clear();
                        generate("",stare_initiala,graf,0,stari_finale,matrice_vizitati,i);
                    }

                    ///afisez cuvintele, in ordine inversa
                    int cnt = 1;
                    for (auto cuvant = results.rbegin(); cuvant != results.rend() && cnt <= 100; ++cuvant  ) {
                        cout<<"("<<cnt<<"):"<<*cuvant<<'\n';
                        cnt++;
                    }*/
                }
            }



    }
    else {
        cout<<"Eroare la incarcarea/generarea automatului! :(\n";
    }

    	cout<<"Goodbye!";

}
