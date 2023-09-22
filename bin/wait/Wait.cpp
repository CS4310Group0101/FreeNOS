#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Wait.h"

Wait::Wait(int argc, char** argv)
: POSIXApplication(argc, argv)
{
    parser().setDescription("Wait for a process to finish.");
    parser().registerPositional("PROCESS_ID", "Wait until this process finishes.");
}

Wait::~Wait() {}

Wait::Result Wait::exec()
{
    const ProcessClient process;
    ProcessID pid = atoi(argumentt().get("PROCESS_ID"));
}

