#include <stdio.h> /* Standard input/output definitions */
#include <stdlib.h>
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */
int open_port(void) {
    int fd; /* File descriptor for the port */
    fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    /*
    * Could not open the port.
    */
    if (fd == -1){
        perror("open_port: Unable to open /dev/ttyACM0 - ");
    }else{
        fcntl(fd, F_SETFL, 0);
    }
    return (fd);
}

int main() {
    int fd = open_port();
    
    fcntl(fd, F_SETFL,0);
    char buff[4];
    int value = -1;
    int prev_value = -1;
    unsigned long now = (unsigned long) time(NULL);

    while (1){
        
//        read(fd, buff, sizeof(buff));
//        printf("%s", buff);
//        if (now - ((unsigned long) time(NULL)) > 100){
            read(fd, buff, sizeof(buff));
            if( buff[0] != 'A'){
                continue;
            }
            value = atoi(buff + 1);
            if (prev_value == value){
                continue;
            }
            prev_value = value;
            printf("distance %d\n", value);
            now = (unsigned long) time(NULL);
//        }
    }


    close(fd);
    return 0;
}
