//
// Created by peixot_b on 12/05/17.
//

#ifndef FTP_CLIENT_H
#define FTP_CLIENT_H

void shell();

/*
Execute un Put du cote client (lecture d'un fichier cote client).
nomFichier: Fichier a utiliser pour la commande (a lire)
*/
void put (char * nomFichier);

/*
Execute un get cote client (ecriture d'un fichier sur le client).
nomFichier: Fichier a ecrire sur le client.
*/
void get (char * nomFichier);

/*
Quitte le client en cas de signal d'interuption
et quitte la session.
*/
void quitCtrlC ();

/*
Quitte le client lorsque l'utilisateur a tape la commande
*/
void quit();


#endif //FTP_CLIENT_H
