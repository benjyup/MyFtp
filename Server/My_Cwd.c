//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Cwd(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  if (chdir(cmd->param1) == -1)
    {
      perror("Le dossier n'existe pas.");
      exit(6);
    }
  my_Send(Serv->socket_service, REQUFILEACT, sizeof(REQUFILEACT));
}