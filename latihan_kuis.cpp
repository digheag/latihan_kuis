#include <iostream>
#include <iomanip>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <string>
using namespace std;

struct Penduduk {
    char nik[20];
    char nama[50]; 
    char alamat[100];
    char jenis_kelamin[2]; 
};


Penduduk* data;
int jumlahData = 0;

void bacaDariFile() {
    FILE* file = fopen("data_penduduk.txt", "r");
    if (!file) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    while (true) {
        Penduduk p;
        if (fscanf(file, "%s\n", p.nik) != 1) break; 
        fgets(p.nama, sizeof(p.nama), file); 
        fgets(p.alamat, sizeof(p.alamat), file);
        fgets(p.jenis_kelamin, sizeof(p.jenis_kelamin), file); 
        Penduduk* temp = new Penduduk[jumlahData + 1];
        for (int i = 0; i < jumlahData; i++) {
            temp[i] = data[i]; 
        }
        temp[jumlahData] = p; 
        delete[] data; 
        data = temp; 
        jumlahData++;
    }
    fclose(file);
}

void simpanKeFile(const Penduduk& p) {
    FILE* file = fopen("data_penduduk.txt", "a"); 
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }
    fprintf(file, "%s\n%s\n%s\n%s\n", p.nik, p.nama, p.alamat, p.jenis_kelamin);
    fclose(file);
}

void simpanSemuaKeFile() {
    FILE* file = fopen("data_penduduk.txt", "w"); 
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }
    for (int i = 0; i < jumlahData; i++) {
        fprintf(file, "%s\n%s\n%s\n%s\n", data[i].nik, data[i].nama, data[i].alamat, data[i].jenis_kelamin);
    }
    fclose(file);
}


void tampilkanData() {
    if (jumlahData == 0) {
        cout << "\nData kosong!\n";
        return;
    }

    
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if ((data[j].nik, data[j + 1].nik) > 0) {
                swap(data[j], data[j + 1]);
            }
        }
    }

    cout << "\nData Kependudukan:\n";
    cout << "-------------------------------------------------------------\n";
    cout << setw(15) << "NIK" << setw(20) << "Nama" << setw(20) << "Alamat" << setw(15) << "Jenis Kelamin" << endl;
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < jumlahData; i++) {
        cout << setw(15) << data[i].nik
             << setw(20) << data[i].nama
             << setw(20) << data[i].alamat
             << setw(15) << data[i].jenis_kelamin << endl;
    }
}


void inputData() {
    Penduduk p;
    cout << "\nMasukkan NIK: ";
    cin >> p.nik;
    cin.ignore();

    for (int i = 0; i < jumlahData; i++) {
        if ((data[i].nik, p.nik) == 0) {
            cout << "\nNIK sudah terdaftar!\n";
            return;
        }
    }

    cout << "Masukkan Nama: ";
    cin.ignore();
    cin.getline(p.nama, sizeof(p.nama)); 
    cout << "Masukkan Alamat: ";
    cin.getline(p.alamat, sizeof(p.alamat)); 
    cout << "Masukkan Jenis Kelamin (L/P): ";
    cin >> p.jenis_kelamin;

    
    Penduduk* temp = new Penduduk[jumlahData + 1];
    for (int i = 0; i < jumlahData; i++) {
        temp[i] = data[i]; 
    }
    temp[jumlahData] = p; 
    data = temp;
    jumlahData++;

    simpanKeFile(p);
    cout << "\nData berhasil ditambahkan!\n";
}

void searchData() {
    if (jumlahData == 0) {
        cout << "\nData kosong!\n";
        return;
    }

    char nik[20]; 
    cout << "\nMasukkan NIK yang dicari: ";
    cin >> nik;

    for (int i = 0; i < jumlahData; i++) {
        if ((data[i].nik, nik) == 0) {
            cout << "\nData ditemukan:\n";
            cout << "NIK: " << data[i].nik << "\n";
            cout << "Nama: " << data[i].nama << "\n";
            cout << "Alamat: " << data[i].alamat << "\n";
            cout << "Jenis Kelamin: " << data[i].jenis_kelamin << "\n";
            return;
        }
    }
    cout << "\nData dengan NIK " << nik << " tidak ditemukan.\n";
}

void editData() {
    if (jumlahData == 0) {
        cout << "\nData kosong!\n";
        return;
    }

    char nik[20]; 
    cout << "\nMasukkan NIK yang akan diedit: ";
    cin >> nik;

    for (int i = 0; i < jumlahData; i++) {
        if ((data[i].nik, nik) == 0) {
            cout << "\nMasukkan alamat baru: ";
            cin.ignore();
            fgets(data[i].alamat, sizeof(data[i].alamat), stdin);
            data[i].alamat[strlen(data[i].alamat) - 1] = '\0'; 

            cout << "\nData berhasil diperbarui!\n";
            simpanSemuaKeFile(); 
            return;
        }
    }
    cout << "\nData dengan NIK " << nik << " tidak ditemukan.\n";
}


void hapusData() {
    if (jumlahData == 0) {
        cout << "\nData kosong!\n";
        return;
    }

    char nik[20]; 
    cout << "\nMasukkan NIK yang akan dihapus: ";
    cin >> nik;
    for (int i = 0; i < jumlahData; i++) {
        if (data[i].nik == nik) {
            Penduduk* temp = new Penduduk[jumlahData - 1];
            for (int j = 0, k = 0; j < jumlahData; j++) {
                if (j != i) {
                    temp[k++] = data[j];
                }
            }
            delete[] data; 
            data = temp; 
            jumlahData--;
            cout << "\nData berhasil dihapus!\n";
            simpanSemuaKeFile();
            return;
        }
    }
    cout << "\nData dengan NIK " << nik << " tidak ditemukan.\n";
}


void menuUtama() {
    int menu;

    do {
        cout << "\n===== MENU UTAMA =====\n";
        cout << "1. Input Data\n2. Output Data\n3. Search Data\n4. Edit Data\n5. Hapus Data\n6. Exit\n";
        cout << "Pilihan: ";
        cin >> menu;

        switch (menu) {
            case 1: inputData(); break;
            case 2: tampilkanData(); break;
            case 3: searchData(); break;
            case 4: editData(); break;
            case 5: hapusData(); break;
            case 6: cout << "\nTerima kasih!\n"; return;
            default: cout << "\nPilihan tidak tersedia!\n"; break;
        }
    } while (true);
}

int main(){
    menuUtama();
    return 0;
}