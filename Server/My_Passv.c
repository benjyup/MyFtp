//
// Created by peixot_b on 18/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Passv(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  my_Send(Serv->socket_service, PASSV, sizeof(PASSV));
}