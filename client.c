#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "nheader.h"


typedef enum {
    MESSAGE, LIST, EXIT
}Command;





int connectToHost(char *serverName, uint16_t portNum); 
void messageShell(); 
Command validateInput(char *input);
char *readLine();
void outgoingMessage(char *data);
void getClientList();
void exitServer();


int main(int argc, char *argv[]) {

    char *handle;
    float errorPercent;
    char *serverName;
    uint16_t portNum;
    int sock;

    
    if (argc != 5) {
        printf("Usage: %s handle error-percent server-name server-port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    handle = argv[1];
    if (strlen(handle) > 100) {
        printf("Handle must be less than 100 characters\n");
        exit(EXIT_FAILURE);
    }
    
    errorPercent = atof(argv[2]);
    if (errorPercent > 100 || errorPercent < 0) {
        printf("Error Percent must be between 0 and 100\n");
        exit(EXIT_FAILURE);
    }


    serverName = argv[3];
    portNum = atoi(argv[4]);

    sock = connectToHost(serverName, portNum); 

    connectToHost(serverName, portNum);

    messageShell();
    
    return 0; 
}


/*
 * Connects to host given a host name
 * and a port number. Port number should
 * be passed in machine order, the function
 * will convert to network order
 */
int connectToHost(char *serverName, uint16_t portNum) {
    int sock;
    struct sockaddr_in remote;
    struct hostent *hp;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    remote.sin_family = AF_INET;

    hp = gethostbyname(serverName);
    if (hp == NULL) {
        printf("Hostname error (%s)\n", serverName);
        exit(EXIT_FAILURE);
    }

    memcpy((char*)&remote.sin_addr, (char*)hp->h_addr, hp->h_length);

    remote.sin_port = htons(portNum);

    if (connect(sock, (struct sockaddr *)&remote, sizeof(struct sockaddr_in) < 0)) {
        perror("connection error");
        exit(EXIT_FAILURE);
    }

    return sock;
}

void messageShell() {
    char *input; 
    char token;
    uint32_t curSeqNum;
    Command command;

    while(1) {
        printf("> ");
        //select call goes here?
        input = readLine();
        command = validateInput(input);
        if (command == MESSAGE) {
            
        }
        else if (command == LIST) {
            
        }
        else if (command == EXIT) {

        }
        else {

        }
        //TODO get command type
        //TODO call correct command type
        //TODO handle incoming messages
    }

}

Command validateInput(char *input) {
    char temp;
    
    temp = input[0];
    if (temp != '%') {
        return -1;
    }

    temp = input[1];
    temp = toupper(temp);

    if (temp == 'M') {
        return MESSAGE;
    }

    if (temp == 'L') {
        return LIST;
    }

    if (temp == 'E') {
        return EXIT;
    }



    return -1;
}



char *readLine() {
    uint16_t maxLineLength = 256;
    int curPos = 0;
    uint8_t c;
    char *line = malloc(maxLineLength * sizeof(char));

    if (line == NULL) {
        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }

    c = fgetc(stdin);
    
    while (c != '\n' || c != EOF) {
        
        if (curPos == maxLineLength) {                         
            line = realloc(line, maxLineLength*=2);
            if (line == NULL) {
                printf("realloc error\n");
                exit(EXIT_FAILURE);
            }
        }
            
        line[curPos] = c;
        curPos++;
        c = fgetc(stdin);
    }

    line[curPos] = '\0';


}

void outgoingMessage(char *data) {

}

void getClientList() {

}

void exitServer() {

}
