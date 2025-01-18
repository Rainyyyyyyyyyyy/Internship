#include <iostream>
#include <sys/types.h>    
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "DynLib.h"


int main(int argc, char **argv){	
	int server_port;
	std::cout<<"Enter port for server: ";
	std::cin>>server_port;
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;  // семейство адресов IPv4
	serverAddress.sin_port = htons(server_port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
	listen(serverSocket, 1);

	char *net_buf = new char[128];
	int clientSocket = accept(serverSocket, nullptr, nullptr);
	while(true){
		ssize_t bytes_read = recv(clientSocket, net_buf, sizeof(net_buf), 0);
		if (bytes_read == 0) {
      // Соединение закрыто клиентом
      printf("Connection closed by client\n");
      close(clientSocket);
			clientSocket = accept(serverSocket, nullptr, nullptr);
			continue;
		}else{
			int size=0;
			char *local_mes = new char[128];
			int S = 0;
      // конвертирование строки в число
			while(net_buf[size]!='\0'){
				S = S * 10 + net_buf[size]-48;
				local_mes[size] = net_buf[size];
				size++;
			}
			local_mes[size] = '\0';
			if(f3(S))std::cout<<local_mes<<'\n';
			else std::cout<<"Error\n";
    }
	}
	return 0;
}
