//
// Created by peixot_b on 16/05/17.
//

#include "Tools.h"
#include "Server.h"

void		my_Send(int s, const void *msg, size_t len)
{
  write(s, msg, len);
}