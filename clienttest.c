#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[])
{
	int sock=0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};
	char message[4000],reply[4000];

	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(8888);

	//Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET,"192.168.114.6",&serv_addr.sin_addr)<=0)
	{
		printf("\n Invalid address/ Address not supported \n");
		return -1;
	}

	if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
	{
		printf("\n Connection Failed \n");
		return -1;
	}

	send(sock,hello,strlen(hello),0);
	printf("Hello message sent \n");
	valread=read(sock,buffer,1024);
	printf("%s\n",buffer);

	int status=1;
	while(status==1)
	{
		printf("Enter your message for server: ");
		fgets(message,4000,stdin);
		send(sock,message,4000,0);
		recv(sock,reply,4000,0);
		printf("\nMessage from server : %s",reply);
	}
	return 0;
}
