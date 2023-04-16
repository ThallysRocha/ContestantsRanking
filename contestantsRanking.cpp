
#include <bits/stdc++.h>
using namespace std;
void add_edge(vector<int> adj[], int src, int dest){
    adj[src].push_back(dest);
    adj[dest].push_back(src);
}
// a modified version of BFS that stores predecessor
// of each vertex in array p
// and its distance from source in array d
bool BFS(vector<int> adj[], int src, int dest, int v,int pred[], int dist[]){
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;
 
    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[v];
 
    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
 
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    // standard BFS algorithm
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
 
// utility function to print the shortest distance
// between source vertex and destination vertex
int shortestDistance(vector<int> adj[], int s, int dest, int v){
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        if(dest == s){
         return dist[dest];
        }
        else{
          //valor escolhido para representar a ausência de caminho
          return 100000;
        }
    }
    return dist[dest];
}

int main(){

    
    int iteracoes = 0;
    cin>>iteracoes;
    for(iteracoes;iteracoes>0;iteracoes--){
        
        int qtdPartidas = 0;
        cin>>qtdPartidas;
        //cada partida tem 3 participantes, então o tamanho máximo do vetor será: 
        int tam_max = (3*qtdPartidas)+1;
        vector<int> grafo[tam_max];
        /*agora é criado um dicionário que vai garantir que cada nome se relacione com um inteiro, dado pelo MapIndex, que será inicializado como 1 
        pois vamos usar a propriedade do map que quando o não foi atribuido nada ainda, o valor retornado será 0.
        */
        map<string, int> indiceNome;
        int MapIndex = 1;
        // temos aqui o nosso ranking, que será um vetor de pares que terá a distância e o nome. A ordem deve ser essa para poder usar a função sort() no final.
        vector<pair<int,string>> nomes_ranking;
        
        for(qtdPartidas;qtdPartidas>0;qtdPartidas--){
            string en;
            string members[3];
            for(int i = 0; i < 3; i++){
                cin>>en;
                members[i] = en;
                //Aqui checamos se o nome não foi mapeado, e se sim, ele ganhará um número e seu nome será adicionado ao vetor do ranking.
                if(indiceNome[en] == 0){
                    indiceNome[en] = MapIndex;
                    nomes_ranking.push_back(make_pair(-1,en));
                    //no fim o indice do mapeamento deve ser incrementado
                    MapIndex++;
                    
                }
            }
            //Adicionando os vértices, cada um dos tres nomes de cada entrada vai ter um vertice um com o outro.
            add_edge(grafo, indiceNome[members[0]],indiceNome[members[1]]);
            add_edge(grafo, indiceNome[members[0]],indiceNome[members[2]]);
            add_edge(grafo, indiceNome[members[2]],indiceNome[members[1]]);
        }
        cout<<nomes_ranking.size()<<"\n";
        for(int i = 0;i<nomes_ranking.size();i++){
            //a primeira posição do pair será a distância para vertice o qual o número foi mapeado a partir de "Ahmad".
            nomes_ranking[i].first = shortestDistance(grafo,indiceNome[nomes_ranking[i].second], indiceNome["Ahmad"], tam_max);
            
        }
        /* 
        O último passo é ordenar o ranking, primeiro pela distância, e depois pelo nome, de forma crescente, é exatamente isso que a função sort() vai fazer,
        só é preciso passar o início e o fim do vetor, e como é um par, ele levará em consideração o primeiro e depois o segundo elemento.
        */
        sort(nomes_ranking.begin(), nomes_ranking.end());
        for(int i = 0;i<nomes_ranking.size();i++){
            //depois de ordenados, precisamos printar na ordem certa e substituindo os que não tem ligação com o "Ahmad" para uma distância "undefined".
            if(nomes_ranking[i].first!=100000){
                cout<<nomes_ranking[i].second<<" "<<nomes_ranking[i].first<<"\n";
            }
            else{
                cout<<nomes_ranking[i].second<<" "<<"undefined\n";
            }
        }
    }


    return 0;
}


