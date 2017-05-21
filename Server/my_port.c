/*
** my_port.c for my_port in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:30:31 2017 Benjamin
** Last update Sun May 21 23:30:36 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Port(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(Serv);
  (void)(cmd_locale);
  (void)(cmd);
  my_Send(Serv->socket_service, COMOK, sizeof(COMOK));
}
