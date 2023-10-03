#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void addCharToBeginning(char *str, char ch) {
    size_t len = strlen(str);

    for (size_t i = len; i > 0; i--) {
        str[i] = str[i - 1];
    }

    str[0] = ch;
}

void moveLastXToStart(char *str, int x) {
    int len = strlen(str);

    if (x > len) {
        return;
    }

    char temp[x + 1];

    strncpy(temp, str + len - x, x);
    temp[x] = '\0';

    // Shift the remaining characters to the end
    memmove(str + x, str, len - x);

    // Copy the temporary buffer (last x characters) to the beginning of the string
    strncpy(str, temp, x);
}


void mydecrypt(char *msg, char *decryptedtxt) {
    int i=strlen(msg);
    char C;
    int X;
    while (i != -1) {
        C = msg[i];
        X = C % 8;
        moveLastXToStart(decryptedtxt, X);
        addCharToBeginning(decryptedtxt, C);
        i--;

    }
    printf("%s\n", decryptedtxt);
}

int main() {
    char msg[MAXMSG];
    char decryptedtxt[MAXMSG];
    strcpy(msg;)
}
