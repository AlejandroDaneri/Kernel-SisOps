#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>


void main (void) {
        char buf[12] = "cmdline: ";
        char *aux = "ufasdasdasdasf";
        char otro[12] = {0};
        strncat(buf, aux, sizeof(buf)-strlen(buf)-1);
        printf("%s\n",buf);
}