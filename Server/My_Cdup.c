//
// Created by peixot_b on 18/05/17.
//

#include "Server.h"
#include "Commande.h"

void	my_Cdup(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  (void)(cmd);
  if (chdir(Serv->pwd) == -1)
    {
      perror("Le dossier n'existe pas.");
      exit(6);
    }
  my_Send(Serv->socket_service, COMOK, sizeof(COMOK));
}