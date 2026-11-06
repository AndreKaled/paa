//problem:https://judge.beecrowd.com/pt/problems/view/1661
#include <stdio.h>
#include <stdlib.h>
 
int main() {
 
    int n;
    while(scanf("%d", &n) != EOF){
        if(!n)
            break;
            
        long long int trabalho_total = 0;
        long long int saldo_acc = 0;
        int ai;
        // processa habitantes um a um
        for(int i = 0; i < n; i++){
            scanf("%d", &ai);
            saldo_acc += ai;
            trabalho_total += llabs(saldo_acc);
        }
        
        printf("%lld\n", trabalho_total);
    }
 
    return 0;
}