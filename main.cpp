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


void riempiMatrice(char matrice[20][50]) // Fiore
{
    // Inizializza la matrice  
    for (int conta=0; conta<20; conta++)
    {
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
    using namespace std;
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<50; j++)
            cout<<matrix[i][j];
        cout<<endl;
    }
}


bool controlla(Ball palla) // Chiara
{
    // Controlla se la palla è in posizione palla.x = 0
    if (palla.x == 0) // Ha toccato il bordo superiore, quindi ha perso
        return true;
    else
        return false;
}


void muoviPalla(Partita p) // Fiore
{
    // Tiene conto della direzione della palla (p.palla.direzione) e cambia la posizione della palla di conseguenza
    if (p.palla.direzione == 1) 
    {
        // Muovo la palla verso Sud-Est (quindi cambio p.palla.x e p.palla.y)
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

//se incontro il muro lo faccio girare dall'altra parte
//se arriva alla lineaprima dei bordi
//se incontra la paletta 

if (p.palla.direzione == 9)
    p.palla.direzione = 3;
else if (p.palla.direzione == 9)
    p.palla.direzione = 3;
    // Mentre lo fa tiene anche conto di se vengono toccati muri, se si è nella cella di fianco a un muro e si sta andando verso il muro si deve cambiare la direzione ---> faccio girare la palla a seconda da dove si è venuti

    if (p.palla.y == 3) { // Potrebbe esserci la paletta in corrispondenza della palla
        if (p.matrix[p.palla.x][3] == p.skin) // Se c'è la paletta allora devi cambiare direzione come se fosse un muro
        {
            // Può venire da NE o da NO
            if (p.palla.direzione == 9)
                p.palla.direzione = 3;
            // Se andava verso NE adesso andrà verso SE
            if (p.palla.direzione == 7)
                p.palla.direzione = 1;
            // Se andava verso NO adesso andrà verso SO
        }
    }
    else if (p.palla.x == 48)
        p.palla.x--; // NO! NON CAMBI LA POSIZIONE MA SOLO LA DIREZIONE!
    else if (p.palla.x == 1)
        p.palla.y--;
    else if (p.palla.y == 18)
        .palla.y++;
}



void aggiornaMatrice(Partita p) // Chiara
{
    // Cancella la vecchia pallina (cerca una 'O' dentro p.matrix)
    for (int i=0; i<20; i++)
    {
        for (int j=0; j<50; j++)
        {
            if(p.matrix[i][j] == 'O')
                p.matrix[i][j] == ' '; // Fatto ✔️
        }
    }
    
    // Posiziona la nuova pallina ('O') sulla base delle coordinate (p.palla.x e p.palla.y)
    p.matrix[p.palla.x][p.palla.y] = 'O';

    // Stessa cosa per la paletta del giocatore, prima pulisci tutta la riga 3, e poi stampi sopra le righette
    // Consiglio: usare p.skin invece di '_' così in caso poi le cambiamo
    for (int j=0; j<50; j++) // Guardi tutta la riga 3
    {
        if(p.matrix[3][j] == '_')
            p.matrix[3][j] == ' ';
    }
    p.matrix[p.x][p.y] = '_';
    
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
    p.palla.skin = 'O';

    riempiMatrice(p.matrix); // Fatta ✔️


    bool end = false;
    while (true) 
    { // Finché vero, quindi un while infinito
        using namespace std::literals; // Permette di scrivere cose tipo 0.25s oppure 1s
	    auto input = std::async(std::launch::async, inputMossa);
        while (input.wait_for(0.15s) != std::future_status::ready) 
        {
            // Controlliamo se ha perso
            if (controlla(p)) // Fatta ✔️
            { // Il giocatore ha perso
                end = true;
                break;
            }
            // Muoviamo la pallina
            muoviPalla(p);
            // Aggiorniamo la matrice
            aggiornaMatrice(p);
            // Aggiorniamo l'immagine
            stampaMatrice(p.matrix); // Fatta ✔️
            p.punteggio++;
        }
        processMove(p, input.get());
        if (end)
            break;
    }
    aggiornaMatrice(p);
    stampaMatrice(p.matrix);
}
