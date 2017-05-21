/*
** my_ls.c for my_ls in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:31:00 2017 Benjamin
** Last update Sun May 21 23:31:01 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Ls(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  FILE		*ls;
  char		freadbuff[BUFSIZE];

  (void)(cmd);
  (void)(cmd_locale);
  if ((ls = popen("ls -l", "r")) == NULL)
    my_Send(Serv->socket_service, LOCALERR, strlen(LOCALERR));
  else
    {
      if (Serv->passv == 0)
	{
	  my_Send(Serv->socket_service, USEPASV, strlen(USEPASV));
	  return ;
	}
      my_Send(Serv->socket_service, FILESTAT, strlen(FILESTAT));
      while (fgets(freadbuff, BUFSIZE, ls) != NULL)
	{
	  freadbuff[strlen(freadbuff) - 1] = '\0';
	  my_Send(Serv->socket_service, freadbuff, strlen(freadbuff));
	  my_Send(Serv->socket_service, "\r\n", 2);
	}
    }
  pclose(ls);
}
