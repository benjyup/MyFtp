/*
** init.c for init in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:32:05 2017 Benjamin
** Last update Sun May 21 23:32:14 2017 Benjamin
*/

#include "commande.h"
#include "server.h"

struct sigaction	old_tuer;

void	killServeur()
{
  sigaction(SIGINT, &old_tuer, NULL);
  kill(0, SIGINT);
  printf("Bye !\n");
}

t_Server	*init()
{
  t_Server		*Serv;

  Serv = malloc(sizeof(*Serv));
  Serv->s_in_size = sizeof(Serv->adresseClient);
  Serv->tmp = 0;
  Serv->passv = 0;
  memset(&Serv->tuer, 0, sizeof(Serv->tuer));
  Serv->tuer.sa_handler = &killServeur;
  sigaction(SIGINT, &Serv->tuer, &old_tuer);
  return (Serv);
}

Commande	*initCmd()
{
  Commande	*cmd;

  cmd = malloc(sizeof(*cmd));
  cmd->param1 = NULL;
  cmd->commande = NULL;
  cmd->local = 0;
  return (cmd);
}

void		initServ(t_Server *Serv, char **av)
{
  if ((Serv->socket_RV = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket");
      exit(1);
    }
  Serv->pwd = av[2];
  if (chdir(Serv->pwd) == -1)
    {
      perror("Le dossier n'existe pas.");
      exit(6);
    }
  Serv->port = (unsigned short)atoi(av[1]);
  Serv->adresseRV.sin_family = AF_INET;
  Serv->adresseRV.sin_port = htons(Serv->port);
  Serv->adresseRV.sin_addr.s_addr = htonl(INADDR_ANY);
  Serv->lgadresseRV = sizeof(Serv->adresseRV);
  if ((bind(Serv->socket_RV, (const struct sockaddr *)&Serv->adresseRV, Serv->lgadresseRV)) == -1)
    {
      perror("bind");
      exit(3);
    }
  if (listen(Serv->socket_RV, 10) == -1)
    {
      perror("listen");
      exit(4);
    }
}
