//problem: https://judge.beecrowd.com/pt/problems/view/1029
#include <stdio.h>

int cont = 0;

int fib(int n){
    cont++;
    if(n <= 0) 
        return 0;
    if(n == 1)
        return 1;
    return fib(n-1) + fib(n-2);
}

int main(){
    int n;
    scanf("%d", &n);
    while(n){
        n--;
        cont--;
        int val;
        scanf("%d", &val);
        printf("fib(%d) = %d calls = %d\n", val,cont,fib(val));
        cont = 0;
    }
    
}