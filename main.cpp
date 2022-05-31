#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <conio.h>
using namespace std;


// Funzione che ritorna il numero di righe presenti in punteggi.txt
int contaRighe() 
{
    // Apri per lettura
    ifstream cin; // cin è lo stream del file in direzione input
    cin.open("punteggi.txt", ios::in); // Apro il file
    if (!cin) // Se non è stato possibile aprire il file in lettura vuol dire che non esiste
        return 0; // Il file è vuoto, nessuno ha ancora giocato a Pingheteponghete

    // Conta righe
    int conta=0;
    string lettura;
    // getline legge una riga alla volta, prende come parametri l'oggetto ifstream (in questo caso cin) e la stringa nella quale mette la riga appena letta
    while (std::getline(cin, lettura)) // Finché non incontra il carattere EOF (End Of File)
        conta++;
    return conta;
}


void stampaFile() 
{
	string lettura;
    ifstream fin("punteggi.txt", ios::in);
    while (getline(fin, lettura))
    	cout << lettura <<endl;
}


void _main(string user, int punteggio) 
{
    int righe = contaRighe(); // Numero di righe nel file
    if (righe == 0) 
	{
        // Non ci sono partite salvate, quindi ci basta scrivere nel file l'utente con il suo punteggio
        ofstream file;
        file.open("punteggi.txt", ios::out);
        file << user << " " << punteggio << endl;
        file.close(); // Chiudi il file, è facoltativo perché si chiuderebbe lo stesso alla fine della funzione quando la variabile file viene distrutta
    } 
	else 
	{
    	ofstream fout;
    	fout.open("punteggi.txt", ios::app);
		fout << user << " " << punteggio << endl;
    }
}







// fare la skin per partita e palla

struct Ball
{
    int x; 
    int y; 
    char skin;
    int direzione;// 9=NE, 3=SE, 1=SO, 7=NO 
};

struct Partita
{
    char matrix[20][50]; 
    int punteggio; 
    char skin;
    int x;
    int larghezza;
    Ball palla;
};


void riempiMatrice(char matrice[20][50])
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
    // Controlla se la palla è in posizione palla.y = 0
    if (palla.y == 0) // Ha toccato il bordo superiore, quindi ha perso
        return true;
    else
        return false;
}


void muoviPalla(Partita &p) // Fiore
{
    // p è una struct con tante variabili, e a noi interessa modificare le coordinate della palla che lei contiene
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
        if (p.matrix[3][p.palla.x] == p.skin) // p.skin ovvero la skin della paletta
        {
            if (p.palla.direzione == 9) // stava andando verso Nord Est
                p.palla.direzione = 3;// Rimbalza verso Sud Est
            else if (p.palla.direzione == 7) // stava andando verso Nord  Ovest
                p.palla.direzione = 1;
            p.punteggio++;
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
                p.matrix[i][j] = ' '; 
        }
    }

    // Posiziona la nuova pallina ('O') sulla base delle coordinate (p.palla.x e p.palla.y)
    p.matrix[p.palla.y][p.palla.x] = 'O';

    // Stessa cosa per la paletta del giocatore, prima pulisco tutta la riga 3, e poi stampo sopra le righette
    // Consiglio: usare p.skin invece di '_' così in caso poi le cambiamo
    for (int j=0; j<50; j++) // Guardo tutta la riga 3
    {
        if (p.matrix[3][j] == p.skin) // p.skin = '_'
            p.matrix[3][j] = ' ';
    }

    if (p.larghezza == 1) {
        p.matrix[3][p.x] = p.skin;
    } else if (p.larghezza == 2) {
        p.matrix[3][p.x-1] = p.skin;
        p.matrix[3][p.x] = p.skin;
    } else if (p.larghezza == 3) {
        p.matrix[3][p.x-1] = p.skin;
        p.matrix[3][p.x] = p.skin;
        p.matrix[3][p.x+1] = p.skin;
        p.larghezza = 0;
    }
    p.larghezza++;

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


void processaMossa(Partita &p, int mossa)
{
    // 4 = sinistra, 6 = destra
    if (mossa == 52)
        p.x--;
    else if (mossa == 54)
        p.x++;
}


int main() 
{
    Partita p;
    p.larghezza = 3;
    p.skin = '_';
    p.palla.skin = 'O';
    p.x = 10; //posizione iniziale paletta
    //posizione iniziale palla
    p.palla.x = 15; 
    p.palla.y = 10;
    p.palla.direzione = 7;
    std::string nome;
    p.punteggio = 0;
    
    stampaFile ();
    /*
    * std:: metto questo pk non ho messo using namespace all'inizio
    */
    std::cout << "Inserisci il tuo nome: ";
    std::cin >> nome;

    riempiMatrice(p.matrix);

    bool end = false; // end quando diventa true mi fa finire il gioco
    while (true) 
    { // Finché vero, quindi un while infinito
        using namespace std::literals; // Permette di scrivere cose tipo 0.25s oppure 1s
	    auto input = std::async(std::launch::async, getch);
        while (input.wait_for(0.15s) != std::future_status::ready) 
        {
            // Controlliamo se ha perso
            if (controlla(p.palla)==true) 
            { // Il giocatore ha perso
                end = true;
                break;
            }
            muoviPalla(p);
            aggiornaMatrice(p);
            stampaMatrice(p.matrix);
        }
        
        if (end==true)
            break;
            
        processaMossa(p, input.get());
    }
    aggiornaMatrice(p);
    stampaMatrice(p.matrix);
	cout<<"il tuo punteggio e': "<<p.punteggio<<endl;
    _main(nome, p.punteggio);
}