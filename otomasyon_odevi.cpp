#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <locale.h>

using namespace std;

struct Urun
{
    char urun_ad[80];
    char urun_kod[10];
    char kategori[80];
    char beden[10];
    char cinsiyet;    
};

void UrunEkle();
void UrunListeleme();
void UrunArama();
void UrunSil();
void UrunDuzenle();

int main(){
	setlocale(LC_ALL,"Turkish");
    
    char anamenu;
    do{
    system("cls");
    
    cout << "|-------Hoþgeldiniz------|" << endl ;
    cout << "|      Seçim Yapýnýz     |" << endl ;
    cout << "|   1- Ürün Ekleme       |" << endl ;
    cout << "|   2- Ürün Listeleme    |" << endl ;
    cout << "|   3- Ürün Arama        |"<< endl;
    cout << "|   4- Ürün Sil          |"<< endl;
    cout << "|   5- Ürün Düzenle      |"<< endl;
    cout << "|------------------------|" << endl ;
    char secim;
    cin>> secim;
    
    switch(secim) 
    {
        case '1' : 
        {
        UrunEkle();
        break;    
        }
        case '2' : 
        {
         UrunListeleme();
         break;
        }
        case '3' : 
        {
         UrunArama();
         break;
        }
        case '4' : 
        {
         UrunSil();
         break;
        }
        case '5' : 
        {
         UrunDuzenle();
         break;
        }
    }
    
    cout << "Anamenüye Dönmek için: a basýn çýkmak için: c" <<endl ; 
    anamenu=getche();
    
    }while(anamenu=='a');
     

    return 0;
}

Urun urun;

void UrunEkle()
{
    ofstream yaz("urun.dat",ios::binary |ios::app);
    char secim;
    int adet=0;
    
    do{
    cout << "Ürün Ad Giriniz:" ;
    cin>> urun.urun_ad;
    cout << "Ürün Kodu Giriniz:" ;
    cin>> urun.urun_kod;
    cout << "Kategori Giriniz:" ;
    cin>> urun.kategori;
    cout << "Beden Giriniz:" ;
    cin>> urun.beden;
    cin.ignore();
    cout << "Ürün Cinsiyeti Giriniz (E/K):" ;
    urun.cinsiyet=getche();
    cout << endl;
    yaz.write((char*)&urun, sizeof(urun));
    adet++;    
    cout << "Baþka Ürün Eklemek Ýster misin (E/H):" ;
    secim=getche();
    cout << endl;
    }while(secim=='e' || secim=='E');
    
    cout << adet << " adet Ürün Eklendi.." << endl;
    
    yaz.close();
}

void UrunListeleme()
{
    ifstream oku("urun.dat",ios::binary |ios::app);
    
    oku.seekg(0,ios::end);
    int kayits=oku.tellg()/sizeof(urun);
    cout << "Toplam Ürün Kayýt Sayýsý:"<< kayits << endl;
    
    if(kayits>0)
    {
        for(int i=0; i<kayits;i++)
        {
            oku.seekg(i*sizeof(urun));
            oku.read((char*)&urun, sizeof(urun));    
        
            cout << i+1 << ". Ürünün Bilgileri"<< endl;
            cout << "Ürün Adý: "<< urun.urun_ad <<endl;
            cout << "Ürün Kodu: "<< urun.urun_kod <<endl;
            cout << "Kategori: "<< urun.kategori <<endl;
            cout << "Beden: "<< urun.beden <<endl;
            if(urun.cinsiyet=='e' || urun.cinsiyet=='E')
            cout << "Ürün Cinsiyeti: Erkek" <<endl;
            else if(urun.cinsiyet=='k' || urun.cinsiyet=='K')
            cout << "Ürün Cinsiyeti: Kadýn" <<endl;
            
        }
    }
    else
    cout << "Kayýt Bulunamadý..." << endl;

    oku.close();
}

void UrunArama()
{
    ifstream oku("urun.dat",ios::binary |ios::app);
    
    oku.seekg(0,ios::end);
    int kayits=oku.tellg()/sizeof(urun);

    cout <<"Aranan Ürün Kodunu Giriniz"<< endl;
    char urun_kod[10];
    cin>> urun_kod;
         
    if(kayits>0)
    {
        for(int i=0; i<kayits;i++)
        {
            
            oku.seekg(i*sizeof(urun));
            oku.read((char*)&urun, sizeof(urun));
            
            if(strcmp(urun.urun_kod,urun_kod)==0)
            {
            cout <<  "Bulunan Ürünün Bilgileri"<< endl;
            cout << "Ürün Adi: "<< urun.urun_ad <<endl;
            cout << "Ürün Kodu: "<< urun.urun_kod <<endl;
            cout << "Kategori: "<< urun.kategori <<endl;
            cout << "Beden: "<< urun.beden <<endl;
            if(urun.cinsiyet=='e' || urun.cinsiyet=='E')
            cout << "Ürün Cinsiyeti: Erkek" <<endl;
            else if(urun.cinsiyet=='k' || urun.cinsiyet=='K')
            cout << "Ürün Cinsiyeti: Kadýn" <<endl;
            }
        }
    }
    else
    cout << "Kayýt Bulunamadý..." << endl;

    oku.close();
}

