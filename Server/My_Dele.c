//
// Created by peixot_b on 18/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Dele(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  if (remove(cmd->param1) == -1)
    {
      perror("Le fichier n'existe pas.");
      exit(6);
    }
  my_Send(Serv->socket_service, REQUFILEACT, sizeof(REQUFILEACT));
}