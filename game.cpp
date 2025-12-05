#include <ncurses/ncurses.h>
#include <unistd.h> 
#include <string.h>
#include <fstream>
using namespace std;

// untuk usleep()

// Ukuran layar
const int LEBAR = 80;
const int TINGGI = 24;

//p = paddle (kiri)
int pKiriX = 4; // posisi kolom
int pKiriY = TINGGI / 2 - 2;   // posisi baris teratas
int pKiriTinggi = 7;   // tinggi paddle
char pKiriSimbol = '#';  

//p = paddle (kanan)
int pKananX = LEBAR - 5;
int pKananY = TINGGI / 2 - 2; 
int pKananTinggi = 7;
char pKananSimbol = '#';

//Bola
int bolaX = LEBAR / 2;
int bolaY = TINGGI / 2;
int arahBolaX = 1; // arah horizontal
int arahBolaY = -1; // arah vertikal        
char bolaSimbol = '*';

int skorKiri = 0;
int skorKanan = 0;
int riwayatSkor[10];
int skor = 0;

void simpenSkorKeFile(){
    ofstream file("RiwayatSkor.txt", ios::app);

    if (file.is_open()){
        file << "Skor Kiri: " << skorKiri << "| Skor Kanan: " << skorKanan << endl;
        file.close();
    }
}

// Menampilkan skor
void gambarSkor() {

    //Skor kiri di pojok kiri atas
    mvprintw(0, 2, "%d", skorKiri );

    //Skor kanan di pojok kanan atas
    mvprintw(0, LEBAR - 4, "%d", skorKanan);

}
void simpenSkor() {
    if(skor < 10){
        riwayatSkor[skor] = skorKiri - skorKanan;
        skor++;
    }
}

// ------------------------------------------------------------ 
// Menggambar elemen pada layar
void gambar() {
    clear();           // hapus layar
    gambarSkor();

    // Gambar bola
    mvaddch(bolaY, bolaX, bolaSimbol);

    // Gambar paddle kiri
    for (int i = 0; i < pKiriTinggi; i++)
        mvaddch(pKiriY + i, pKiriX, pKiriSimbol);

    // Gambar paddle kanan
    for (int i = 0; i < pKananTinggi; i++)
        mvaddch(pKananY + i, pKananX, pKananSimbol);

    refresh();         // tampilkan ke layar
}

// ------------------------------------------------------------
// Menggerakkan bola dan deteksi tabrakan
void gerakBola() {
    int nextX = bolaX + arahBolaX;
    int nextY = bolaY + arahBolaY;

    if (nextY <=0 || nextY >= TINGGI - 1) { //PANTUL ATAS BAWAH
        arahBolaY = -arahBolaY;  
    }

    if (nextX <= 0) {   // bola keluar kiri
        skorKanan++;
        simpenSkor();
        bolaX = LEBAR / 2;
        bolaY = TINGGI / 2;
        arahBolaY = 1;
        arahBolaY = -1;
        return;
    }
    
    if (nextX >= LEBAR - 1) { // bola keluar kanan
        skorKiri++;
        simpenSkor();
        bolaX = LEBAR / 2;
        bolaY = TINGGI / 2;
        arahBolaX = -1;
        arahBolaY = -1;
        return;
    }

    // Tabrak paddle kiri
    if (nextX == pKiriX) {
        if (nextY >= pKiriY && nextY < pKiriY + pKiriTinggi) {

            arahBolaX = -arahBolaX;
        }
    }

    // Tabrak paddle kanan
    if (nextX == pKananX) {
        if (nextY >= pKananY && nextY < pKananY + pKananTinggi) {
            arahBolaX = -arahBolaX;
        }
    }

    // Update posisi bola
    bolaX += arahBolaX;
    bolaY += arahBolaY;
}

// ------------------------------------------------------------
// Paddle kanan bergerak otomatis (AI sederhana)
void gerakPaddleKanan() {
    if (bolaY < pKananY && pKananY > 0)
        pKananY--;
    else if (bolaY > pKananY + pKananTinggi &&
             pKananY + pKananTinggi < TINGGI - 1)
        pKananY++;
}

// ------------------------------------------------------------
// Input pemain untuk paddle kiri
void inputPemain(bool &jalan) {
    int tombol = getch();  // baca input

    if (tombol == 'w' && pKiriY > 0)
        pKiriY--;

    if (tombol == 's' && pKiriY + pKiriTinggi < TINGGI - 1)
        pKiriY++;

    if (tombol == 'q'){
        simpenSkorKeFile();
        jalan = false;
    }
}

// ------------------------------------------------------------
int main() {

    // Inisialisasi ncurses
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);  // agar getch() tidak menunggu input

    bool jalan = true;

    // Loop utama game
    while (jalan) {
        inputPemain(jalan);
        gerakBola();
        gerakPaddleKanan();
        gambar();

        napms(75); // delay 75ms
    }

    endwin(); // keluar ncurses
    return 0;
}
