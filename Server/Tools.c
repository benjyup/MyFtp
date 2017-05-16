//
// Created by peixot_b on 12/05/17.
//

#include "Tools.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char		*enMinuscule(char *ligne)
{
  unsigned int	i;
  char		*nouvLigne;

  nouvLigne = (char*) malloc (sizeof(char)*strlen(ligne));
  for(i = 0; i < strlen(ligne); i++)
    nouvLigne[i]=tolower(ligne[i]);
  return (nouvLigne);
}

int	myIndex(int i, char *parcour)
{
  while(parcour[i] == ' ')
    i++;
  while (parcour[i] != '\0' && parcour[i] != ' ')
    i++;
  return (i);
}

Commande	*analyseCommande(char *ligne)
{
  Commande	*cmd;
  char		*parcour;
  int 		i;

  i = 0;
  fflush(stdout);
  parcour = ligne;
  cmd = (Commande*)malloc(sizeof(Commande));
  cmd->local = 0;
  i = myIndex(i, parcour);
  cmd->commande = (char*)malloc(sizeof(char) * (i));
  strncpy(cmd->commande, ligne, i);
  if (parcour[i] != '\0')
    *((cmd->commande) + i) = '\0';
  if (parcour[i] != '\0')
    {
      cmd->param1 = (char*)malloc(sizeof(char) * (strlen(ligne) - (i + 1)));
      strcpy(cmd->param1, &parcour[i + 1]);
      if (((cmd->commande)[0]) == '!')
	{
	  cmd->local = 1;
	  cmd->commande = (cmd->commande) + 1;
	}
    }
  return (cmd);
}

int	rcvControl(int sock)
{
  int	ctr;
  char	txt[MAX_ERREUR];

  if (read(sock, &ctr, sizeof(int)) == -1)
    {
      perror("Read socket control");
      exit(7);
    }
  if (read(sock , &txt, MAX_ERREUR) == -1)
    {
      perror("Read socket control");
      exit(7);
    }
  printf("-->%s\n",txt);
  fflush(stdout);
  return ctr;
}

void	sendControl(int ctr, char *txt, int sock)
{
  write(sock, &ctr, sizeof(int));
  printf("%s", txt);
  write(sock, txt, sizeof(txt));
}

void	execLocal(Commande *cmd)
{
  int	pid;

  pid = 0;
  if ((pid = fork()) == 0)
    {
      if (strcmp(cmd->commande, "LIST") == 0)
	execlp(cmd->commande, cmd->commande, NULL);
      else if (strcmp(cmd->commande, "pwd") == 0)
	  execlp(cmd->commande, cmd->commande, NULL);
	else if (strcmp(cmd->commande, "help") == 0)
	    help();
	  else if (strcmp(cmd->commande, "cd") == 0)
	      chdir(cmd->param1);
    }
  wait(&pid);
}

int	idCommande(Commande *cmd)
{
  if (cmd->commande == NULL)
    return (0);
  else if (strcmp(cmd->commande, "LIST") == 0)
      return (1);
    else if (strcmp(cmd->commande, "pwd") == 0)
	return (1);
      else if (strcmp(cmd->commande, "cd") == 0)
	  return (1);
	else if (strcmp(cmd->commande, "help") == 0)
	    return (1);
	  else
	    return (0);
}

int	execDistant(Commande *cmd, int sock)
{
  if (strcmp(cmd->commande, "LIST") == 0)
    return execDistantLs(sock);
  else if (strcmp(cmd->commande, "pwd") == 0)
      return execDistantPwd(sock);
    else if (strcmp(cmd->commande, "cd") == 0)
	return execDistantCd(sock, cmd->param1);
      else
	return (0);
}

int	execDistantCd(int sock, char *dir)
{
  int res = 0;

  if ((res = chdir(dir)) == -1)
    {
      perror("Le dossier n'existe pas.");
      exit(6);
    }
  if ((write(sock, "Commande CD executee avec succes\n", MAX_SYSTEM)) < 0)
    {
      perror("write System");
      exit(6);
    }
  return (res);
}

int			execDistantLs(int sock)
{
  DIR			*rep;
  struct dirent		*dansRep;
  char			buf[MAX_SYSTEM];


  printf("||2||");
  if ((rep = opendir(".")) == NULL)
    {
      perror("Opendir Ls");
      return (0);
    }
  strcpy(buf, "");
  if ((dansRep = readdir(rep)) == NULL)
    {
      perror("Readdir Ls");
      return (0);
    }
  printf("||2||");
  while (dansRep != NULL)
    {
      fflush(stdout);
      strcat(buf, dansRep->d_name);
      strcat(buf, "\n");
      if ((dansRep = readdir(rep)) == NULL)
	{
	  perror("Readdir Ls");
	  return (0);
	}
    }
  printf("||3||");
  printf("LS donne :%s\n", buf);
  if ((write(sock, buf, MAX_SYSTEM)) < 0)
    {
      perror("write system");
      return (0);
    }
  closedir(rep);
  return (1);
}

int	execDistantPwd(int sock)
{
  char * var;

  var = getenv("cwd");
  fflush(stdout);
  printf("PWD: %s \n", var);
  if ((write(sock, var, MAX_SYSTEM)) < 0)
    {
      perror("write system");
      return (0);
    }
  return (1);
}

void	help()
{
  fflush(stdout);
  printf("Bordel\n");
  printf("Commandes disponibles : \n");
  printf("| Local | Distant |\n");
  printf("|-----------------|\n");
  printf("| cd    | !cd     |\n");
  printf("| ls    | !ls     |\n");
  printf("| pwd   | !pwd    |\n");
  printf("|-----------------|\n");
  printf("get \n");
  printf("put \n");
  printf("quit \n");
  fflush(stdout);
}