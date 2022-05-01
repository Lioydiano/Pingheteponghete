#include <fstream>
using namespace std;

void _main(string user, int punteggio) {
    int righe = contaRighe(); // Numero di righe nel file
    if (righe == 0) {
        // Non ci sono partite salvate, quindi ci basta scrivere nel file l'utente con il suo punteggio
        // Il nome utente è user, il punteggio è punteggio
        ofstream file;
        file.open("punteggi.txt", ios::out);
        file << user << " " << punteggio << endl;
        file.close(); // Chiudi il file, è facoltativo perché si chiuderebbe lo stesso alla fine della funzione quando la variabile file viene distrutta
    } else {
        // "Se l'utente user non esiste"
        if (esisteUtente(user, righe) == 0) // ! significa "NOT"
            righe++; // Se l'utente non esiste, allora aggiungi una riga agli array
        string nomi[righe]; // Array che conterrà i nomi
        int dati[righe]; // Array che conterrà i punteggi
        /*
        * nomi[0] = "Chiara"; dati[0] = 100;
        * nomi[1] = "Fiore"; dati[1] = 200;
        * nomi[2] = "Giulia"; dati[2] = 300;
        */
        // Leggi il file e inseriscilo negli array
        leggiFile(nomi, dati, righe); // Riempie gli array nomi e dati
        inserisciUtente(nomi, dati, user, punteggio, righe);
        stampaFile(nomi, dati, righe);
    }
}


// Funzione che ritorna il numero di righe presenti in punteggi.txt
int contaRighe() {
    // Apri per lettura
    ifstream cin; // cin è lo stream del file in direzione input
    cin.open("punteggi.txt", ios::in); // Apro il file
    if (!cin) // Se non è stato possibile aprire il file in lettura vuol dire che non esiste
        return 0; // Il file è vuoto, nessuno ha ancora giocato a Pingheteponghete

    // Conta righe
    int conta=0;
    // getline legge una riga alla volta, prende come parametri l'oggetto ifstream (in questo caso cin) e la stringa nella quale mette la riga appena letta
    while (getline(cin, " ")) // Finché non incontra il carattere EOF (End Of File)
        conta++;
    return conta;
}


// Funzione che dice se l'utente esiste già nel file punteggi.txt
bool esisteUtente(string username, int n) 
{
    ifstream file;// Apri punteggi.txt in lettura
    file.open("punteggi.txt", ios::in);
    string parola;
    // Scorri per tutto il file e cerchi se trovi username, se lo trovi
	for (int i=0; i<n*2-1; i++) //ripeti n*2 volte cerca per n*2 volte l'username
	{
        cin>>parola;
        if (parola==username)
        	return true;
    }
    return false;
    // Se alla fine non l'hai trovato ritorni false
}


// Funzione che legge il file punteggi.txt e ritorna i dati in un array
void leggiFile(string nomi[], int dati[], int n) {
    ifstream cin; // cin è lo stream del file in direzione input
    cin.open("punteggi.txt", ios::in); // Apro il file

    // Leggi riga per riga
    for (int i=0; i<n; i++) {
        cin >> nomi[i]; // Prende la prima stringa (il nome)
        cin >> dati[i]; // Prende la seconda stringa (il punteggio) sottoforma di int
    }
}


// Funzione che inserisce i dati dell'utente nelle punteggi
void inserisciUtente(string nomi[], int dati[], string username, int punteggio, int n) {
    if (esisteUtente(username, n) == false) 
	{ // Se l'utente non esiste
        // Aggiungi l'utente all'array
        nomi[n] = username;
        // Aggiungi il punteggio all'array
        dati[n] = punteggio;
    } 
	else 
	{ // Se l'utente esiste
        // Aggiorna il punteggio dell'utente
        for (int i=0; i<n; i++) 
		{ // i è una variabile che scorre finché non trova l'utente
            if (nomi[i] == username) 
			{ // "Se ho trovato l'utente in posizione i"
                if (dati[i] < punteggio) // "Se il punteggio dell'utente in posizione i è minore del punteggio dell'utente che si sta salvando"
                    dati[i] = punteggio; // Aggiorna il punteggio dell'utente
                break; // Fa finire il ciclo for
            }
        }
    }
}


// Funzione che rimette i dati dell'utente nelle punteggi.txt
void stampaFile(string nomi[], int dati[], int n) 
{
    // Apri per scrittura
    ofstream cout("punteggi.txt", ios::out);
    for (int i=0; i<n; i++)
    {
    	cout<< nomi[i] << " " << dati[i];
	}
}
