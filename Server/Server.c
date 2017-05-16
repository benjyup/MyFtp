//
// Created by peixot_b on 12/05/17.
//

#include "Server.h"
#include "Tools.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void	Serveur_put(char *nomFichier, t_Server *Serv)
{
  int	n;
  int	tailleMessage;
  int	fic;
  int	totalRecu;
  char	buf[BUFSIZE];

  n = 0;
  tailleMessage = 0;
  totalRecu = 0;
  printf("Lancement de put\n");
  fflush(stdout);
  if (rcvControl(Serv->socket_service))
    {
      if ((fic = open(nomFichier, O_WRONLY | O_CREAT | O_TRUNC,0666)) == -1) {
	  fflush(stdout);
	  perror("Erreur dans l ouverture du fichier: ");
	  sendControl(0, "Probleme avec le fichier", Serv->socket_service);
	}
      else
	{
	  sendControl(1, "Fichier cree et ouvert", Serv->socket_service);
	  read(Serv->socket_service, &tailleMessage, sizeof(int));
	  printf("Taille du message recu (theorique) : %d \n", tailleMessage);
	  fflush(stdout);
	  while(totalRecu < tailleMessage)
	    {
	      if ((n = read(Serv->socket_service, buf, BUFSIZE)) < 0)
		{
		  perror("Read");
		  exit(7);
		}
	      totalRecu += n;
	      if (write(fic, buf, n) != n)
		{
		  perror("write");
		  exit(7);
		}
	    }
	  if (tailleMessage > totalRecu)
	    {
	      printf("Message recu IMCOMPLET \n");
	      fflush(stdout);
	    }
	  close(fic);
	}
    }
}

void		get(char *nomFichier, t_Server *Serv)
{
  int		n;
  int		tailleFichier;
  int		tailleEnvoyee;
  struct stat	infos;
  int		src;
  int		ecrit;
  char		buf[BUFSIZE];

  n = 0;
  tailleEnvoyee = 0;
  tailleFichier = 0;
  printf("GET COMMENCE...\n");
  fflush(stdout);
  if (nomFichier == 0)
    {
      sendControl(0, "Il manque le nom du fichier", Serv->socket_service);
      printf("Manque nom de fichier");
    }
  else
    {
      if ((src = open(nomFichier, O_RDONLY)) == -1)
	{
	  sendControl(0, "Le fichier nexiste pas", Serv->socket_service);
	  printf("Le fichier n existe pas\n");
	}
      else
	{
	  fstat(src, &infos);
	  tailleFichier = infos.st_size;
	  sendControl(1, "Debut transfert ...", Serv->socket_service);
	  printf("Taille totale du fichier transmis: %d \n", tailleFichier);
	  write(Serv->socket_service, &tailleFichier, sizeof(int));
	  while (tailleEnvoyee < tailleFichier )
	    {
	      if ((n = read(src, buf, BUFSIZE)) < 0)
		{
		  perror("Read");
		  exit(5);
		}
	      tailleEnvoyee += n;
	      printf("Taille du lot transmis: %d \n", n);
	      if ((ecrit = write(Serv->socket_service, buf, n)) != n)
		{
		  perror("write");
		  exit(6);
		}
	    }
	  close(src);
	}
    }
}

int	LoopCommand(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  int	i;

  i = 0;
  while (cmd_locale[i].cmdServ)
    {
      if (strcmp(cmd_locale[i].cmdServ, cmd->commande) == 0)
	{
	  cmd_locale[i].fptr(Serv, cmd_locale);
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
  if (strcmp("USER", cmd->commande) == 0)
    {
      my_User(Serv, cmd);
      err = true;
    }
  else if (strcmp("PASS", cmd->commande) == 0)
      {
	if (my_Pass(Serv, cmd) == 1)
	  return (1);
	err = true;
      }
    else if (strcmp("QUIT", cmd->commande) == 0)
	my_QuitBefore(Serv);
  if (!err)
    my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
  return (0);
}

void	myLoop(t_Server *Serv, char *ligne, Commande *cmd, Commande_Locale *cmd_locale)
{
  bool	connect;

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
	  while((ligne = get_next_line(Serv->socket_service)) != 0)
	    {
	      if (ligne[strlen(ligne) - 1] == '\r')
		ligne[strlen(ligne) - 1] = '\0';
	      cmd = analyseCommande(ligne);
	      if (!connect)
		{
		  if (LoopConnection(Serv, cmd) == 1)
		    connect = true;
		}
	      else
		LoopCommand(Serv, cmd_locale, cmd);
	    }
	}
      close(Serv->socket_service);
    }
}

int			main(int ac, char **av)
{
  t_Server		*Serv;
  char			ligne[MAX_COMMANDE];
  Commande		*cmd;
  Commande_Locale	cmdLoc[] =
	  {
		  {"USER", my_UserMsg},
		  {"PASS", my_PassMsg},
		  //{"SYST", fct_syst},
		  //{"FEAT", fct_feat},
		  //{"PWD", fct_pwd},
		  //{"EPSV", fct_epsv},
		  //{"PASV", fct_pasv},
		  {"LIST", my_Ls},
		  {"HELP", my_Help},
		  {"PWD", my_Pwd},
		  //{"RETR", fct_retr},
		  //{"STOR", fct_stor},
		  //{"TYPE", fct_type},
		  {"QUIT", my_Quit},
		  {0, 0}
	  };

  if (ac != 3)
    return (0);
  Serv = init();
  cmd = malloc(sizeof(*cmd));
  cmd->param1 = NULL;
  initServ(Serv, av);
  myLoop(Serv, ligne, cmd, cmdLoc);
/* armement du handler pour eliminer les fils morts */
  //kill_zombie(action.sa_handler);
  //sigaction(SIGCHLD,&action, NULL);
}