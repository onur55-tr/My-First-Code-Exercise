#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::cin;
using std::end;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;

class hesap_sorgu{
    private:
        char hesapnumarasi[20];
        char ilkisim[15];
        char sonisim[15];
        float toplam_bakiye;
    
    public:
        void read_data();
        void show_data();
        void write_rec();
        void read_rec();
        void search_rec();
        void edit_rec();
        void del_rec();

};
void hesap_sorgu::read_data(){
    cout << "\nHesap Numarası Giriniz: ";
    cin >> hesapnumarasi;
    cout << "İlk Adınız: ";
    cin >> ilkisim;
    cout << "Soy Adınız: ";
    cin >> sonisim;
    cout << "Bakiyeyi Giriniz: ";
    cin >> toplam_bakiye;
    //cout << endl;

}
void hesap_sorgu::show_data(){

    cout << "-----------------------------------\n";
    cout << "Hesap Numarası: " << hesapnumarasi << "\n";
    cout << "İlk Adı: " << ilkisim << "\n";
    cout << "Soy Adı: " << sonisim << "\n";
    cout << "Mevcut Bakiye: " << toplam_bakiye << "\n";
    cout << "-----------------------------------\n";

}
void hesap_sorgu::write_rec(){
    ofstream outfile;
    outfile.open("record.bank", ios::binary|ios::app);
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void hesap_sorgu::read_rec(){
    
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout << "Açılamıyor. Dosya bulunamadı!!";
        return;
    }
    cout << "\n\t\t\t\t\t\t--------------------------------Dosyadaki Veri--------------------------------\n";
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))){
            show_data();
        }
    }
    infile.close();
}
void hesap_sorgu::search_rec(){
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile){
        cout << "Açılamıyor! Dosya bulunamadı!!";
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout << "Dosyada " << count << " kayıt var.\n";
    cout << "Aramak için kayıt numarası giriniz: ";
    cin >> n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void hesap_sorgu::edit_rec(){
    int n;
    fstream infile;
    infile.open("record.bank", ios::in|ios::binary);
    if(!infile){
        cout << "Açılamadı! Dosya bulunamadı";
        return;
    }
    infile.seekg(0, ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout << "\nDosyada " << count << " kayıt var.";
    cout << "\nDüzenlenecek kayıt numarası giriniz: ";
    cin >> n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout << "\nKayıt" << n << "aşağıdaki verilere sahiptir.";
    show_data();
    infile.close();
    infile.open("record.bank", ios::out|ios::in|ios::binary);
    infile.seekp((n-1)*sizeof(*this));
    cout << "\nDeğiştirmek için veriyi girin: ";
    read_data();
    infile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void hesap_sorgu::del_rec(){
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile){
        cout << "Açılamadı! Dosya bulunamadı";
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout << "\nDosyada " << count << " kayıt var.";
    cout << "\nSilinecek kayıt numarası giriniz: ";
    cin >> n;
    fstream tmpfile;
    tmpfile.open("onur.bank",ios::out|ios::binary);
    infile.seekg(0);
    for(int i = 0; i < count; i++){
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if (i == (n-1))
            count;
        tmpfile.write(reinterpret_cast<char*>(this),sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("onur.bank", "record.bank");
}
int main(){
    hesap_sorgu a;
    int choice;
    cout << "-----------------------------------Onur Bank System-----------------------------------\n";
    while(true){
        cout << "Aşağıdaki Seçeneklerden Birini Seçiniz ";
        cout << "\n\t1-->Kayıt dosyası ekleme";
        cout << "\n\t2-->Kayıt dosyası gösterme";
        cout << "\n\t3-->Kayıt dosyası arama";
        cout << "\n\t4-->Kayıt dosyası güncelleme";
        cout << "\n\t5-->Kayıt dosyası silme";
        cout << "\n\t6-->Çıkış";
        cout << "\nSeçiminizi Giriniz: ";
        cin >> choice;
        switch(choice){
            case 1:
            system("clear");
            a.write_rec();
            break;
            
            case 2:
            system("clear");
            a.read_rec();
            break;
            
            case 3:
            system("clear");
            a.search_rec();
            break;
            
            case 4:            
            system("clear");
            a.edit_rec();
            break;

            case 5:
            system("clear");
            a.del_rec();
            break;

            case 6:
            system("clear");
            exit(0);
            break;

        }
    }
    system("pause");
    return 0;   
}