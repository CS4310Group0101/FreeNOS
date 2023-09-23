#include <stdio.h>
#include <sys/wait.h>
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
    ProcessClient::Info info;

    //Get command line argument 1
    ProcessID pid = atoi(arguments().get("PROCESS_ID"));
    const ProcessClient::Result result = process.processInfo(pid, info);

    // If pid is found, wait until process finishes
    if(result == ProcessClient::Success)
    {
        printf("Waiting for process %d to finish.\n", pid);
        waitpid(pid, 0, 0);
        printf("Process %d finished.\n", pid);
    }
    //Error handling for negative pid
    else if (pid <= 0)
    {
        ERROR("invalid pid '" << arguments().get("PROCESS_ID") << "'");
        return InvalidArgument;
    }
    else
    {
        printf("Process %d not found.\n", pid);
    }

    return Success;
}

