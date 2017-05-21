/*
** my_cwd.c for my_cwd in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:33:04 2017 Benjamin
** Last update Sun May 21 23:33:04 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Cwd(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  if (chdir(cmd->param1) == -1)
    my_Send(Serv->socket_service, ERRDIR, sizeof(ERRDIR));
  else
    my_Send(Serv->socket_service, REQUFILEACT, sizeof(REQUFILEACT));
}
