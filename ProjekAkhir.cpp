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


int main() {
    
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);



    endwin(); 
    return 0;
}
