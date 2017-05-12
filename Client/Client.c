//
// Created by peixot_b on 12/05/17.
//

#include "Client.h"
#include "Tools.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int sock;
char buf[BUFSIZE];
Commande * cmd; //Commande en cours rafinnee
struct sigaction	old_tuer;

/***********/
/*SHELL FTP*/
/***********/

char *mygets(char *buf, size_t size) {
  if (buf != NULL && size > 0) {
      if (fgets(buf, size, stdin)) {
	  buf[strcspn(buf, "\n")] = '\0';
	  return buf;
	}
      *buf = '\0';  /* clear buffer at end of file */
    }
  return NULL;
}

void shell() {

  struct sigaction tuer;
  char * ligne; //Commande brute
  int n=0;
  int q=0;

  memset(&tuer, 0, sizeof(tuer));
  tuer.sa_handler = &quitCtrlC;
/* Armement du Control C pour tuer le client et quitter le serveur*/
  sigaction(SIGINT, &tuer, &old_tuer);

  printf("Lancement shell...\n");

  ligne =(char * )malloc(sizeof(char)*MAX_COMMANDE);

  while(q == 0) {

      printf("FTP>");fflush(stdout);
      if (strlen(mygets(ligne, sizeof(ligne))) >= 1)
	{
	  printf("\n");
	  fflush(stdout);

	  /*Decoupage de la commande*/

	  cmd = analyseCommande(ligne);

	  if ((idCommande(cmd)) && (cmd->local==0)) { //La commande est systeme

	      printf("\n");fflush(stdout);
	      execLocal(cmd);fflush(stdout);
	      printf("\n");fflush(stdout);

	    }else{

	      /*Envoi de la commande au serveur*/

	      if ((n  = write(sock,ligne,MAX_COMMANDE)) == -1){
		  perror("Write");
		  exit(6);
		}

	      //La commande existe elle ?
	      if(rcvControl(sock)){

		  /*Execution de la commande sur le client*/

		  if ((cmd->local) == 1){ //la commande commence par !

		      if ((read(sock,buf,MAX_SYSTEM)) < 0) {
			  perror("Read Commande Distant");
			  exit(5);
			}

		      printf("%s",buf);  //reception des resultats d'execution

		      rcvControl(sock);

		    }
		  else
		    {
		      if(strcmp(cmd->commande,"put")==0)
			put(cmd->param1);
		      else if (strcmp(cmd->commande,"get")==0)
			  get(cmd->param1);
			else if (strcmp(cmd->commande,"quit")==0)
			    {
			      quit();
			      q=1;
			    }
			  else
			    printf("Commande Inconnue au niveau client \n");
		    }
		}
	    }
	}
    }
}


/*****************/
/*PUT COTE CLIENT*/
/*****************/

void put (char * nomFichier) {

  int n = 0;
  int tailleFichier = 0;
  int tailleEnvoyee = 0;
  struct stat infos;
  int src;
  int ecrit;
  char buf[BUFSIZE];

  if (nomFichier == 0){

      printf("Manque nom de fichier");
      sendControl(0,"Manque nom de fichier",sock);


    }else{

      /*Ouverture fichier*/
      if ((src = open(nomFichier,O_RDONLY)) == -1) {

	  printf("Le fichier n existe pas\n");
	  sendControl(0,"Fichier n'existe pas",sock);

	}else{ //si le fichier existe

	  sendControl(1,"Fichier existe",sock);

	  if(rcvControl(sock)) { //si le serveur est OK

	      /*Recupere la taille du fichier*/
	      fstat(src,&infos);

	      tailleFichier = infos.st_size;

	      printf("Taille totale du fichier transmis: %d \n",tailleFichier);
	      /*Envoi de la taille du fichier*/
	      write(sock,&tailleFichier,sizeof(int));

	      while (tailleEnvoyee < tailleFichier ) {

		  /* lecture du fichier et d'ecriture dans la socket */
		  if ((n=read(src,buf,BUFSIZE)) < 0) {
		      perror("Read");
		      exit(5);
		    }

		  tailleEnvoyee += n;

		  if ((ecrit = write(sock, buf, n)) != n){
		      perror("put write");
		      exit(6);
		    }

		}
	      /* fermeture du fichier a lire */
	      close(src);
	    }
	}
    }
}

/*****************/
/*GET COTE CLIENT*/
/*****************/

void get (char * nomFichier) {

  int n = 0;
  int tailleMessage = 0;
  int dst;
  int totalRecu = 0;
//int ctrl=0;

  printf("GET COMMENCE...\n");
  fflush(stdout);

  //le fichier existe til ?
  if(rcvControl(sock)) {

      /* ouverture du fichier a ecrire */
      if ((dst = open(nomFichier, O_WRONLY | O_CREAT | O_TRUNC,0666)) == -1) {
	  printf("Probleme avec le fichier %s\n", nomFichier);
	  fflush(stdout);
	  perror("Erreur ouverture fichier: ");
	  exit(7);
	}

      /*On recupere la taille du message*/
      read(sock,&tailleMessage,sizeof(int));
      printf("Taille du message recu (theorique) : %d \n",tailleMessage);
      fflush(stdout);

      while(totalRecu < tailleMessage ){

	  /* lecture dans la socket et ecriture dans le fichier */
	  if((n=read(sock,buf,BUFSIZE)) < 0) {
	      perror("Read");
	      exit(7);
	    }

	  totalRecu += n;

	  if (write(dst,buf,n) != n){
	      perror("write");
	      exit(7);
	    }

	}

      if(tailleMessage > totalRecu){
	  printf("Message recu IMCOMPLET \n");
	  fflush(stdout);
	}
      /* fermeture du fichier a ecrire */
      close(dst);
    }
}

/*********************************/
/*QUITTER LA SESSION ET LE CLIENT*/
/*********************************/

void quitCtrlC () {
  if ((write(sock,"quit",MAX_COMMANDE)) < 0){
      perror("Write CtrlC");
      exit(6);
    }
  sigaction(SIGINT, &old_tuer, NULL);
  kill(0, SIGINT);
  quit();
}

void quit() {

  printf("Bye...\n");
  fflush(stdout);
  exit(0);

}


/******/
/*MAIN*/
/******/

int main (int argc, char * argv []) {

//int src, n, ecrit;
  struct sockaddr_in adresse_serveur;
  struct hostent *hote;
  unsigned short port;

  if (argc != 3)
    {
      printf("Usage : ./client <PORT> <HOSTNAME>");
      return (0);
    }
/* creation de la socket locale */
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
      perror("socket");
      exit(1);}

/* recuperation de l'adresse IP du serveur (a partir de son nom) */
  if ((hote = gethostbyname(argv[2])) == NULL){
      perror("gethostbyname");
      exit(2);}

/* preparation de l'adresse du serveur */
  port = (unsigned short) atoi(argv[1]);

  adresse_serveur.sin_family = AF_INET;
  adresse_serveur.sin_port = htons(port);
  bcopy(hote->h_addr, &adresse_serveur.sin_addr, hote->h_length);
  printf("L'adresse en notation pointee %s\n", inet_ntoa(adresse_serveur.sin_addr));
  fflush(stdout);

/* demande de connexion au serveur */
  if (connect(sock, (struct sockaddr *)&adresse_serveur, sizeof(adresse_serveur))==-1){
      perror("connect");
      exit(3);}

/* le serveur a accepte la connexion */
  printf("connexion acceptee\n");
  fflush(stdout);
  shell();
}
