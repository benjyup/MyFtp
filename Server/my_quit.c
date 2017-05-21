/*
** my_quit.c for my_quit in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:30:23 2017 Benjamin
** Last update Sun May 21 23:30:24 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Quit(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd);
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
