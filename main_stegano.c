#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc < 4 || argc > 5 || (argv[1][0] == 'd' && argc != 4) || (argv[1][0] == 'e' && argc != 5))
	{		
		printf("ERROR: Wrong parameters!\n");
		printf("Usage:\n");
		printf("For encryption: ./stegano [e] [source file] [destination file] [text file]\n");
		printf("For decryption: ./stegano [d] [source file] [text file]\n");
		return 0;
	}
	stegano(argv);
	return 0;
}
