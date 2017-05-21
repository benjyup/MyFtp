/*
** my_passv.c for my_passv in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:33:37 2017 Benjamin
** Last update Sun May 21 23:33:38 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Passv(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(Serv);
  (void)(cmd_locale);
  (void)(cmd);
  my_Send(Serv->socket_service, PASSV, sizeof(PASSV));
  Serv->passv = 1;
}
