#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 80

int main(int argc, char** argv){
        int fd, letti;
        char buffer[MAX];

        if(argc != 2){
                printf("Usage:\nccat filename");
                exit(0);
        }
        fd = open(argv[1], O_RDONLY);

        while((letti = read(fd,buffer,MAX)) > 0){
                write(1, buffer, letti);
        }

        close(fd);
}
