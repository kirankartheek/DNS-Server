#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 
   
int main(int argc, char *argv[]) 
{ 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024];
    memset(buffer,0,1024); 
   //creating the socket of the client using the socket function present in socket.h header file.
   //AF_INET denoted IPv4 Address and SOCK_STREAM is used to denote that its TCP that is being used.
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
   //htons is used to convert the host byte order to network byte order i.e from little endian format to big endian format.
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form 
   // inet_pton() function converts an Internet address in its standard text format into its numeric binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }
    char *np="entry not found in the database";
    char s[100]; 
    printf("Enter the domain or ip address:\n");
    scanf("%s",s);
   
    //ssize_t send(int socket, const void *buffer, size_t length, int flags);

    send(sock , argv[1] , strlen(argv[1]) , 0 );
    send(sock , "*" , 1 , 0 );
    send(sock , argv[2] , strlen(argv[2]) , 0 );
    send(sock , "*" , 1 , 0 );
    send(sock , s , strlen(s) , 0 );  
    

    valread = read( sock , buffer, 1024);
    if(strcmp(buffer,np)!=0)
    {
        if((int)s[0]<=57&&(int)s[0]>=48)
            printf("The domain name of %s is %s\n",s,buffer);
        else
            printf("The IP Address of %s is %s\n",s,buffer);
    }
    else
        printf("%s\n",np);

    return 0; 
} 
