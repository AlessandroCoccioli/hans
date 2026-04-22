#ifndef PARTITA_H
#define PARTITA_H

#include <iostream>
#include <vector>
#include "Carta.h"
#include "Pollaio.h"
using namespace std;

class partita{
    private:
        int turno_attutale; //tiene il conto del turno
        int punteggio_tot; //tiene conto del punteggio
        vector<Carta*> mazzo_giocatore;/*Rappresenta la mano del giocatore.
                                        * 1.vector: Un contenitore dinamico che permette di pescare 
                                        * giocare/scartare carte durante il turno.
                                        * 2. <Carta*>: Il vettore non contiene l'oggetto "fisico", ma un puntatore 
                                        * (indirizzo di memoria) alla carta creata dalla Persona A. 
                                        * Questo evita di duplicare dati pesanti e permette a tutto il gruppo 
                                        * di lavorare sullo stesso set di galline.
                                        */

        Pollaio* griglia_giocatore; //puntatori agli oggetti(fernando)
    
    public:
        Partita(Pollaio* p); //iniziallizza il primo turno

        //gestione dellla partita
        void inizia_partita(); //prende 2 carte dal mazzo
        void esegui_turno(); //gestisce pesca -> gioca -> scarta
        bool finita(); //vede se è arrivato al dodicesimo turno

        //logica dei turni
        void pesca(); //prende due carte dal mazzo
        void gioca(); //coinvolge la tui e serve per effettivamente giocare
        void scarta(); //scarta la carta

        //punteggio
        int punteggio_finale();
        int vedi_migliotre();
        int bonus_medaglie();
};

#endif
