#include <ncurses.h>
#include <unistd.h> 
#include <fstream>
using namespace std;

const int LEBAR = 80;
const int TINGGI = 24;

//pKiri = paddle kiri
int pKiriX = 4; 
int pKiriY = TINGGI / 2 - 2; 
int pKiriTinggi = 7;   
char pKiriSimbol = '#';

//pKanan = paddle kanan
int pKananX = LEBAR - 5;
int pKananY = TINGGI / 2 - 2;
int pKananTinggi = 7;
char pKananSimbol = '#';

int bolaX = LEBAR / 2;
int bolaY = TINGGI / 2;
int arahBolaX = 1; // arah horizontal
int arahBolaY = -1; // arah vertikal        
char bolaSimbol = '*';

int skorKiri = 0;
int skorKanan = 0;
int riwayatSkor[10];
int skor = 0;

void simpenSkorKeFile()
{
    ofstream file("RiwayatSkor.txt", ios::app);
    if (file.is_open()){
        file << "Skor Kiri: " << skorKiri << "| Skor Kanan: " << skorKanan << endl;
        file.close();
    }
}



int main() {
    
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);



    endwin(); 
    return 0;
}
