//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Tools.h"

void	my_Pwd(t_Server *Serv, Commande_Locale *cmd_locale)
{
  char path[BUFSIZE];

  (void)(cmd_locale);
  memset(path, '\0', BUFSIZE);
  sprintf(path, PATHCREA, Serv->pwd);
  my_Send(Serv->socket_service, path, strlen(path));
}