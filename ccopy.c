#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "macros.h" // macro per la gestione degli errori

#define BUFFER_SIZE 1

int main(int argc, char** argv){
	int fd1, fd2, letti;
	char scelta;
	char buffer[BUFFER_SIZE];

	if(argc != 3){
		WRITE("Usage\nccopy file1 file2\n\n");
		exit(1);
	}

	IFERROR((fd1 = open(argv[1],O_RDONLY)),argv[1]);

	if((fd2 = open(argv[2],O_RDONLY,644)) != -1){
		do{
			printf("Il file gia esiste, si vuole sovrascrivere (S o N)");
			scanf(" %c",&scelta);
		}while(scelta != 's' && scelta != 'n');
			close(fd2);
		if(scelta == 'n'){
			close(fd1);
			exit(0);
		}
	}

	IFERROR((fd2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,644)),argv[2]);


	while((letti = read(fd1,buffer,BUFFER_SIZE)) > 0){
		IFERROR(write(fd2,buffer,letti),argv[2]);
	}

	IFERROR(close(fd1),argv[1]);
	IFERROR(close(fd2),argv[2]);

	return 0;
}
