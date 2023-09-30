#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP]; // pour stocker la réponse du serveur
    char message[MAXMSG]; // pour stocker le message à envoyer au serveur

    // Affiche les échanges avec le serveur (false pour désactiver)
    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    int ret;
    ret = envoyer_recevoir("login 12316038 BOUDELLAL", reponse);
    prefix_print(stderr, COL_RECU, reponse);
    ret = envoyer_recevoir("load tutorielFORT", reponse);
    ret = envoyer_recevoir("start", reponse);
    ret = envoyer_recevoir("OK", reponse);
    ret = envoyer_recevoir("OUI", reponse);
    for (int k= 0 ; k!= 10 ; k++ ){
        for (int j= 0 ; j != 10 ; j++ ){
            int i = 0;
            strcpy(message, reponse);
            while (message[i]) {
                message[i] = toupper(message[i]);
                i++;
            }
            ret = envoyer_recevoir(message, reponse);
            prefix_print(stderr, COL_RECU, reponse);
    }


    // Notez qu'ici on n'utilise pas la reponse du serveur

    lire_clavier(message);   // message tapé au clavier
    envoyer_recevoir(message, reponse); // on envoie message, et on reçoit la réponse du serveur

    printf ("Réponse du serveur: %s", reponse);

    printf ("Fin de la connection au serveur\n");
    return 0;
}
}