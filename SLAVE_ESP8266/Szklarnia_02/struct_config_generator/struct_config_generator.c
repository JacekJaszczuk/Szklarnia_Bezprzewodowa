// Generator pliku struktury dla programu "Szklarnia_02".
#include "../struct_config.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	// Zmienne programu:
	int fd;      // Deskryptor pliku.

	// Otwórz plik:
	fd = open("../data/struct_config.bin", O_WRONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}

	// Zapisz strukturę do pliku:
	if  (write(fd, &config, sizeof(config)) < 0)
	{
		perror("write");
		exit(1);
	}

	// Zamknij plik:
	close(fd);

	return 0;
}
