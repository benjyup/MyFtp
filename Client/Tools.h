//
// Created by peixot_b on 12/05/17.
//

#ifndef FTP_TOOLS_H
#define FTP_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <signal.h>
#include <dirent.h>
#include <sys/wait.h>

#define BUFSIZE 1024 //Taille du buffer pour les transfert
#define MAX_COMMANDE 256 //Taille maximum de la commande
#define MAX_ERREUR 256 //Taille maximum des messages de control
#define MAX_SYSTEM 1024 //taille maximum des reponses commande systeme distants


typedef struct	s_Commande
{
  char		*commande;
  char		*param1;
  int		local;
}		Commande;

int		rcvControl(int sock);
char		*enMinuscule(char *ligne);
Commande	*analyseCommande(char *ligne);
void		sendControl(int ctr, char *txt, int sock);
int		idCommande(Commande *cmd);
void		execLocal(Commande *cmd);
int		execDistant(Commande * cmd, int sock);
int		execDistantPwd(int sock);
int		execDistantLs(int sock);
int		execDistantCd(int sock, char * dir);
void		help();

#endif //FTP_TOOLS_H