#define arraysize 501
int maxData = 0x7fffffff;

typedef struct edge
{
   int to;
   int w;
}edge;

vector<edge> adjmap[arraysize]; //vector实现邻接表 

int d[arraysize];
bool final[arraysize];          //记录顶点是否在队列中，SPFA算法可以入队列多次 
int cnt[arraysize];             //记录顶点入队列次数 

bool SPFA(int s)
{
     queue<int> myqueue;
     int i,j;
     for(i=0;i<n+1;++i)
     {
         d[i] = maxData;        //将除源点以外的其余点的距离设置为无穷大 
     }
     memset(final,0,sizeof(final));
     memset(cnt,0,sizeof(cnt));
     d[s]=0;                   //源点的距离为0 
     final[s] = true;          
     cnt[s]++;                 //源点的入队列次数增加 
     myqueue.push(s);
     int topint;
     while(!myqueue.empty())
     {
         topint = myqueue.front();
		 myqueue.pop();
         final[topint] = false;
         for(i=0;i<adjmap[topint].size();++i)
         {
             int to = adjmap[topint][i].to;
             if(d[topint]<maxData && d[to]>d[topint]+ adjmap[topint][i].w)
             {                                 
                  d[to] = d[topint]+ adjmap[topint][i].w;
                  if(!final[to])
                  {
                      final[to] = true;
                      cnt[to]++;
                      if(cnt[to]>=n)   //当一个点入队的次数>=n时就证明出现了负环。
                         return true;
                      myqueue.push(to);
                  }                  
             }
         }
     }
     return false;
}

int main()
{
    for(i=1;i<n+1;++i)       //此处特别注意对邻接表清空 
        adjmap[i].clear();
    for(i=0;i<m;++i)         //双向 
    {
        cin>>s>>e>>w;
        temp.to = e;
        temp.w = w;
        adjmap[s].push_back(temp);
        temp.to = s;
        adjmap[e].push_back(temp);      
    }
}