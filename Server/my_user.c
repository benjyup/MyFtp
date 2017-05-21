/*
** my_user.c for my_user in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:29:57 2017 Benjamin
** Last update Sun May 21 23:29:58 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

int	my_User(t_Server *Serv, Commande *cmd)
{
  if (cmd->param1 == NULL)
    {
      Serv->tmp = 0;
      my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
      return (0);
    }
  if (strcasecmp(cmd->param1, "anonymous") == 0)
    {
      Serv->tmp = 1;
      my_Send(Serv->socket_service, USERNAMEOK, sizeof(USERNAMEOK));
    }
  else
    {
      Serv->tmp = 0;
      my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
    }
  return (0);
}

void	my_UserMsg(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd);
  (void)(cmd_locale);
  my_Send(Serv->socket_service, CHANGEUSER, strlen(CHANGEUSER));
}
