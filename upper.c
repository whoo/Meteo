#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

#define URL "Arabie saoudite : arrestation de 431 personnes accusées d'être liées à l'EI"


int main(int argc, char **argv)
{

	char *tb=URL;
	printf("%s\n",Supper(tb));
	return 0;
}
