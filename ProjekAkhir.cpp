#include <ncurses.h>
#include <unistd.h> 
#include <fstream>
using namespace std;

const int LEBAR = 80;
const int TINGGI = 24;




int main() {
    
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);



    endwin(); 
    return 0;
}
