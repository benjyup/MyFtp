/*
** my_send.c for my_send in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:30:10 2017 Benjamin
** Last update Sun May 21 23:34:33 2017 Benjamin
*/

#include "commande.h"
#include "server.h"

void	my_Send(int s, const void *msg, size_t len)
{
  write(s, msg, len);
}
