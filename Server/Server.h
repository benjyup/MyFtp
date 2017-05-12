//
// Created by peixot_b on 12/05/17.
//

#ifndef FTP_SERVER_H
#define FTP_SERVER_H

#define TRUE 1

/**************************************************
  Nom de la fonction : kill_zombie(int sig)
============================================
  Description : Permet d eliminer les processus
	        qui sont en etat zombie
**************************************************/

void kill_zombie();


/*********************************************************************
  Nom de la fonction : Serveur_put(char * nomFichier)
============================================
  Description : recoit lr fichier de nom nomFichier
		en provenance du client et le stocke
		sous le meme nom dans le repertoire
		ou le serveur a ete lance
**************************************************/

void Serveur_put(char * nomFichier);

/*********************************************************************
  Nom de la fonction : Serveur_get(char * nomFichier)
============================================
  Description : expedie le fichier de nom nomFichier
		a destination du client
**************************************************/

void Serveur_get (char * nomFichier);


/*********************************************************************
  Nom de la fonction : Fermer_serveur()
============================================
  Description : Fermeture du serveur
**************************************************/

void Fermer_serveur();


/*********************************************************************
  Nom de la fonction : Quit()
============================================
  Description : deconnexion du client distant
**************************************************/

void Quit ();


#endif //FTP_SERVER_H
