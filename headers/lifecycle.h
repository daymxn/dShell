#ifndef DSHELL_LIFECYCLE_H
#define DSHELL_LIFECYCLE_H

#include "pch.h"
#include "util.h"
#include "tokenzier.h"
#include "parser.h"
#include "executor.h"

/**
 * Represents the lifecycle of the shell.\n
 *
 * Read line, parse line, execute line, repeat.
 */
_Noreturn void lifecycle(void);

#endif //DSHELL_LIFECYCLE_H
