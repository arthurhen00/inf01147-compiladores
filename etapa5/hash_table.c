// Compiladores - Etapa 5 - Marcelo Johann - 2024/01
// Arthur Hendges da Silva - 00332968
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

hash_t *hashTable[HASH_SIZE];

void hashInit() {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int hashHorner(char *str) {
    int p = 31;
    int hash = 0;
    int ascci = 0;
    int textSize = strlen(str);

    for (int i = 0; i < textSize; i++) {
        ascci += (int)str[i];
        hash = (p * hash + ascci) % HASH_SIZE;
    }

    return hash;  
}

hash_t *hashSearch(char *str) {
    int hash = hashHorner(str);
    hash_t *node = hashTable[hash];

    for ( ;node ;node = node->next) {
        if (!strcmp(node->str, str)) {
            return node;
        }
    }

    return NULL;
}

hash_t *hashInsert(char *str, int type) {
    int hash = hashHorner(str);

    hash_t *newNode = hashSearch(str);
    if (newNode) {
        return newNode;
    }

    newNode = (hash_t*)malloc(sizeof(hash_t));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }

    newNode->str = strdup(str);
    if (newNode->str == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(newNode);
        return NULL;
    }

    newNode->type = type;
    newNode->next = hashTable[hash];
    hashTable[hash] = newNode;
    return newNode;
}

void hashPrint() {
    hash_t *node;
    for (int i = 0; i < HASH_SIZE; i++) {
        for (node = hashTable[i]; node; node = node->next) {
            fprintf(stderr, "hash %3d -> [%8s %3d %3d]\n", i, node->str, node->type, node->datatype);
        }
    }
}

hash_t *makeTemp() {
    static int num = 0;
    char buffer[256];

    sprintf(buffer, "_temp%d", num++);
    return hashInsert(buffer, SYMBOL_VAR);
}

hash_t *makeLabel() {
    static int num = 0;
    char buffer[256];

    sprintf(buffer, "_label%d", num++);
    return hashInsert(buffer, SYMBOL_LABEL);
}