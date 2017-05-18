//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Noop(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  (void)(cmd);
  my_Send(Serv->socket_service, COMOK, strlen(COMOK));
}