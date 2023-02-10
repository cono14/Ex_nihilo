#include "Blueprint.hpp"
#include <cstring>


Blueprint::Blueprint(const char a[][AMP_ROOM + 1], BP_Entity entities[], int e_size) {
    for (int i = 0; i < ALT_ROOM; i++) {
        strcpy(mappa[i], a[i]);
    } next = nullptr;

    this->entities = entities;
    this->e_size = e_size;
};


Blueprint* Blueprint::create_map_list(Blueprint* const A[], int i) {
    int j = 0;
    while (j < i - 1) {
        A[j]->next = A[j + 1];
        j++;
    }
    A[j]->next = this;
    this->next = A[0];
    return A[0]->next;
}