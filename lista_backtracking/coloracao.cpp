#include <stdio.h>
#include <vector>
using namespace std; 

int N, M, cliques = 0;
char img[1024][1025];

//funcao de busca em profundidade pra pintar a imagem
void dfs(int i, int j){
    vector<pair<int, int>> pilha;
    pilha.push_back({i,j});
    img[i][j] = 'o';
    
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};
    
    while(!pilha.empty()){
        int x = pilha.back().first;
        int y = pilha.back().second;
        pilha.pop_back();
        
        for(int i = 0; i < 4; i++){
            int ni = x + di[i];
            int nj = y + dj[i];
            
            if(ni >= 0 && ni < N && nj >= 0 && nj < M &&
                img[ni][nj] == '.'){
                    img[ni][nj] = '0';
                    pilha.push_back({ni, nj});
            }
        }
    }
}

int main() {
 
    scanf("%d %d", &N, &M);
    
    for(int i = 0; i < N; i++)
        scanf("%s", img[i]);
    
    //percorre a imagem e quando acha um ponto
    //conta como clique e pinta o resto
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(img[i][j] == '.'){
                cliques++;
                dfs(i, j);
            }
        }
    }
    
    printf("%d\n", cliques);
 
    return 0;
}