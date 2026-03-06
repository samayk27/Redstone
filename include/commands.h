#ifndef COMMANDS_H
#define COMMANDS_H

#include "protocol.h"
#include "store.h"
#include <string.h>
#include <strings.h> /* for strcasecmp */


void cmd_dispatch(int fd, RESPcommand *cmd);

#endif
