//
// Created by peixot_b on 16/05/17.
//

#include "Commande.h"
#include "Server.h"

void	SocketError(t_Server *Serv)
{
  if (Serv->socket_service == -1)
    {
      perror("accept");
      exit(5);
    }
}