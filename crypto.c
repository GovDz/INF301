#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "client.h"

void crypteSeq_encoder(char * txt, char * enc) {
    char seq[256] = "";
    char * seen_pt; int seen_loc;
    char tmp_char; int i;
    unsigned long global_id = 0; int len_seq = 0;
    while (global_id < strlen(txt)) {
        seen_pt = strchr(seq, txt[global_id]);
        if (seen_pt == NULL) {
            enc[global_id] = txt[global_id];
            seq[len_seq] = txt[global_id];
            seq[len_seq + 1] = '\0';
            len_seq++;
        } else {
            seen_loc = seen_pt - seq;
            tmp_char = seq[seen_loc];
            if (seen_loc == 0)
                enc[global_id] = seq[len_seq - 1];
            else
                enc[global_id] = seq[seen_loc - 1];
            if (seen_loc < len_seq - 1) {
                for (i = seen_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = tmp_char;
            }
        }
        global_id++;
    }
    enc[global_id] = '\0';
}

void crypteSeq_decoder(char * enc, char * txt) {
    char seq[256] = "";
    char * seen_pt; int seen_loc; int replace_loc;
    char tmp_char; int i;
    unsigned long global_id = 0; int len_seq = 0;
    while (global_id < strlen(enc)) {
        seen_pt = strchr(seq, enc[global_id]);
        if (seen_pt == NULL) {
            txt[global_id] = enc[global_id];
            seq[len_seq] = enc[global_id];
            seq[len_seq + 1] = '\0';
            len_seq++;
        } else {
            seen_loc = seen_pt - seq;
            if (seen_loc == len_seq - 1)
                replace_loc = 0;
            else
                replace_loc = seen_loc + 1;
            txt[global_id] = seq[replace_loc];
            tmp_char = seq[replace_loc];
            if (replace_loc < len_seq - 1) {
                for (i = replace_loc + 1; i < len_seq; i++) {
                    seq[i-1] = seq[i];
                }
                seq[len_seq - 1] = tmp_char;
            }
        }
        global_id++;
    }
    txt[global_id] = '\0';
}

struct liste_chainee
{
    struct cellule *tete;
    int longueur;
    struct cellule *queue;
} liste;
struct cellule
{
    struct cellule *precedent;
    char valeur;
    struct cellule *suivant;
} cel;
void ajouter_debut(struct liste_chainee texte_decode, int valeur_decalage)
{
    //On initialise d'abord toutes nos variables que l'on aura besoin pour la suite
    struct cellule *precedent;
    struct cellule *actuel = texte_decode.queue;
    struct cellule *nvlle_queue;
    struct cellule *nvlle_tete;
    struct cellule *ancienne_queue = texte_decode.queue;
    struct cellule *ancienne_tete = texte_decode.tete;
    for (int i = 0; i < valeur_decalage - 1; i++)
    {
        precedent = actuel->precedent; //On cherche la valeur précédente de l'actuel
    }
    // On remet a jour toutes nos variables
    nvlle_tete = precedent;
    nvlle_queue = nvlle_tete->precedent;
    ancienne_queue->suivant = ancienne_tete;
    ancienne_tete->precedent = ancienne_queue;
    nvlle_tete->precedent = NULL;
    nvlle_queue->suivant = NULL;
    texte_decode.tete = nvlle_tete;
    texte_decode.queue = nvlle_queue;
}
void ajouter_lettre_au_debut(char lettre, struct liste_chainee texte_decode)
{
    //On initialise nos variables
    struct cellule ancienne_tete;
    ancienne_tete.precedent = texte_decode.tete->precedent;
    ancienne_tete.suivant = texte_decode.tete->suivant;
    ancienne_tete.valeur = texte_decode.tete->valeur;
    struct cellule nvlle_tete;

    //On remet à jour nos variables
    nvlle_tete.valeur = lettre;
    nvlle_tete.suivant = &ancienne_tete;
    ancienne_tete.precedent = &nvlle_tete;
    texte_decode.tete = &nvlle_tete;
}
void decoder_texte_decrypteMove_rapide(char *texte_code, char *texte_decode)
/*
 * Fonction:
 *  decoder_texte_decrypteMove
 *
 * Description:
 *  Décrypte un texte crypté à l'aide de l'agorithme crypteMove ainsi qu'une compléxité de O(n)
 *
 * Arguments
 *  texte_code: le texte que l'on cherche a décoder
 *  texte_decode: le texte dans lequel on veut stoquer le texte decodé
 *
 * return: vide
 */
{
    char lettre;
    struct liste_chainee texte_decode_chainee;
    texte_decode_chainee.tete = NULL;
    texte_decode_chainee.queue = NULL;
    texte_decode_chainee.longueur = 0;
    int longueur_texte_code = strlen(texte_code) - 1;
    int longueur_texte_decode_chainee = 0; // initialement le texte decode est vide et sera rempli au fur et a mesure
    for (int index_texte_code = longueur_texte_code; index_texte_code >= 0; index_texte_code--)
    {
        lettre = texte_code[index_texte_code];
        int valeur_decalage = lettre % 8;
        if (longueur_texte_decode_chainee > valeur_decalage) // On vérifie si le texte est suffisamment long pour effectuer le Décalage
        {
            ajouter_debut(texte_decode_chainee, valeur_decalage);
        }
        ajouter_lettre_au_debut(lettre, texte_decode_chainee);
        longueur_texte_decode_chainee++;
    }

    struct cellule *cellule_actuelle = NULL;
    for (int i = 0; cellule_actuelle != texte_decode_chainee.queue; i++)
    {
        texte_decode[i] = cellule_actuelle->valeur;
        cellule_actuelle = cellule_actuelle->suivant;
    }
}

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
