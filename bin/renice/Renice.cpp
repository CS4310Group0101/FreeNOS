#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<ProcessClient.h>
#include<sys/renice.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change the priority of a process");
    parser().registerFlag('n', "priority", "Set the priority of the process");
    parser().registerPositional("PRIORITY", "The new priority of the process");
    parser().registerPositional("PROCESS_ID", "The process ID of the process to change");
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    if(arguments().get("priority")) {
        const ProcessClient process;
        const int priority = atoi(arguments().get("PRIORITY"));
        ProcessID pid = atoi(arguments().get("PROCESS_ID"));

        ProcessClient::Info info;
        ProcessClient::Result result = process.processInfo(pid, info);

        // check if the process exists
        if(result == ProcessClient::NotFound) {
            ERROR("Process %d not found\n" << pid);
            return NotFound;
        }

        // check if the priority is valid
        if(priority > Process::Highest || priority < Process::Lowest) {
            ERROR("Invalid priority level: %d\n" << priority);
            return InvalidArgument;
        }

        renicepid(pid, priority, 0, 0);
        printf("Process %d priority changed to %d\n", pid, priority);
    }
}