void UrunSil()
{
    char urun_kod[10];
    char secim= ' ';
    bool var=false;
     
    ifstream oku("urun.dat",ios::binary |ios::app);
    
    oku.seekg(0,ios::end);
    int kayitsayisi=oku.tellg()/sizeof(urun);
    
    cout<<"Kaydýný Sileceðiniz Ürün Kodunu Giriniz : ";
    cin>>urun_kod;

    for(int i=0;i<kayitsayisi;i++)
    {
        oku.seekg(i*sizeof(urun));
        oku.read((char*)&urun, sizeof(urun));
            
        if(strcmp(urun.urun_kod,urun_kod)==0)
        {
            cout<<endl;
            cout<<"Ürünun Bilgileri";
            cout<<"\nAdý : "<<urun.urun_ad;
            cout<<"\nKodu : "<<urun.urun_kod;
            cout<<"\nKategori : "<<urun.kategori;
            cout<<"\nBeden : "<<urun.beden;
            cout<<"\nCinsiyet [E/K]: ";
            if(urun.cinsiyet=='e'||urun.cinsiyet=='E')
            cout<<"Erkek";
            if(urun.cinsiyet=='k'||urun.cinsiyet=='K')
            cout<<"Kadýn";
                
            cout<<"\n\nSilmek Ýstediðiniz Kayýt Bu Mu? [E/H] : ";
            secim=getche();
            if(secim == 'H' || secim == 'h')
            {      
                Urun y_urun;
                ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
                
                strcpy(y_urun.urun_ad,urun.urun_ad);
                strcpy(y_urun.urun_kod,urun.urun_kod);
                strcpy(y_urun.kategori,urun.kategori);
                strcpy(y_urun.beden,urun.beden);
                urun.cinsiyet=y_urun.cinsiyet;
                        
                y_dosya.write((char*)&urun, sizeof(urun));
                y_dosya.close();
            }
            if(secim=='e'||secim=='E')
            {
                var=true;
            }
        }
        else
        {
            Urun y_urun;
            ofstream y_dosya("Yedek.dat",ios::app|ios::binary);
              
            strcpy(y_urun.urun_ad,urun.urun_ad);
            strcpy(y_urun.urun_kod,urun.urun_kod);
            strcpy(y_urun.kategori,urun.kategori);
            strcpy(y_urun.beden,urun.beden);
            urun.cinsiyet=y_urun.cinsiyet;
                       
            y_dosya.write((char*)&urun, sizeof(urun));
            y_dosya.close();
        }
    }
    oku.close();
    if(var)
    {
        remove("urun.dat");
        rename("Yedek.dat","urun.dat");
        cout<<"\n Kayit Silindi"<<endl;
    }
    else
    {
        remove("Yedek.dat");
        cout<<"\n Kayýt Bulunamadý"<<endl;                  
    }
}

void UrunDuzenle()
{
    char urun_kod[10];
    char secim = ' ';
    bool var = false;
    
    ifstream oku("urun.dat", ios::binary | ios::app);
    
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);
    
    cout << "Kaydýný Düzelteceðiniz Ürün Kodunu Giriniz: ";
    cin >> urun_kod;
    
    for(int i = 0; i < kayitsayisi; i++)
    {
        oku.seekg(i * sizeof(urun));
        oku.read((char*)&urun, sizeof(urun));
        
        if(strcmp(urun.urun_kod, urun_kod) == 0)
        {
            cout << endl;
            cout << "Ürünün Bilgileri" << endl;
            cout << "Adý: " << urun.urun_ad << endl;
            cout << "Kodu: " << urun.urun_kod << endl;
            cout << "Kategori: " << urun.kategori << endl;
            cout << "Beden: " << urun.beden << endl;
            cout << "Cinsiyet [E/K]: ";
            if(urun.cinsiyet == 'e' || urun.cinsiyet == 'E')
                cout << "Erkek";
            if(urun.cinsiyet == 'k' || urun.cinsiyet == 'K')
                cout << "Kadýn";
            
            cout << "\n\nDüzeltmek Ýstediðiniz Kayýt Bu Mu? [E/H]: ";
            secim = getche();
            if(secim == 'E' || secim == 'e')
            {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                cout << "\nYeni Ürün Adý Giriniz: ";
                cin >> urun.urun_ad;
                cout << "Yeni Ürün Kodu Giriniz: ";
                cin >> urun.urun_kod;
                cout << "Yeni Kategori Giriniz: ";
                cin >> urun.kategori;
                cout << "Yeni Beden Giriniz: ";
                cin >> urun.beden;
                cout << "Yeni Ürün Cinsiyeti Giriniz (E/K): ";
                urun.cinsiyet = getche();
                cout << endl;
                
                dosya.write((char*)&urun, sizeof(urun));
                dosya.close();
            }
            else
            {
                Urun y_urun;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
                
                strcpy(y_urun.urun_ad, urun.urun_ad);
                strcpy(y_urun.urun_kod, urun.urun_kod);
                strcpy(y_urun.kategori, urun.kategori);
                strcpy(y_urun.beden, urun.beden);
                urun.cinsiyet = y_urun.cinsiyet;
                
                y_dosya.write((char*)&y_urun, sizeof(y_urun));
                y_dosya.close();
            }
        }
    }
    oku.close();
    if(var)
    {
        remove("urun.dat");
        rename("Yedek.dat", "urun.dat");
        cout << "\nKayýt Düzeltildi." << endl;
    }
    else
    {
        remove("Yedek.dat");
        cout << "\nKayýt Bulunamadý." << endl;
    }
}


     

