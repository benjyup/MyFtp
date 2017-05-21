/*
** my_cdup.c for my_cdup in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:31:38 2017 Benjamin
** Last update Sun May 21 23:31:39 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Cdup(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  (void)(cmd);
  if (chdir(Serv->pwd) == -1)
    my_Send(Serv->socket_service, COMOK, sizeof(COMOK));
  else
    my_Send(Serv->socket_service, ERRDIR, sizeof(ERRDIR));
}
