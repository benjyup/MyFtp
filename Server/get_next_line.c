//
// Created by peixot_b on 15/05/17.
//

#include	<string.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"Server.h"
#include	"Commande.h"

static int	begin;

void	*Checkmalloc(int size)
{
  void	*p;

  p = malloc(size);
  if (p == 0)
    exit (1);
  return (p);
}

int     Checkread(int id_open, void *buffer, int nbytes)
{
  int   nb;

  nb = read(id_open, buffer, nbytes);
  if (nb == -1)
    exit (1);
  return (nb);
}

static char	*add_line(char *line, char *buff, int pos)
{
  int	size;
  char	*rest;

  size = (line ? strlen(line) : 0) + pos;
  rest = Checkmalloc(size + 1);
  if (line)
    {
      strncpy(rest, line, size - pos);
      free(line);
    }
  strncpy(rest + size - pos, buff + begin, pos);
  rest[size] = 0;
  begin += (pos + 1);
  return (rest);
}

char		*get_next_line(int fd)
{
  int		pos;
  static int	nbread;
  char		*line;
  static char	buff[BUFSIZE];

  for (line = 0, pos = 0; ; pos++)
    {
      if (begin >= nbread)
	{
	  begin = 0;
	  if (!(nbread = Checkread(fd, buff, BUFSIZE)))
	    return (line);
	  pos = 0;
	}
      if (buff[begin + pos] == '\n')
	{
	  line = add_line(line, buff, pos);
	  return (line);
	}
      if (begin + pos + 1 == nbread)
	line = add_line(line, buff, pos + 1);
    }
}