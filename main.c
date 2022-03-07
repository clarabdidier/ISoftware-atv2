#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define QTD_MESSAGES 2

int main() {
    int pipeFileDescriptors[2];
    int returnStatus;
    char writeMessages[QTD_MESSAGES][20] = {"Maria", "Joao andou a noite"};
    char readMessages[20];
    memset(readMessages, '\0', sizeof(char) * 20);

    returnStatus = pipe(pipeFileDescriptors);

    if (returnStatus == -1) {
        printf("Error when create pipe\n");
        return 1;
    }

    int pid = fork();

     
    if (pid > 0) { 
        for (int i = 0; i < QTD_MESSAGES; i++) {
            printf("Writing Message %d is %s\n", i, writeMessages[i]);
            write(pipeFileDescriptors[1], writeMessages[i], sizeof(char) * 20);
        }
    }

    else if (pid == 0){
        for (int i = 0; i < QTD_MESSAGES; i++) {
            read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
            printf("Reading Message %d is %s\n", i, readMessages);
        }
    } else {
        printf("Error creating child process");
    }

    return 0;
}
