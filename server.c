#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>

int open_server(int port)
{
	int serv_sock = 0;
	int err_chk = 0;
	struct sockaddr_in serv_addr;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1) {
		return -1;
	}
    
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	err_chk = bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (err_chk == -1) {
		return -1;
	}

	err_chk = listen(serv_sock, 5);
	if (err_chk == -1) {
		return -1;
	}

	return serv_sock;
}


int main(int argc, char *argv[])
{
    socklen_t clnt_addr_size;
    struct sockaddr_in clnt_addr;
    int serv_sock = 0;
    int clnt_sock = 0;
    char buffer[1024];

    if(argc != 2)
    {
        printf("argc 개수가 틀림\n");
        exit(1);
    }

    serv_sock = open_server(atoi(argv[1]));
    clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);


    while(1)
    {
        recv(clnt_sock, buffer, 1024,0); // 받아오기
        if(!strcmp(buffer,"ls"))
        {
            int name_count = 0;
            struct dirent ** name_list = NULL;
            
            name_count = scandir(".",&name_list,NULL,alphasort); // 디렉토리의 내용 가져오기

            send(clnt_sock,&name_count, sizeof(name_count),0); // name_count 보내기

            for(int i=0;i<name_count;i++)
            {
                strcpy(buffer, name_list[i] -> d_name); // buffer에 복사해서
                send(clnt_sock, buffer, 1024, 0); // buffer를 send
            }
        }
        else if(!strcmp(buffer,"cd"))
        {

        }
        else if(!strcmp(buffer,"get"))
        {

        }
        else if(!strcmp(buffer,"put"))
        {

        }
    }

 
    
}