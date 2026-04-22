#include "curses.h"
#include "Carta.h"
#include "Pollaio.h"
#include "partita.h"
#include <vector>

void disegnaCarta(int startY, int startX, const char* razza, int uova, bool selezionata, int coloreID) {
    if (selezionata) attron(A_REVERSE);
    attron(COLOR_PAIR(coloreID));
    for (int i = 0; i <= 15; i++) {
        mvaddch(startY, startX + i, ACS_HLINE);
        mvaddch(startY + 6, startX + i, ACS_HLINE);
    }
    for (int i = 0; i <= 6; i++) {
        mvaddch(startY + i, startX, ACS_VLINE);
        mvaddch(startY + i, startX + 15, ACS_VLINE);
    }
    mvprintw(startY + 2, startX + 2, "R:%s", razza);
    mvprintw(startY + 4, startX + 2, "U:%d", uova);
    attroff(COLOR_PAIR(coloreID));
    if (selezionata) attroff(A_REVERSE);
}

int main() {
    initscr(); start_color(); cbreak(); noecho(); keypad(stdscr, TRUE); curs_set(0);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    Pollaio mioPollaio;
    int rigaAttuale = 0, colAttuale = 0, cartaManoAttuale = 0;
    bool inMano = false;
    Carta* cartaSelezionataPtr = nullptr;
    std::vector<Carta*> mazzo_giocatore;
    mazzo_giocatore.push_back(new Carta(1, "Padovana", 5, 2));
    mazzo_giocatore.push_back(new Carta(2, "Sebright", 3, 1));

    while (true) {
        clear();
        mvprintw(0, 0, "HENS TUI - USA LE FRECCE E INVIO");
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 4; c++) {
                bool evidenziata = (!inMano && r == rigaAttuale && c == colAttuale);
                Carta* cartaInCella = mioPollaio.getCarta(r, c);
                const char* n = (cartaInCella) ? cartaInCella->getRazza().c_str() : "Vuoto";
                int u = (cartaInCella) ? cartaInCella->getUova() : 0;
                disegnaCarta(r * 7 + 2, c * 17 + 2, n, u, evidenziata, (cartaInCella ? 2 : 1));
            }
        }
        disegnaCarta(25, 2, "Mano 1", 2, (inMano && cartaManoAttuale == 0), 3);
        disegnaCarta(25, 19, "Mano 2", 1, (inMano && cartaManoAttuale == 1), 3);
        
        int tasto = getch();
        if (tasto == 27) break;
        switch (tasto) {
            case KEY_UP: if (inMano) inMano = false; else if (rigaAttuale > 0) rigaAttuale--; break;
            case KEY_DOWN: if (!inMano) { if (rigaAttuale < 2) rigaAttuale++; else inMano = true; } break;
            case KEY_LEFT: if (inMano && cartaManoAttuale > 0) cartaManoAttuale--; else if (colAttuale > 0) colAttuale--; break;
            case KEY_RIGHT: if (inMano && cartaManoAttuale < 1) cartaManoAttuale++; else if (colAttuale < 3) colAttuale++; break;
            case 10: 
                if (inMano) cartaSelezionataPtr = mazzo_giocatore[cartaManoAttuale];
                else if (cartaSelezionataPtr) {
                    if (mioPollaio.inserisciCarta(rigaAttuale, colAttuale, cartaSelezionataPtr)) cartaSelezionataPtr = nullptr;
                }
                break;
        }
    }
    endwin(); return 0;
}