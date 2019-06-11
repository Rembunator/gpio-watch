#include <stdlib.h>
#include <stdio.h>
#include "gpio/GPIOClass.h"
#include <poll.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

int main() 
{
    printf("Hello World\n");
    
    int result;
    
    GPIOClass* gpio21 = new GPIOClass(21);
    
    gpio21->set_in();
    
    
    
    
   char str[256];
   struct timeval tv;
   struct pollfd pfd;
   int fd;
   char buf[8];

   sprintf(str, "/sys/class/gpio/gpio%d/value", 21);

   if ((fd = open(str, O_RDONLY)) < 0)
   {
      fprintf(stderr, "Failed, gpio %d not exported.\n", 21);
      exit(1);
   }

   pfd.fd = fd;

   pfd.events = POLLPRI;

   lseek(fd, 0, SEEK_SET);    /* consume any prior interrupt */
   read(fd, buf, sizeof buf);

   poll(&pfd, 1, -1);         /* wait for interrupt */

   lseek(fd, 0, SEEK_SET);    /* consume interrupt */
   read(fd, buf, sizeof buf);

    result = system("am start -a com.android.internal.intent.action.REQUEST_SHUTDOWN");
    printf("Result: %d", result);
    

   exit(0);
}
