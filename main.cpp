#include <iostream>
#include <string>
#include <cstdlib> 
#include <cstring> 
#include <unistd.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
using namespace std;
void Exception(const string & why, const int exitCode ) 
{
    cout << "ErrorCode:"<<exitCode <<endl<< why << endl;
    exit(exitCode);
}
int main()
{
    
    
    sockaddr_in * kera = new (sockaddr_in);
    kera->sin_family = AF_INET; 
    kera->sin_port = 0;         
    kera->sin_addr.s_addr = 0;  

    
    sockaddr_in * jhf = new (sockaddr_in);
    jhf->sin_family = AF_INET;     
    jhf->sin_port = htons(7);  
    jhf->sin_addr.s_addr = inet_addr("82.179.90.12"); 
    
    
    char *buffer = new char[4096];
    strcpy(buffer,"hello world");   
    int msgLen = strlen(buffer);          
   
    
    int mySocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (mySocket == -1) {
        close(mySocket);
        Exception("Error open socket",11);
    }
    
    int rc = bind(mySocket,(const sockaddr *) kera, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error bind socket with local address",12);
        }

   
    rc = connect(mySocket, (const sockaddr*) jhf, sizeof(sockaddr_in));
    if (rc == -1) {
        close(mySocket);
        Exception("Error connect socket with remote server.", 13);
    }

   
    rc = send(mySocket, buffer, msgLen, 0);
    if (rc == -1) {
        close(mySocket);
        Exception("Error send meskerage", 14);
    }
    cout << " send: " << buffer << endl; 
      
    
    rc = recv(mySocket, buffer, 4096, 0);
    if (rc == -1) {
        close(mySocket);
       Exception("Error receive answer.", 15);
    }
    buffer[rc] = '\0'; 
    cout << " receive: " << buffer << endl; 
    
    close(mySocket);

    delete kera;
    delete jhf;
    delete[] buffer;
    return 0;
}
