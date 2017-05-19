//
// Created by peixot_b on 12/05/17.
//

#include "Server.h"
#include "Commande.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int	LoopCommand(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  int	i;

  i = 0;
  printf("COMMANDE : %s\n", cmd->commande);
  while (cmd_locale[i].cmdServ != 0)
    {
      if (strncasecmp(cmd_locale[i].cmdServ, cmd->commande, cmd_locale[i].len) == 0)
	{
	  cmd_locale[i].fptr(Serv, cmd_locale, cmd);
	  break ;
	}
      i++;
    }
  return (0);
}

int	LoopConnection(t_Server *Serv, Commande *cmd)
{
  bool	err;

  err = false;
  if (strncasecmp("USER", cmd->commande, 4) == 0)
    {
      my_User(Serv, cmd);
      err = true;
    }
  else if (strncasecmp("PASS", cmd->commande, 4) == 0)
      {
	if (my_Pass(Serv, cmd) == 1)
	  return (1);
	err = true;
      }
    else if (strncasecmp("QUIT", cmd->commande, 4) == 0)
	my_QuitBefore(Serv);
  if (strlen(cmd->commande) >= 1 && (!err))
    my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
  return (0);
}

void	myLoop(t_Server *Serv, Commande *cmd, Commande_Locale *cmd_locale)
{
  bool	connect;
  char	*ligne;

  connect = false;
  while (TRUE)
    {
      printf("CONNEXION PRETE....\n");
      fflush(stdout);
      Serv->lgadresseClient = sizeof(Serv->adresseClient);
      if ((Serv->socket_service = accept(Serv->socket_RV, (struct sockaddr *)&Serv->adresseClient, &Serv->s_in_size)) == -1
	  && errno == EINTR)
	continue ;
      SocketError(Serv);
      printf("Connexion Acceptee\n");
      fflush(stdout);
      if (fork() == 0)
	{
	  close(Serv->socket_RV);
	  my_Send(Serv->socket_service, SERVREADYUSER, sizeof(SERVREADYUSER));
	  while((ligne = get_next_line(Serv->socket_service)) != 0)
	    {
	      if (ligne[strlen(ligne) - 1] == '\r')
		ligne[strlen(ligne) - 1] = '\0';
	      if (strlen(ligne) >= 2)
		{
		  cmd->commande = ligne;
		  cmd->param1 = strtok(ligne, " ");
		  cmd->param1 = strtok(NULL, " ");
		}
	      if (!connect)
		{
		  if (LoopConnection(Serv, cmd) == 1)
		    connect = true;
		}
	      else
		LoopCommand(Serv, cmd_locale, cmd);
	      free(cmd->commande);
	    }
	}
      close(Serv->socket_service);
    }
}

int			main(int ac, char **av)
{
  t_Server		*Serv;
  Commande		*cmd;
  Commande_Locale	cmdLoc[] =
	  {
		  {"USER", my_UserMsg, 4},
		  {"PASS", my_PassMsg, 4},
		  {"LIST", my_Ls, 4},
		  {"HELP", my_Help, 4},
		  {"PWD", my_Pwd, 3},
		  {"NOOP", my_Noop, 4},
		  {"CWD", my_Cwd, 3},
		  {"CDUP", my_Cdup, 4},
		  {"QUIT", my_Quit, 4},
		  {"DELE", my_Dele, 4},
		  {"PASSV", my_Passv, 5},
		  {"STOR", my_Stor, 4},
		  {"PORT", my_Port, 4},
		  {"RETR", my_Retr, 4}
	};

  if (ac != 3)
    return (0);
  Serv = init();
  cmd = initCmd();
  initServ(Serv, av);
  myLoop(Serv, cmd, cmdLoc);
}