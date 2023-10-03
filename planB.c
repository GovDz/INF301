#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

void caesarEncrypt(char *secret, int shift) {
    int length = strlen(secret);

    for (int i = 0; i < length; i++) {
        char c = secret[i];

        if (isalpha(c)) {
            char base = (islower(c)) ? 'a' : 'A';
            secret[i] = (c - base - shift) % 26 + base;

            // Ensure the result is a positive index
            if (secret[i] < base) {
                secret[i] += 26;
            }
        }
    }
}

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    char lettre1, lettre2;
    int decalage;
    char secret[20] = "hasta la revolucion";
    envoyer_recevoir("login XXXXXX XXXXXXX", reponse);
    envoyer_recevoir("load planB", reponse);
    envoyer_recevoir("ok", reponse);
    envoyer_recevoir("help", reponse);
    printf("%s\n", reponse);


    lettre1 = 'c';
    lettre2 = reponse[0];
    lettre1 = toupper(lettre1);
    lettre2 = toupper(lettre2);
    decalage = lettre2 - lettre1;
    if (decalage < 0) {
        decalage = 26 + decalage;
    }
    caesarEncrypt(secret,decalage);
    envoyer_recevoir("start", reponse);
    envoyer_recevoir("42", reponse);
    envoyer_recevoir(secret, reponse);
    printf("%s\n", reponse);

    // Notez qu'ici on n'utilise pas la reponse du serveur

    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse);
    printf("%s",reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
