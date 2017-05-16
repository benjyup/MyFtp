//
// Created by peixot_b on 16/05/17.
//


#include "Server.h"
#include "Tools.h"

void	my_Quit(t_Server *Serv, Commande_Locale *cmd_locale)
{
  (void)(cmd_locale);
  printf("Recu message QUIT\n");
  fflush(stdout);
  my_Send(Serv->socket_service, SERVCLOSING, sizeof(SERVCLOSING));
  exit(1);
  close(Serv->socket_service);
}
void	my_QuitBefore(t_Server *Serv)
{
  printf("Recu message QUIT\n");
  fflush(stdout);
  my_Send(Serv->socket_service, SERVCLOSING, sizeof(SERVCLOSING));
  exit(1);
  close(Serv->socket_service);
}