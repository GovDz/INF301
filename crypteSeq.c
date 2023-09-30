#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP

int main() {
    char reponse[MAXREP];
    char msg[MAXMSG];

  // pour stocker la réponse du serveur

    mode_debug(false);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.


    envoyer_recevoir("login 12316038 BOUDELLAL", reponse);
    printf("%s",reponse);
    envoyer_recevoir("load crypteSeq", reponse);
    envoyer_recevoir("start", reponse);
    mydecrypt(reponse, msg);


}
