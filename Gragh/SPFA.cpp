#define arraysize 501
int maxData = 0x7fffffff;

typedef struct edge
{
   int to;
   int w;
}edge;

vector<edge> adjmap[arraysize]; //vectorʵ���ڽӱ� 

int d[arraysize];
bool final[arraysize];          //��¼�����Ƿ��ڶ����У�SPFA�㷨��������ж�� 
int cnt[arraysize];             //��¼��������д��� 

bool SPFA(int s)
{
     queue<int> myqueue;
     int i,j;
     for(i=0;i<n+1;++i)
     {
         d[i] = maxData;        //����Դ������������ľ�������Ϊ����� 
     }
     memset(final,0,sizeof(final));
     memset(cnt,0,sizeof(cnt));
     d[s]=0;                   //Դ��ľ���Ϊ0 
     final[s] = true;          
     cnt[s]++;                 //Դ�������д������� 
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
                      if(cnt[to]>=n)   //��һ������ӵĴ���>=nʱ��֤�������˸�����
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
    for(i=1;i<n+1;++i)       //�˴��ر�ע����ڽӱ���� 
        adjmap[i].clear();
    for(i=0;i<m;++i)         //˫�� 
    {
        cin>>s>>e>>w;
        temp.to = e;
        temp.w = w;
        adjmap[s].push_back(temp);
        temp.to = s;
        adjmap[e].push_back(temp);      
    }
}