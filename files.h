#ifndef FILES_H
#define FILES_H

char *get_file_name(char *path);
int download(int sock);
int upload(int sock, char *path);

#endif
