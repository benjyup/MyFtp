/*
** my_pwd.c for my_pwd in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:33:49 2017 Benjamin
** Last update Sun May 21 23:33:54 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Pwd(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  char	path[BUFSIZE];

  (void)(cmd_locale);
  (void)(cmd);
  memset(path, '\0', BUFSIZE);
  sprintf(path, PATHCREA, Serv->pwd);
  my_Send(Serv->socket_service, path, strlen(path));
}
