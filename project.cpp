#include <iostream>
#include<climits>
#include<queue>
using namespace std;


struct edge {
    int flow=0;
    int cost=0;

};
edge arr[203][203];
edge arr1[203][203];



int maxOfArr(int N, int tab[]){
    int res = 0;
    for (int i=0; i<N;i++){
        res = max(res,tab[i]);
    }
    return res;
}




void findMinCostPaths(int s, int N, int distance[],int parents[]) {
    queue<int> Q;
    int processed[N];
    for (int i=0;i<N;i++){
        distance[i] = INT_MAX;
        parents[i] = -1;
        processed[i] = false;
    }

    distance[s] = 0;
    Q.push(s);

    while (!Q.empty()) {

        int u = Q.front();
        Q.pop();
        processed[u] = false;

        for (int v=0; v<N; v++) {
            if(arr1[u][v].flow > 0){
                if (distance[v] > distance[u] + arr1[u][v].cost) {
                    distance[v] = distance[u] + arr1[u][v].cost;
                    parents[v] = u;
                    if (!processed[v]) {
                        processed[v] = true;
                        Q.push(v);
                    }
                }
            }
        }
    }
}

int minCostFlow(int N,int combats, int s, int t, int T) {

    int distance[N];
    int parents[N];

    int flow = 0;
    int cost = 0;

    while (flow < combats) {
        findMinCostPaths(s, N, distance, parents);
        if (distance[t] == INT_MAX){
            break;
        }

        int currflow = combats - flow;
        int v = t;
        while (v != s) {
            currflow = min(currflow, arr1[parents[v]][v].flow);
            v = parents[v];
        }

        flow += currflow;
        cost += currflow * distance[t];
        v = t;
        while (v != s) {
            arr1[parents[v]][v].flow -= currflow;
            arr1[v][parents[v]].flow += currflow;
            arr1[v][parents[v]].cost = -arr1[parents[v]][v].cost;

            v = parents[v];
        }
    }

    if (flow < combats || arr[0][t].flow <T){
        return INT_MAX;}
    else{
        return cost;}
}



bool microbribery(int s,int t,int startN,int combats,int money,int B){
    int min_cost;
    int N = startN+2;


    for(int T=0;T<startN;T++){

        for(int i=0;i<startN;i++){
            arr[i][t].cost = B;
            arr[i][t].flow = T;
        }
        arr[0][t].cost = 0;


        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                arr1[i][j].cost = arr[i][j].cost;
                arr1[i][j].flow = arr[i][j].flow;
            }
        }

        min_cost = minCostFlow(N,combats,s,t,T);
        if(min_cost != INT_MAX){
            int k = min_cost - B*(combats-T);
            if (k<=money){
                return true;
            }
        }
    }
    return false;
}


int main() {

    int numOfsets;
    cin >> numOfsets;

    for(int k =0; k< numOfsets ;k++){
        int money, startN,combats;
        cin >> money >> startN;
        combats = (startN*(startN-1))/2;

        int wins[startN];
        for(int i=0;i<startN;i++){
            wins[i] =0;
        }

        int v1,v2,w,price;
        int B =1;
        for (int i = 0; i< combats; i++){
            cin >> v1 >> v2 >> w >> price;
            edge e;
            e.cost = price;
            e.flow = 1;
            B += price;
            if(v1 == w){
                arr[v1][v2].cost = price;
                arr[v1][v2].flow = 1;
            }
            else{
                arr[v2][v1].cost = price;
                arr[v2][v1].flow = 1;

            }
            wins[w] += 1;
        }

        if(maxOfArr(startN, wins)<=wins[0]){
            cout<<"TAK"<<endl;
        }

        else{
            for (int j = 0;j<startN;j++){
                arr[startN][j].flow = wins[j];
            }

            if(microbribery(startN,startN+1,startN,combats,money,B)){
                cout<<"TAK"<<endl;
            }
            else{
                cout<<"NIE"<<endl;
            }
        }

        for(int i=0;i<startN+2;i++){
            for (int j=0;j<startN+2;j++){
                arr[i][j].flow =0;
                arr[i][j].cost =0;
            }
        }
	}
}

