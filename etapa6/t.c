#include <stdio.h>

int funcao(int a, int b, int c, 
            int d, int e, int f, 
            int g, int h, int i, 
            int j, int k, int l,
            int m, int n, int o,
            int p, int q, int r,
            int s, int t, int u,
            int v, int w, int x) { return o; }

int entrada1 = 10;
int entrada2 = 20;

int main() {
    
    printf("%d\n", funcao(entrada1,entrada2,entrada2,entrada2,
                        entrada2,entrada2,entrada2,entrada2,
                        entrada2,entrada2,entrada2,entrada1,entrada1,
                            entrada1,entrada1,1,2,3,4,5,6,7,8,9));

}
