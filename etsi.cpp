#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>
using namespace std;

// Algoritmia varten mika etaisyys oli alkupisteesta edellisella kerralla.
int kayntiet[100];
int lyhinmatka;

struct Tie;
typedef vector<Tie> Tievektori;

struct Asema
{
   string nimi;
   Tievektori tiet;
   int indeksi;
};
typedef vector<Asema> Asemavektori;
Asemavektori asemavec;

//algoritmia varten paras vektori
Asemavektori paras;

struct Tie
{
   Asema *asema;
   int etaisyys;
};

Asema *hae_asema(string s);
bool onko_reitti(Asema *eka,Asema *toka,int matka,Asemavektori reitti);

int main()
{
   cout << "Reitinetsija" << endl;   
   ifstream fs;
   fs.open("ulos.txt"); 
   string rivi;
   getline(fs,rivi);
   stringstream ss(rivi);
   ss << rivi;
   int pysakemaara;
   ss >> pysakemaara;
    
   cout << "Pysakkien maara:" << pysakemaara << endl;
   for (int i=0;i < pysakemaara;i++)
   {
      getline(fs,rivi);
      Asema as;
      as.nimi = rivi;
      as.indeksi = i;
      asemavec.push_back(as);
      cout << as.nimi << endl;
   }
   int tiemaara;
   fs >> tiemaara;
   getline(fs,rivi);
   cout << "Teiden maara:" << tiemaara << endl;   
   for (int i=0;i < tiemaara;i++)
   {
      getline(fs,rivi);
      Tie tie1, tie2;
      Asema *as1 = hae_asema(rivi);
      getline(fs,rivi);
      Asema *as2 = hae_asema(rivi);
      tie1.asema = as2;
      tie2.asema = as1;
      int etaisyys;
      fs >> etaisyys;
      getline(fs,rivi);
      tie1.etaisyys = etaisyys;
      tie2.etaisyys = etaisyys;
      as1->tiet.push_back(tie1);
      as2->tiet.push_back(tie2);
   }

   string a1,a2;
   while (1)
   {
      cout << "Anna lahtoasemaksi lo jos haluat lopettaa" << endl;
      cout <<"Anna lahtoasema:";
      cin >> a1;
      // muunnetaan isoihin aakkosiin
      transform(a1.begin(), a1.end(),a1.begin(), ::toupper);
      if (a1 == "LO") 
         break;
      cout <<"Anna paateasema:";
      cin >> a2;
      transform(a2.begin(), a2.end(),a2.begin(), ::toupper);

      
      for (int i=0;i < pysakemaara;i++)
         kayntiet[i] = 10000;     
   
      lyhinmatka = 10000;
      Asemavektori reitti;  
      bool loytyi = onko_reitti(hae_asema(a1) ,hae_asema(a2),0,reitti);
      cout << "Paras reitti on:";
      Asemavektori::iterator j;
         for (j = paras.begin();j != paras.end();j++)
            cout << j->nimi << " ";
      cout << endl;
   }
}

bool onko_reitti(Asema *eka,Asema *toka,int matka,Asemavektori reitti)
{
   vector<Tie>::iterator i;
   bool loytyi = false;
   if (kayntiet[eka->indeksi] < matka)
       return false;
   kayntiet[eka->indeksi] = matka;
   reitti.push_back(*eka);
   for (i = eka->tiet.begin();i != eka->tiet.end();i++)
   {
      if(i->asema == toka)  
      {
         cout <<"loytyi linkki:"<<toka->nimi << " " <<matka+i->etaisyys << endl;
         if ((matka+i->etaisyys) >= lyhinmatka)
            continue;
         lyhinmatka = matka+i->etaisyys; 
         reitti.push_back(*(i->asema));  
         kayntiet[toka->indeksi] = matka+i->etaisyys;
         paras = reitti;
         Asemavektori::iterator j;
         for (j = reitti.begin();j != reitti.end();j++)
            cout << j->nimi << " ";
         cout << endl;
         loytyi = true;
         continue;
      }
      else
         onko_reitti(i->asema,toka,matka+i->etaisyys,reitti);
   }   
   return loytyi;
}

Asema *hae_asema(string s)
{
   vector<Asema>::iterator i;
   for (i = asemavec.begin();i != asemavec.end();i++)
   {
      //cout << i->nimi << endl;
      if (i->nimi == s)
      {
         cout << "loytyi:" << i->nimi << endl;
         return &(*i);
      }
   }
   cout << "Parsetus virhe" << endl;
   return NULL;
}
