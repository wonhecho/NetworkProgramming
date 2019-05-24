#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n, input=0;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char message[1000] , server_reply[2000];
    

    char buffer[256];
    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");
//    write(sockfd,"HelloC",6);


        while(1)
	{
    	printf("Main Menu: \n");
    	printf("1. Input a message(rock/paper/scissors)\n");
    	printf("2. Exit\n");
    	printf("Select option: ");
    	
    	scanf("%d",&input);
	//fgets(buffer,255,stdin);
	n = write(sockfd,&input,sizeof(input));
		if (n < 0)
        	error("ERROR writing to socket");
	
		if(input==1)
		{	printf("Please enter the message: \n");
			
			bzero(buffer,256);
			//fgets(buffer,255,stdin);
			scanf("%s", buffer , 255);

        		
			/*n = read(sockfd, buffer, 256);
			if (n < 0) error("ERROR reading from socket"); */
			
			printf("User Input:%s \n",buffer);
			printf("---------------------- \n");
			
			
			/* Send message to the server */
		
        	
			 n = write(sockfd,buffer,strlen(buffer));
			sleep(5);
			if (n<0)
				error("ERROR writing to socket");
			
			printf("did send message \n");

			//Receive a reply from the server
			n= read(sockfd , server_reply , 255);
			printf("%s \n", server_reply);

			printf("did read reply \n");
		
			if (n < 0)  {
            		perror("ERROR writing to socket \n");
            		exit(1);}

			
			
		}

		else if(input==2)
		{
			
			break;
		}
	
		
	}

    close(sockfd);
    return 0;
}
