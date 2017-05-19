//
// Created by peixot_b on 12/05/17.
//

#ifndef FTP_SERVER_H
#define FTP_SERVER_H

#include "Commande.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define	TRUE		1
#define	SERVREADYMIN	"120 Service ready in nnn minutes.\r\n"
#define	DATAOPEN	"125 Data connection already open; transfer starting.\r\n"
#define	FILESTAT	"150 File status okay; about to open data connection.\r\n"
#define COMOK		"200 Command okay.\r\n"
#define	HELPMSG		"214 Help message.\r\n"
#define	SERVREADYUSER	"220 Service ready for new user.\r\n"
#define	SERVCLOSING	"221 Service closing control connection.\r\n"
#define	CLOSEDATACO	"226 Closing data connection.\r\n"
#define	PASSV		"227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n"
#define	LOGGED		"230 User logged in, proceed.\r\n"
#define	REQUFILEACT	"250 Requested file action okay, completed.\r\n"
#define	PATHCREA	"257 %s created.\r\n"
#define	USERNAMEOK	"331 User name okay, need password.\r\n"
#define	NEEDACCOUNT	"332 Need account for login.\r\n"
#define PLSLOGIN	"530 Not logged in.\r\n"
#define	ERRFC		"xxx Error (RFC compliant)\r\n"
#define ALREADYLOG	"230 Already logged in.\r\n"
#define CHANGEUSER	"530 Can't change from guest user.\r\n"
#define USERFIRST	"503 Login with USER first.\r\n"
#define	ERRDIR		"550 Failed to change directory.\r\n"
#define	FILEMISS	"450 Requested file action not taken.\r\n"
#define	LOCALERR	"451 Requested action aborted: local error in processing.\r\n"

typedef struct		s_Server
{
  char			*pwd;
  int 			socket_RV;
  int			socket_service;
  struct sockaddr_in	adresseRV;
  int			lgadresseRV;
  struct sockaddr_in	adresseClient;
  int			lgadresseClient;
  struct hostent	*hote;
  unsigned short	port;
  socklen_t		s_in_size;
  struct sigaction	tuer;
  int			tmp;
}			t_Server;

t_Server		*init();
Commande		*initCmd();
void			initServ(t_Server *Serv, char **av);
void			kill_zombie();
void			SocketError(t_Server *Serv);
void			Fermer_serveur();
char			*get_next_line(int fd);
void			my_Ls(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Help(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Pwd(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
int			my_User(t_Server *Serv, Commande *cmd);
int			my_Pass(t_Server *Serv, Commande *cmd);
void			my_Send(int s, const void *msg, size_t len);
void			my_UserMsg(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_PassMsg(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Quit(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_QuitBefore(t_Server *Serv);
void			my_Noop(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Cwd(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Cdup(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Dele(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Passv(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Port(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Stor(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);
void			my_Retr(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd);

#endif //FTP_SERVER_H