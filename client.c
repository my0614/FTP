
/* 소켓을 생성하고 서버에 connect 작업을 수행한 후, 소켓의 fd 반환 */
int open_connection(const char *host, int port)
{
	int sock = 0;
	int err_chk = 0;
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(host);
	serv_addr.sin_port = htons(port);

	err_chk = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (err_chk == -1) {
		return -1;
	}
	return sock;
}

int main(int argc , char *argv[])
{
    if(argc != 3)
    {
        printf("argc 개수 에러\n");
        exit(1);
    }

    sock = open_connection(argv[1], atoi(argv[2])); // 루프백, 포트번호

    while(1)
    {
        scanf("%s",buffer);
        send(sock, buffer, 1024,0); // 보내기
         if(!strcmp(buffer,"ls"))
        {
            int name_count;
            recv(sock,&name_count,sizeof(name_count),0); // ls 파일 개수 가져오기
            for(int i=0;i<name_count;i++)
            {
                recv(sock, buffer, 1024,0); // ls출력
                printf("%s\n",buffer);
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
