#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "RunCaesar_crypt.h"

#define MESSAGEHEADER "The secret knows "
#define KEYLEN 8

char charToLetter(char in) {
  // conversion from ASCII:
  // A -> 0, B -> 1...
  if(in > 64 && in < 91) return in - 65;
  if(in > 96 && in < 123) return in - 97;
  return in;
}

bool isLetter(char in) {
  return (in > 64 && in < 91) || (in > 96 && in < 123);
}

char caesar(char message, char key) {
  // Caesar cypher
  return 65 + ((charToLetter(message) + charToLetter(key)) % 26);
}

char* vigenere(char *m, char *k) {
  // Vigenere cypher
  int length = strlen(m);
  char *out = (char *) malloc((length + 1) * sizeof(char));
  int j = 0;
  for(int i = 0; i < length; i++) {
    if(isLetter(m[i])) {
      out[i] = caesar(m[i], k[j]);
      j++;
      j%=KEYLEN;
    } else {
      // do not encrypt symbols
      out[i] = m[i];
    }
  }
  out[length] = 0;
  return out;
}

//char rng() {
//  // return a random byte
//  return (getAdcValue() >> 1) & 0xFF;
//}

void fillKey(char *key) {
  // create random key for vigenere encryption
  randseed = millis()*random(1024);
  randseed = randseed%1024;
  randomSeed(randseed);
  Zufallszahl = random(24)+1;           // globale Variable
  // Serial.print("This number may help!   ");
  // Serial.println(Zufallszahl);
  for(int i = 0; i < KEYLEN; i++) {
    key[i] = 65 + (Zufallszahl);       // globale Variable
//    key[i] = 65 + (rng() % 26);
  }
}

char* encrypt(char* msg) {
  char key[KEYLEN];
  // no one can guess the key if it's random
  fillKey(key);
  char *buf = malloc(sizeof(char) * 50);  // früher 100
  // prepend message header

//  Serial.print(MESSAGEHEADER);
//  Serial.println(msg);
  sprintf(buf, "%s%s", MESSAGEHEADER, msg);
  char *out = vigenere(buf, key);
  free(buf);
  return out;
}
