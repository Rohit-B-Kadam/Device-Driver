#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_LENGTH 256
static char receive[BUFFER_LENGTH];

int main()
{
    int ret , fd;
    char stringToSend[BUFFER_LENGTH];

    printf("Starting device test code example...\n");
    
    
    fd = open("/dev/Marvellous Driver 1", O_RDWR);
    if(fd < 0)
    {
        perror("Failed to open the device..");
        return errno;
    }

    printf("Type a short string to the kernel Module:\n");
    scanf("%[^\n]%*c",stringToSend);
    printf("Writing message to device [%s]\n",stringToSend);

    ret = write(fd, stringToSend , strlen(stringToSend));
    if(ret < 0)
    {
        perror("Failed to write the message to the device");
        return errno;
    }

    printf("Press Enter to read back from the device\n");
    getchar();

    printf("Reading from the device...\n");
    ret = read(fd,receive, BUFFER_LENGTH);
    if(ret < 0)
    {
        perror("Failed to read the message to the device");
        return errno;
    }

    printf("The recived message is: [%s]\n",receive);
    printf("End of the program\n");

    return 0;

    return 0;
}