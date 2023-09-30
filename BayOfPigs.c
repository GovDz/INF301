#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void addCharToBeginning(char *str, char ch) {
    // Calculate the length of the original string
    size_t len = strlen(str);

    // Shift the characters in the string to the right to make room for the new character
    for (size_t i = len; i > 0; i--) {
        str[i] = str[i - 1];
    }

    // Add the new character to the beginning of the string
    str[0] = ch;
}

void moveLastXToStart(char *str, int x) {
    int len = strlen(str);

    // Check if x is valid (less than or equal to the string length)
    if (x > len) {
        return;
    }

    char temp[x + 1];

    // Copy the last x characters to the temporary buffer
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
    char reponse[MAXREP];
    char message[MAXREP];
    char decryptedtxt[MAXREP];
    // pour stocker la réponse du serveur

    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12316038 BOUDELLAL", reponse);
    printf("%s",reponse);
    envoyer_recevoir("load BayOfPigs", reponse);
    envoyer_recevoir("start", reponse);
    mydecrypt(reponse, message);
    strcpy(decryptedtxt,"Par otuam eriet");
    envoyer_recevoir(decryptedtxt,reponse);
    mydecrypt(reponse, message);
}
