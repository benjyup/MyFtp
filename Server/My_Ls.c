//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Ls(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  FILE		*ls;
  char		freadbuff[BUFSIZE];

  (void)(cmd);
  (void)(cmd_locale);
  if ((ls = popen("ls -l", "r")) == NULL)
    my_Send(Serv->socket_service, LOCALERR, strlen(LOCALERR));
  else
    {
      my_Send(Serv->socket_service, FILESTAT, strlen(FILESTAT));
      while (fgets(freadbuff, BUFSIZE, ls) != NULL)
	{
	  freadbuff[strlen(freadbuff) - 1] = '\0';
	  my_Send(Serv->socket_service, freadbuff, strlen(freadbuff));
	  my_Send(Serv->socket_service, "\r\n", 2);
	}
    }
  pclose(ls);
}