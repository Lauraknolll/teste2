#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -99999

typedef struct _hash 
{
   int key;
} Hash;

int h(int chave, int M)
{
    return chave % M;
}

int h2(int chave, int M)
{
    return 1 + (chave % (M-1));
}

int linear_probing (int chave, int iter, int M) 
{
   return (h(chave, M) + iter) % M;
}

int quadratic_probing (int chave, int iter, int M) 
{
   int c1 = 1;
   int c2 = 3;
   return (h(chave, M) + c1*iter + c2*iter*iter) % M;
}

int double_hash (int chave, int iter, int M) 
{
   return (h(chave, M) + iter*h2(chave, M)) % M;
}

/* */
Hash* create_hash (int M)
{ 
   int h;
   Hash *H = (Hash *)malloc(M * sizeof(Hash));
   for (h = 0; h < M; h++) {
      H[h].key = EMPTY;
   }
   return H;
}

/* */
void free_hash (Hash *H, int M) 
{
   free(H);
}

/* */
int hash_search (Hash *H, int M, int key) 
{
   int j, i = 0;
   do {
      //j = linear_probing (key, i, M);
      j = quadratic_probing (key, i, M);
      //j = double_hash (key, i, M);
      printf("Testando chave: %d\n", j);
      if (H[j].key == key) {
         return j;
      }
      i++;
   } while ((i != M) || (H[j].key != EMPTY));
}

/* */
int hash_insert (Hash *H, int M, int key, int *colisoes) 
{
   int j, i = 0;
   do {
      //j = linear_probing (key, i, M);
      j = quadratic_probing (key, i, M);
      //j = double_hash (key, i, M);
      if (H[j].key == EMPTY) {
         H[j].key = key;
         return j;
      }
      else {
         *colisoes = *colisoes + 1;
      }
      i++;
   } while (i != M);
}

/* */
void hash_print (Hash *H, int M) 
{
   int i;
   for (i = 0; i < M; i++) {
      if (H[i].key != EMPTY) {
         printf("%2d - %d\n", i, H[i].key);
      }
      else {
         printf("%2d -   \n", i);
      } 
   }
}

int main ()
{
   int colisoes = 0;
   int M = 11;
   Hash *H = create_hash (M);
   hash_insert (H, M, 10, &colisoes);
   hash_insert (H, M, 22, &colisoes);
   hash_insert (H, M, 31, &colisoes);
   hash_insert (H, M, 4, &colisoes);
   hash_insert (H, M, 15, &colisoes);
   hash_insert (H, M, 28, &colisoes);
   hash_insert (H, M, 17, &colisoes);
   hash_insert (H, M, 88, &colisoes);
   hash_insert (H, M, 59, &colisoes);
   printf("Numero de colisoes: %d\n", colisoes);
   hash_print (H, M);
   free_hash (H, M);
   return 0;
}
