#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

char *get_file_name(char *path)
{

    int path_len = strlen(path);
    for(int i = path_len-1;i>=0;i--)
    {
        if(path[i] == '/')
        {
            return &path[i+1]; 
        }
    }
    return path;
}

int download(int sock)
{
    int fp;
    int size = 0;
    char buffer[1024] = {0,};
    char file_name[1024] = {0,};
    recv(sock, &size, sizeof(size),0);
    printf("size = %d\n",size);
    recv(sock, file_name, sizeof(file_name), 0);
    printf("file_name = %s\n",file_name);
    int alllen = 0;
    int len = 0;
    fp = open(file_name, O_RDONLY);
    if (fp == NULL) {
        printf("ERR\n");
        return 0;
    }
    while((len = recv(sock, buffer,1024, 0)) > 0)
    {
        alllen += len;
        write(fp, buffer,sizeof(buffer),fp); // file write
        if(size <= alllen)
        {
            break;
        }
    }
    printf("all : %d\n", alllen);
    printf("success");
}



int upload(int sock, char *path)
{
    struct stat fsize;
    char buffer[1024];
    int size = 0;
    int len = 0;
    char *file_name = get_file_name(path);
    int fp;
    fp = open(path, O_RDONLY);
    if (fp == NULL) {
        printf("ERR\n");
        return 0;
    }
    fstat(fp, &fsize);
    size = fsize.st_size;
    printf("size = %d\n", size);
    send(sock, &size, sizeof(size), 0);
     
    send(sock, file_name, strlen(file_name) + 1, 0); // file name send
    printf("file_name = %s\n", file_name);
    printf("Start\n");
    while((len = read(fp, buffer, sizeof(buffer))) > 0)
    {
        printf("... len = %d\n", len);
        send(sock, buffer,len,0); // file send
    }
    printf("success");
}
