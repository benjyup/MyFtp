/*
** my_retr.c for my_retr in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:34:05 2017 Benjamin
** Last update Sun May 21 23:34:10 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Retr(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(Serv);
  (void)(cmd_locale);
  (void)(cmd);
  if (Serv->passv == 0)
    my_Send(Serv->socket_service, USEPASV, strlen(USEPASV));
  else
    my_Send(Serv->socket_service, FILESTAT, sizeof(FILESTAT));
}
