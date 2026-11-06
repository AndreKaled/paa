//problem: https://judge.beecrowd.com/pt/problems/view/1851
#include <stdio.h>

typedef struct {
    long long Ti, Fi, arrival;
} Dragon;

Dragon heap[100005];
int heap_size = 0;

// a tem prioridade sobre b se Ta/Fa < Tb/Fb
static inline int less(Dragon *a, Dragon *b) {
    return a->Ti * b->Fi < b->Ti * a->Fi;
}

void push(Dragon d) {
    int i = heap_size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!less(&d, &heap[p])) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = d;
}

Dragon pop() {
    Dragon ret = heap[0];
    Dragon last = heap[--heap_size];
    int i = 0;
    if (heap_size > 0) {
        while (1) {
            int l = 2 * i + 1, r = 2 * i + 2, c = -1;
            if (l < heap_size) c = l;
            if (r < heap_size && less(&heap[r], &heap[l])) c = r;
            if (c == -1 || !less(&heap[c], &last)) break;
            heap[i] = heap[c];
            i = c;
        }
        heap[i] = last;
    }
    return ret;
}

int main() {
    long long Ti, Fi, day = 1, free_time = 1, total_fine = 0;

    while (scanf("%lld %lld", &Ti, &Fi) == 2) {
        // Treina enquanto ela estiver livre antes do dia de hoje
        while (free_time < day && heap_size > 0) {
            Dragon cur = pop();
            total_fine += cur.Fi * (free_time - cur.arrival); // só dias dormindo
            free_time += cur.Ti;
        }
        if (free_time < day) free_time = day;

        push((Dragon){Ti, Fi, day});
        day++;
    }

    while (heap_size > 0) {
        Dragon cur = pop();
        total_fine += cur.Fi * (free_time - cur.arrival);
        free_time += cur.Ti;
    }

    printf("%lld\n", total_fine);
    return 0;
}