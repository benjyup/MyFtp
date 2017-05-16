//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Tools.h"

void	my_Ls(t_Server *Serv, Commande_Locale *cmd_locale)
{
  FILE		*ls;
  char		freadbuff[BUFSIZE];

  (void)(cmd_locale);
  if ((ls = popen("ls", "r")) == NULL)
    {
      printf("Error in popen\n");
      exit(1);
    }
  my_Send(Serv->socket_service, FILESTAT, strlen(FILESTAT));
  while (fgets(freadbuff, BUFSIZE, ls) != NULL)
    {
      freadbuff[strlen(freadbuff) - 1] = '\0';
      my_Send(Serv->socket_service, freadbuff, strlen(freadbuff));
      my_Send(Serv->socket_service, "\r\n", 2);
    }
  pclose(ls);
}