/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define READ 0
#define WRITE 1

int fd[2];



void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int main(int argc, char *argv[])
{ 

    int sockfd, newsockfd, portno , input;
    char client_message[256];
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    
         

    if (argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

     if(pipe(fd)==-1)
	error("ERROR opening pipe");

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd < 0)
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    
    
    printf("listening...\n");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); 
    printf("listened\n");
	//create thread
    /*int client_sock;
    pthread_t client_threadid;
    while((client_sock = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen) != -1))
    {  	 pthread_create(&client_threadid,NULL,handle_connection,&sockfd);
	 printf("Here\n");*/

    //get  port number
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    if (getsockname(sockfd, (struct sockaddr *)&sin, &len) == -1)
    perror("getsockname");
    else
    printf("port number %d\n", ntohs(sin.sin_port));
	
    /*     //get client ip address
    char clntName[INET_ADDRSTRLEN];
    FILE *output;
   
    if(inet_ntop(AF_INET,&cli_addr.sin_addr.s_addr,clntName,sizeof(clntName))!=NULL) {
    output = fopen("output.txt","a+");  
    fprintf(output,"%s%c%d",clntName,'/',ntohs(cli_addr.sin_port));  
    fclose(output);
    } else {
    printf("Unable to get address\n"); 
    }    */

	if (newsockfd < 0) {
	    	//error("ERROR on accept");
	printf("%d\n",inet_ntoa(cli_addr.sin_addr));
}

	while(1)
	{
            printf("while 1 loop \n");
           sleep(1); 
	bzero(buffer, 256);
	bzero(client_message, 256);

        n = read(newsockfd,&input,sizeof(input));
 

    	if (n < 0) 
            error("ERROR reading from socket");
	printf("input: %d\n",input); 
	//printf("%s \n",buffer);
	//printf("Hello3\n");

	printf("Buffer %s\n", buffer);
 	if(input==1)
    	{	
		//printf("User Input1:\n %s",client_message);
                //Receive a message from client
            while((read(newsockfd , buffer , 255)) > 0 )
 	
              	{   printf("Hello \n");
		    printf("User Input:%s\n",buffer);
		    printf("Hello1 \n");

		    
		    const char* words[3]; // 1
		    words[0] = "rock";
		    words[1] = "paper";
		    words[2]="scissors";

		    const char* random; // 2
		    srand(time(NULL)); //initialize the random seed
		    random = words[rand() % 3]; // 3
		    
		    printf("server makes his choice randomly..\n");
		    sleep(2);
		    printf("%s \n",random);// 4
		    sleep(2);
		    printf("server's choice: %s \n" ,random);
		    printf("client's choice: %s \n" ,buffer);
		    
		    if (!(strcmp(random,"rock")) && !(strcmp(buffer,"rock"))) {
			//message = "isopalia";
			printf("isopalia\n");
			//send message to the client
			n= write(sockfd,"isopalia",strlen("isopalia"));
		     }
		     else if (!(strcmp(random,"rock")) && !(strcmp(buffer,"paper"))) {
			//message = "client is the winner";
			printf("client is the winner");
			n= write(sockfd,"client is the winner",strlen("client is the winner"));
		     }
		     else if (!(strcmp(random,"rock")) && !(strcmp(buffer,"scissors"))) {
			//message = "server is the winner";
			printf("server is the winner");
			n= write(sockfd,"server is the winner",strlen("server is the winner"));
		     }
		     else if (!(strcmp(random,"paper")) && !(strcmp(buffer,"rock"))) {
			//message = "server is the winner";
			printf("server is the winner");
			n= write(sockfd,"server is the winner",strlen("server is the winner"));
		     }
		     else if (!(strcmp(random,"paper")) && !(strcmp(buffer,"paper"))) {
			//message = "isopalia";
			printf("isopalia");
			n= write(sockfd,"isopalia",strlen("isopalia"));
		     }
		     else if (!(strcmp(random,"paper")) && !(strcmp(buffer,"scissors"))) {
			//message = "client is the winner";
			printf("client is the winner");
			n= write(sockfd,"client is the winner",strlen("client is the winner"));
		     }
		     else if (!(strcmp(random,"scissors")) && !(strcmp(buffer,"rock"))) {
			//message = "client is the winner";
			printf("client is the winner");
			n= write(sockfd,"client is the winner",strlen("client is the winner"));
		     }
		     else if (!(strcmp(random,"scissors")) && !(strcmp(buffer,"paper"))) {
			//message = "server is the winner";
			printf("server is the winner");
			n= write(sockfd,"server is the winner",strlen("server is the winner"));
		     }
		     else if (!(strcmp(random,"scissors")) && !(strcmp(buffer,"scissors"))) {
			//message = "isopalia";
			printf("isopalia");
			n= write(sockfd,"isopalia",strlen("isopalia"));
		     } else {
			 printf("error!");

			 //close(sockfd);
			 //return 0;
			}
	
    //edw ok
    		     }
	
           
                     }
    	           else if(input==2)
		   {
			printf("else if input 2");
    			close(sockfd);
			break;
	           }
	
        
        
        //while
        }
	printf("end of main");
    //main   
}

