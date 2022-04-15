#include <iostream>
#include <fstream>
#include <thread>
#include <future>

// fare la skin per partita e palla

struct Ball
{
    int x; // destra-sinistra
    int y; // alto-basso
    char skin;
    int direzione;// 9=NE, 3=SE, 1=SO, 7=NO (Direzioni del tastierino numerico)
};

struct Partita
{
    char matrix[20][50]; // Il campo di gioco
    int punteggio; // Punteggio del giocatore
    char skin;
    int x; // Posizione in orizzontale della pädellå
    Ball palla; // Palla in questione
};


void riempiMatrice(char matrice[20][50]) // Fiore
{
    // Inizializza la matrice
	for (int i=0; i<20; i++) {
		for (int j=0; j<50; j++)
			matrice[i][j] = ' ';
	}

    for (int conta=0; conta<50; conta++)
    {
        matrice[0][conta] = '#';
        matrice[19][conta] = '#';
    }
    
    for (int conta=0; conta<20; conta++)
    {
        matrice[conta][0] = '#';
        matrice[conta][49] = '#';
    }
}


void stampaMatrice(char matrice[20][50]) // Chiara
{
    system("cls"); // Si cancella lo schermo
    using namespace std; // Si deve stampare la matrice
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<50; j++)
            cout<<matrice[i][j];
        cout<<endl;
    }
}


bool controlla(Ball palla) // Chiara
{
    // Controlla se la palla è in posizione palla.x = 0
    if (palla.y == 0) // Ha toccato il bordo superiore, quindi ha perso
        return true;
    else
        return false;
}


void muoviPalla(Partita &p) // Fiore
{
    // Tiene conto della direzione della palla (p.palla.direzione) e cambia la posizione della palla di conseguenza
    
    if (p.palla.direzione == 1)
    {
    // Muovo la palla verso Sud-Ovest (cambio p.palla.x e p.palla.y)
        p.palla.x--;
        p.palla.y++;
    }
    else if (p.palla.direzione == 3) 
    {
        p.palla.x++;
        p.palla.y++;
    }
    else if (p.palla.direzione == 7) 
    {
        p.palla.x--;
        p.palla.y--;
    }
    else if (p.palla.direzione == 9) 
    {
        p.palla.x++;
        p.palla.y--;
    }

    // 9=NE, 3=SE, 1=SO, 7=NO
    if (p.palla.x == 0) // Se colpisci il muro sinistra
    {
        if(p.palla.direzione == 7)
        {
            p.palla.direzione = 9; 
        }
        else if (p.palla.direzione == 1)
        {
            p.palla.direzione = 3;
        }
    }

    if (p.palla.x == 49) // Se colpisci il muro a destra
    {
        if(p.palla.direzione == 9)
        {
            p.palla.direzione = 7; 
        }
        else if (p.palla.direzione == 3)
        {
            p.palla.direzione = 1;
        }
    }
    // 9=NE, 3=SE, 1=SO, 7=NO
    if (p.palla.y == 19) // Se colpisci il muro in basso
    {
        if(p.palla.direzione == 1)
        {
            p.palla.direzione = 7;
        }
        else if (p.palla.direzione == 3)
        {
            p.palla.direzione = 9;
        }
    }

    // Controllo se colpisce la paletta
    // 9=NE, 3=SE, 1=SO, 7=NO
    if (p.palla.y == 3)
    {
        if (p.matrix[3][p.palla.x] == p.skin) // p.skin = '_'
        {
            if (p.palla.direzione == 9) // stava andando verso Nord Est
                p.palla.direzione = 3;// Rimbalza verso Sud Est
            else if (p.palla.direzione == 7) // stava andando verso Nord  Ovest
                p.palla.direzione = 1;
        }
    }
}


void aggiornaMatrice(Partita &p) // Chiara
{
    // Cancella la vecchia pallina (cerca una 'O' dentro p.matrix)
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<50; j++)
        {
            if(p.matrix[i][j] == 'O')
                p.matrix[i][j] = ' '; // Fatto
        }
    }
    
    // Posiziona la nuova pallina ('O') sulla base delle coordinate (p.palla.x e p.palla.y)
    p.matrix[p.palla.y][p.palla.x] = 'O';

    // Stessa cosa per la paletta del giocatore, prima pulisci tutta la riga 3, e poi stampi sopra le righette
    // Consiglio: usare p.skin invece di '_' così in caso poi le cambiamo
    for (int j=0; j<50; j++) // Guardi tutta la riga 3
    {
        if (p.matrix[3][j] == p.skin) // p.skin = '_'
            p.matrix[3][j] = ' ';
    }

    p.matrix[3][p.x-1] = p.skin;
    p.matrix[3][p.x] = p.skin;
    p.matrix[3][p.x+1] = p.skin;

    for (int conta=0; conta<50; conta++)
    {
        p.matrix[0][conta] = '#';
        p.matrix[19][conta] = '#';
    }
    
    for (int conta=0; conta<20; conta++)
    {
        p.matrix[conta][0] = '#';
        p.matrix[conta][49] = '#';
    }
}


void processaMossa(Partita &p, int mossa) // Chiara
{
    // Sposta la paletta a seconda di quanto indicato dall'utente
    // 4 = sinistra, 6 = destra
    if (mossa == 4)
        p.x--;// Muovi a sinistra
    else if (mossa == 6)
        p.x++;
}


// Attende una mossa, poi ritorna il valore
int inputMossa() //spiegazione di Mattia in classe
{
    using namespace std;
    int mossa;
    if (cin >> mossa)
        return mossa;
}


int main() 
{
    Partita p;
    p.skin = '_';
    p.palla.skin = 'O';
    p.x = 10;
    p.palla.x = 15;
    p.palla.y = 10;
    p.palla.direzione = 7;

    riempiMatrice(p.matrix); // Fatta

    bool end = false;
    while (true) 
    { // Finché vero, quindi un while infinito
        using namespace std::literals; // Permette di scrivere cose tipo 0.25s oppure 1s
	    auto input = std::async(std::launch::async, inputMossa);
        while (input.wait_for(0.15s) != std::future_status::ready) 
        {
            // Controlliamo se ha perso
            if (controlla(p.palla)) // Fatta
            { // Il giocatore ha perso
                end = true;
                break;
            }
            // Muoviamo la pallina
            muoviPalla(p);
            // Aggiorniamo la matrice
            aggiornaMatrice(p);
            // Aggiorniamo l'immagine
            stampaMatrice(p.matrix); // Fatta
            p.punteggio++;
        }
        processaMossa(p, input.get());
        if (end)
            break;
    }
    aggiornaMatrice(p);
    stampaMatrice(p.matrix);
}