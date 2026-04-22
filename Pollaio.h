#ifndef POLLAIO_H
#define POLLAIO_H
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Carta.h"
using namespace std;

class Pollaio {
private:
        Carta* griglia[3][4];//matrice della griglia, volendo potrebbe anche essere 4x3
        int cartePiazzate;

public:
        // COSTRUTTORE
        Pollaio(): cartePiazzate (0) { // facendo cartePiazzate (0) INIZIALIZIAMO la variabile a 0
            for(int i=0; i<3; i++){
                for(int j=0;j<4;j++){
                        griglia[i][j] = nullptr;
                }
            }
        } // Inizializzamo tutto a nullptr
    
        bool mossaLegale(int riga, int colonna, Carta* nuovaCarta) {
                // 1. Controllo confini
                if (riga < 0 || riga >= 3 || colonna < 0 || colonna >= 4) return false; // controllo: la riga è -1? la colonna è 5? in tutti i due casi scarteremo la mossa
                
                // 2. Controllo se la cella è libera
                if (griglia[riga][colonna] != nullptr) return false; // controllo: la cella è piena? scartiamo la mossa
        
                // 3. Prima carta
                if (cartePiazzate == 0) return true; // in questo caso la facciamo inserire
        
                //REGOLE DI ADIACENZA
                bool haVicino = false; // ci permette di capire se vicino alla carte c'è ne un'altra
                int dr[] = {-1, 1, 0, 0}; // Direzioni: giù (+1), sù (-1), fermo (0), fermo (0)
                int dc[] = {0, 0, -1, 1}; //Direzioni: destra (+1), sinistra (-1), fermo (0), fermo (0)
        
                for (int i = 0; i < 4; i++) { //for che gira da 0 a 3, i valori degli array
                    int vr = riga + dr[i]; //se i = 0 allora vr = riga + (-1) quindi saliamo sopra ecc..
                    int vc = colonna + dc[i]; // se i = 2 allora vc = colonna + (-1) quindi si sposta di una colonna a sinistra
        
                    if (vr >= 0 && vr < 3 && vc >= 0 && vc < 4 && griglia[vr][vc] != nullptr) {
                        haVicino = true; 
                        Carta* vicino = griglia[vr][vc];
        
                        if (nuovaCarta->getRazza() != vicino->getRazza()) { // sostanzialmente chiede: La carta che sto posando è di razza diversa a quella che ho vicino?
                            bool diffUno = (nuovaCarta->getValore() == vicino->getValore() + 1) || 
                                           (nuovaCarta->getValore() == vicino->getValore() - 1); // condizione v/f(||): crea una regola che ci dice che la carta può essere immediatamente succ. o prec. a quella vicina
                            bool regolaUnoSei = (nuovaCarta->getValore() == 1 && vicino->getValore() == 6) ||
                                                (nuovaCarta->getValore() == 6 && vicino->getValore() == 1); // gestione caso speciale(1,6-6,1): in questo gioco se abbiamo gli estremi (1,6 oppure 6,1) è legale che si tocchino
                            
                            if (!diffUno && !regolaUnoSei) return false; //se queste condizioni non si verificano annulla la mossa
                        }
                    }
                }
                return haVicino; // se tutto è ok la mossa è legale
            }

    
        bool inserisciCarta(int riga, int colonna, Carta* nuovaCarta){
            // Chiediamo alla funzione che abbiamo appena scritto se la mossa è valida
            if (mossaLegale(riga, colonna, nuovaCarta)) {
            // Se sì, salviamo il puntatore nella griglia
                griglia[riga][colonna] = nuovaCarta;
                // Incrementiamo il contatore (fondamentale per mossaLegale)
                cartePiazzate++;
                return true; // Operazione riuscita!
            }
            // Se mossaLegale ha detto no, restituiamo false e non facciamo nulla
            return false;
        }
    
    
        Carta* getCarta(int riga, int colonna) const { // aggiungo const così la funzione promette solo di guardare dentro il pollaio e non modificare nulla
            // Un piccolo controllo di sicurezza per non crashare
            if (riga >= 0 && riga < 3 && colonna >= 0 && colonna < 4) {
                return griglia[riga][colonna];
            }
            
            // Se Andrea chiede una coordinata pazza es. griglia[5][-1], restituiamo il nulla cioè l'errore
            return nullptr;
        }
    #endif
};