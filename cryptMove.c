#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void moveFirstXToEnd(char *str, int x) {
    int len = strlen(str);

    if (x >= len) {
        return; // No need to move if x is greater than or equal to the string length
    }

    char temp[x];
    strncpy(temp, str, x); // Copy the first x characters to a temporary array
    memmove(str, str + x, len - x); // Shift the remaining characters to the beginning of the string
    strncpy(str + len - x, temp, x); // Copy the first x characters from the temporary array to the end
}


void mycrypt(char *msg, char *decryptedtxt) {
    char *temp;
    int i=0;
    char C;
    int X;
    while (msg[0] != '\0') {
        C = msg[0];
        decryptedtxt[i] = C;
        temp = msg + 1;
        strcpy(msg, temp);
        X = C % 8;
        moveFirstXToEnd(msg, X);
        i++;
    }

}

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG];
    char key[MAXREP];
    char msg[MAXMSG];
    // char test[MAXMSG];
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    //strcpy(test,"Patria o muerte");
    envoyer_recevoir("login 12316038 BOUDELLAL", reponse);
    printf("%s",reponse);
    envoyer_recevoir("load crypteMove", reponse);
    envoyer_recevoir("help", reponse);
    strcpy(key,reponse);
    // mycrypt(test,msg);
    printf("%s\n",msg);
    mycrypt(key,msg);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir(msg, reponse);
    printf("%s",reponse);


    // Notez qu'ici on n'utilise pas la reponse du serveur

    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse);
    printf("%s",reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    strcpy(message, "Petit message court.");
    // pour stocker le message à envoyer au serveur
    mycrypt(message, reponse);
    // Affiche les échanges avec le serveur (false pour désactiver)

    return 0;
}
