//
// Created by peixot_b on 15/05/17.
//

#include	<string.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"Server.h"

#define BUFF_SIZE 1000

static int	begin;

void	*xmalloc(int size)
{
  void	*p;

  p = malloc(size);
  if (p == 0)
    exit (1);
  return (p);
}

int     xread(int id_open, void *buffer, int nbytes)
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
  rest = xmalloc(size + 1);
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
  static int	nbread;
  static char	buff[BUFF_SIZE];
  char		*line;
  int		pos;

  for (line = 0, pos = 0; ; pos++)
    {
      if (begin >= nbread)
	{
	  begin = 0;
	  if (!(nbread = xread(fd, buff, BUFF_SIZE)))
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