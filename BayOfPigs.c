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

    memmove(str + x, str, len - x);

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
    envoyer_recevoir("login XXXXXX XXXXXXX", reponse);
    printf("%s",reponse);
    envoyer_recevoir("load BayOfPigs", reponse);
    envoyer_recevoir("start", reponse);
    mydecrypt(reponse, message);
    strcpy(decryptedtxt,"Par otuam eriet");
    envoyer_recevoir(decryptedtxt,reponse);
    mydecrypt(reponse, message);
}
