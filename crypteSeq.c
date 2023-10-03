#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAXMSG MAXREP



void crypteSeq_dec(char * enc, char * txt) {
    char seq[256] = "";
    char * pt; int loc;
    int replace_loc;
    char tmp;
    int i;
    unsigned long id = 0; int len_seq = 0;
    while (id < strlen(enc)) {
        pt = strchr(seq, enc[id]);
        if (pt == NULL) {
            txt[id] = enc[id];
            seq[len_seq] = enc[id];
            seq[len_seq + 1] = '\0';
            len_seq++;
        } else {
            loc = pt - seq;
            if (loc == len_seq - 1)
                replace_loc = 0;
            else
                replace_loc = loc + 1;
            txt[id] = seq[replace_loc];
            tmp = seq[replace_loc];
            if (replace_loc < len_seq - 1) {
                for (i = replace_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = tmp;
            }
        }
        id++;
    }
    txt[id] = '\0';
}


void crypteMove_dec(char * enc, char * dec) {
    char buffer[MAXREP];
    int len_dec;
    int ln_enc;
    int X;
    int i;
    len_dec = 0;
    ln_enc = strlen(enc) - 1;
    while (ln_enc >= 0) {
        X = enc[ln_enc] % 8;
        if (len_dec > X) {
            strcpy(buffer, dec + len_dec - X);
            dec[len_dec - X] = '\0';
            strcat(buffer, dec);
            strcpy(dec + 1, buffer);
        } else {
            for (i = len_dec; i >= 0; i--) {
                dec[i+1] = dec[i];
            }
        }
        dec[0] = enc[ln_enc--];
        len_dec++;
    }
    dec[len_dec] = '\0';
}

void crypteSeq_enc(char * dec, char * enc) {
    char seq[256] = "";
    char * pt;
    int loc;
    char tmp; 
    int i;
    unsigned long id = 0; 
    int len_seq = 0;
    while (id < strlen(dec)) {
        pt = strchr(seq, dec[id]);
        if (pt == NULL) {
            enc[id] = dec[id];
            seq[len_seq] = dec[id];
            seq[len_seq + 1] = '\0';
            len_seq++;
        } else {
            loc = pt - seq;
            tmp = seq[loc];
            if (loc == 0)
                enc[id] = seq[len_seq - 1];
            else
                enc[id] = seq[loc - 1];
            if (loc < len_seq - 1) {
                for (i = loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = tmp;
            }
        }
        id++;
    }
    enc[id] = '\0';
}

int main() {
    char reponse[MAXREP];
    char text[MAXREP];
    char dec[MAXREP];

  // pour stocker la réponse du serveur

    mode_debug(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr", 9999);
    // utilisez le port 443 en cas de problème sur le 9999
    /* connexion("im2ag-appolab.u-ga.fr", 443); */

    // Remplacez <identifiant> et <mot de passe> ci dessous.


    envoyer_recevoir("login XXXXXX XXXXXXX", reponse);
    envoyer_recevoir("load crypteSeq", reponse);
    crypteMove_dec(reponse, text);
    printf("\n%s\n", text);
    text[0] = '\0';
    envoyer_recevoir("start", reponse);
    crypteMove_dec(reponse, text);
    printf("\n%s\n", text);
    crypteSeq_enc(text, dec);
    text[0] = '\0';

    envoyer_recevoir(dec, reponse);
    crypteSeq_dec(reponse + 83, text);
    printf("\n%s\n", text);
    text[0] = '\0';

    envoyer_recevoir("C'est fini?", reponse);
    return 0;


}
