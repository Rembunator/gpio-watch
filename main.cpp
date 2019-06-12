#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "gpio/GPIOClass.h"
#include <poll.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <libgen.h>
#include <iostream>
#include <limits.h>
//ToDo: cleanup includes

using namespace std;

const int MAX_PATH = 1024;

int poll_files(pollfd * poll_list, int polllListSize);

struct gpioInit 
{
    int port;
    string command;
    int gpioValueFd;
    GPIOClass* gpio;
};
unordered_map<int, gpioInit> gpioInitMap;

void exitHandler(int s)
{
    printf("Caught signal %d\n",s);

    GPIOClass *gpio;

    for ( auto it : gpioInitMap )
    {
        gpio = it.second.gpio;
        delete gpio;
    }
    exit(1); 
}

string getExeDir()
{
    // Find current executable path
    char res[ MAX_PATH ];
    ssize_t count = readlink( "/proc/self/exe", res, MAX_PATH );
    const char *path;

    if (count != -1) {
        path = dirname(res);
    }
    return path;
}

int main() 
{
    // Catch user interrupts
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = exitHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);

    int fdConfig;
    char configFile[19] = "gpio_inputs.config";
    ifstream infile( getExeDir() + "/" + configFile);

    if ( !infile )
    {
        printf( "The config file '%s' could not be opened.", configFile );
        exit(1);
    }

    string line;
    string delimiter = "=";

    while (getline(infile, line))
    {

        size_t pos = 0;
        string strGpioNr, strCommand;
        if ((pos = line.find(delimiter)) != std::string::npos) 
        {
            gpioInit newGpioInit;

            newGpioInit.port        = stoi( line.substr( 0, pos ) );
            newGpioInit.command     = line.substr( pos+1 );

            GPIOClass* gpio = new GPIOClass( newGpioInit.port );
            gpio->set_in();

            newGpioInit.gpio        = gpio;
            newGpioInit.gpioValueFd = gpio->getValueFd();

            gpioInitMap[ newGpioInit.gpioValueFd ] = newGpioInit;
        }
    }

    int polllListSize = gpioInitMap.size();
    struct pollfd pollList[ polllListSize ];

    // Create a pollfd array to pass to the poll_files function    
    int index = 0;
    //int gpioValueFd;
    char buf[8];
    for (auto it : gpioInitMap)
    {
        lseek(it.first, 0, SEEK_SET);    /* consume any prior interrupt */
        read(it.first, buf, sizeof buf);

        pollList[ index ].fd = it.first;
        pollList[ index ].events = POLLPRI;
        index++;
    }

    int result;
    while (1)
    {
        int polledFiles = poll_files( pollList, polllListSize );
        printf( "RetVal: %d\n", polledFiles );

        for(auto &&item: pollList)
        {
            if ((item.revents&POLLPRI) == POLLPRI)
            {
                lseek(item.fd, 0, SEEK_SET);    /* consume interrupt */
                read(item.fd, buf, sizeof buf);

                printf( "Success on item: %d\n", gpioInitMap[ item.fd ].port );
                printf( "Perform action: %s\n", gpioInitMap[ item.fd ].command.c_str() );
                result = system( gpioInitMap[ item.fd ].command.c_str() );
                printf( "Result: %d", result );
            }
            else
            {
                printf( "Nothing yet on item: %d\n", gpioInitMap[ item.fd ].port );
            }
        }
        printf( "\n" );
    }

    exit(0);
}


int poll_files(pollfd * poll_list, int pollListSize)
{
    int retval;
    // int pollListSize = sizeof( poll_list );

    printf("Pol list size: %d ", pollListSize);

    retval = poll(poll_list, pollListSize, 10000);
    /* Retval will always be greater than 0 or -1 in this case.
    Since we're doing it while blocking */

    if(retval < 0)
    {
        perror("Error while polling\n");
        return -1;
    }

    return retval;
}
