// Etapa 2
// Arthur Hendges da Silva - 00332968
// 2024/01

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

void hashInit(hash_t *table[]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        table[i] = NULL;
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

hash_t *hashSearch(hash_t *table[], char *str) {
    int hash = hashHorner(str);
    hash_t *node = table[hash];

    for ( ;node ;node = node->next) {
        if (!strcmp(node->str, str)) {
            return node;
        }
    }

    return NULL;
}

hash_t *hashInsert(hash_t *table[], char *str, int type) {
    int hash = hashHorner(str);

    hash_t *newNode = hashSearch(table, str);
    if (newNode) {
        // fprintf(stderr, "Literal %s already in use.\n", str);
        return NULL;
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
    newNode->next = table[hash];
    table[hash] = newNode;
    return newNode;
}

void hashPrint(hash_t *table[]) {
    hash_t *node;
    for (int i = 0; i < HASH_SIZE; i++) {
        for (node = table[i]; node; node = node->next) {
            fprintf(stderr, "hash %4d -> [%s %d]\n", i, node->str, node->type);
        }
    }
}