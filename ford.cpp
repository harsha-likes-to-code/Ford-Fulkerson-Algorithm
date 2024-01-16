#include<iostream>
#include<queue>
using namespace std;
#define INF 9999
#define V 6
int bfs(int rgraph[V][V],int s,int t,int parent[])
{
    int visited[V];
    for(int i=0;i<V;i++)
    {
        visited[i]=0;
    }
    queue<int> q;
    q.push(s);
    visited[s]=1;
    parent[s]=-1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int v=0;v<V;v++)
        {
            if(visited[v]==0 && rgraph[u][v]>0)
            {
                if(v==t)
                {
                    parent[v]=u;
                    return 1;
                }
                q.push(v);
                parent[v]=u;
                visited[v]=1;
            }
        }
    }
    return 0;
}

int ford_fulkerson(int graph[V][V],int s,int t)
{
    int u,v;
    int rgraph[V][V];
    for(u=0;u<V;u++)
    {
        for(v=0;v<V;v++)
        {
            rgraph[u][v]=graph[u][v];
        }
    }
    int parent[V];
    int max_flow=0;
    while(bfs(rgraph,s,t,parent)==1)
    {
        int path_flow=INF;
        for(v=t;v!=s;v=parent[v])
        {
            u = parent[v];
            path_flow=min(path_flow,rgraph[u][v]);
        }
        for(v=t;v!=s;v=parent[v])
        {
            u=parent[v];
            rgraph[u][v]-=path_flow;
            rgraph[v][u]+=path_flow;
        }
         max_flow=max_flow+path_flow;
    }
    return max_flow;

}
int main()
{
       int graph[V][V] = {{0,16,13,0,0,0},{0,0,10,12,0,0},{0,4,0,0,14,0},
                       {0,0,9,0,0,20},{0,0,0,7,0,4},{0,0,0,0,0,0}};
                       cout<<ford_fulkerson(graph,0,5);
                       return 0;
}
