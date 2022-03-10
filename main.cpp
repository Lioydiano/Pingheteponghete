#include <iostream>
#include <fstream>
#include <thread>
#include <future>


struct Partita
{
    char matrix[20][50]; // Il campo di gioco
    int punteggio; // Punteggio del giocatore
    char skin;
    int x; // Posizione in orizzontale della pädellå
    Ball palla; // Palla in questione
};


struct Ball
{
    int x;
    int y;
    char skin;
    int direzione;// 9=NE, 3=SE, 1=SO, 7=NO (Direzioni del tastierino numerico)
};

void direzione (char matrix[x][y]) // Fiore
{
    if (direzione=!9 || direzione=!3 || direzione=!1 || direzione=! 1)
    if (direzione == 9)
    {
        matrix[x+1][y+1];
         if (direzione == 3)
        {
            matrix[x-1][y+1];
            if (direzione == 1)
            {
                matrix[x-1][y-1];
                if (direzione == 7)
                    ms
            }
        }
    }       
}

void riempiMatrice(char matrice[20][50]) // Fiore
{
    // Inizializza la matrice  
    for (int conta=0; conta<20; conta++){
        if (conta==0 || conta==49)
            matrice [20][conta] >> '#';
    }
    
    for (int conta=0; conta<50; conta++)
    {
        if (conta==0 || conta==19)
            matrice [conta][50] >> '#';
    }
}


void stampaMatrice(char matrice[20][50]) // Chiara
{
    // Si cancella lo schermo
    system("cls"); // In C++ si può eseguire un comando del terminal con la funzione system()
    // Si deve stampare la matrice
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<50; j++)
            std::cout<<matrix[i][j];
        std::cout<<std::endl;
    }
}


bool controlla(Ball palla) // Chiara
{
    // Controlla se la palla è in posizione palla.x = 0 o palla.x = 1
    if (palla.x==0)
        return true;
    else
        return false;
}


// Attende una mossa, poi ritorna il valore
std::string inputMossa() //spiegazione di Mattia in classe
{
    std::string mossa;
    if (cin >> mossa)
        return mossa;
}


int main() 
{
    Partita p;
    p.skin = '_';

    riempiMatrice(p.matrix);


    bool end = false;
    while (true) 
    { // Finché vero, quindi un while infinito
        using namespace std::literals; // Permette di scrivere cose tipo 0.25s oppure 1s
	    auto input = std::async(std::launch::async, inputMossa);
        while (input.wait_for(0.15s) != std::future_status::ready) 
        {
            // Controlliamo se ha perso
            if (controlla(p)) 
            { // Il giocatore ha perso
                end = true;
                break;
            }
            // Muoviamo la pallina
            muoviPalla(p);
            // Aggiorniamo la matrice
            aggiornaMatrice(p);
            // Aggiorniamo l'immagine
            stampaMatrice(p.matrix);
            p.punteggio++;
        }
        processMove(p, input.get());
        if (end)
            break;
    }
    updateMatrix(p);
    printMatrix(p.matrix);
}