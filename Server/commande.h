//
// Created by peixot_b on 12/05/17.
//

#ifndef COMMANDE_H_
#define COMMANDE_H_

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

#define BUFSIZE		1024
#define MAX_COMMANDE	256
#define MAX_ERREUR	256
#define MAX_SYSTEM	1024

typedef struct	s_Commande_Local
{
  char		*cmdServ;
  void		(*fptr)();
  int		len;
}		Commande_Locale;

typedef struct	s_Commande
{
  char		*commande;
  char		*param1;
  int		local;
}		Commande;

#endif //COMMANDE_H_
