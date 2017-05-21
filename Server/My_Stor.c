//
// Created by peixot_b on 18/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Stor(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(Serv);
  (void)(cmd_locale);
  (void)(cmd);
  if (Serv->passv == 0)
    my_Send(Serv->socket_service, USEPASV, strlen(USEPASV));
  else
    my_Send(Serv->socket_service, FILESTAT, sizeof(FILESTAT));
}