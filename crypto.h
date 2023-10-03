#ifndef __CRYPTO_H__
#define __CRYPTO_H__
#include "client.h"
#include <stdio.h>
#include <string.h>

void crypteSeq_encoder(char * txt, char * enc);

void crypteSeq_decoder(char * enc, char * txt);

void ajouter_debut(char * txt, char * enc);

void ajouter_lettre_au_debut(char * enc, char * txt);

void decoder_texte_decrypteMove_rapide(char * txt, char * enc);

void moveFirstXToEnd(char * enc, int x);

#endif