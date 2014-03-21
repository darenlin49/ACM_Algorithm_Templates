/*
字典树，又称单词查找树，Trie树，是一种树形结构，典型应用是用于统计，排序和保存大量的字符串，所以经常被搜索引擎系统用于文本词频统计。它的优点是：利用字符串的公共前缀来节约存储空间，最大限度的减少无谓的字符串比较，查询效率比哈希表高。

字典树的应用：

字符串的快速检索
哈希
最长公共前缀
*/



//Trie树模板   by AbandonZHANG


int words_num;

struct Trie_node
{
    int Ch_Count;   //统计单词个数，如果为0表示没有该串。
    int hash;       //单词hash后的标识数
    Trie_node *next[26];//指向各个子树的指针,下标0-25代表26字符,如果是数字改成10就行了
    Trie_node()
    {
        Ch_Count=0;
        hash=-1;
        memset(next,NULL,sizeof(next));
    }
};

class Trie
{
public:
    Trie();
    void insert(char *word);                 //插入新单词
    int search(char * word);                 //返回单词个数，如果为0表示不存在该单词
private:
    Trie_node* root;
};

Trie::Trie()
{
    root = new Trie_node();
}

void Trie::insert(char * word)			//有时候可以插入查询一块儿做
{
    Trie_node *p = root;
    int len=strlen(word);
    if(len==0)return ;
    for (int i=0;i<len;i++)
    {
        if(p->next[word[i]-'a'] == NULL)      //如果不存在的话，我们就建立一个新的节点
        {
            Trie_node *tmp = new Trie_node();
            p->next[word[i]-'a'] = tmp;
            p = p->next[word[i]-'a'];         //每插入一步，相当于有一个新串经过，指针要向下移动
        }
        else                                //如果这个节点之前就已经存在呃，我们只需要把统计次数加上1
            p=p->next[word[i]-'a'];
        //p->Ch_Count++;                      //这里是求所有前缀出现的次数，如果只求整个单词出现次数则用后一个
    }
    p->Ch_Count++;                        //求整个单词的出现次数
    /*
    if (p->hash<0)
        p->hash=words_num++;
    */
    return ;
}

int Trie::search(char * word)                //返回单词个数，如果为0表示不存在该单词
{
    Trie_node *p = root;
    int len=strlen(word);
    if (len==0) return 0;
    for (int i=0;i<len;i++)
    {
        if (p->next[word[i]-'a']!=NULL)
            p=p->next[word[i]-'a'];
        else
            return 0;
    }
    return p->Ch_Count;
    //return p->hash;                       //返回单词的hash标识数，如果为0表示不存在该单词
}

int main() 		//简单测试
{
    Trie t;
    t.insert("a");
    t.insert("abandon");
    string c= "abandoned";
    t.insert(c);
    t.insert("abashed");
    if(t.search("abashed"))
        printf("abashed true\n");
    if(t.search("a"))
        printf("a true\n");
    if(t.search("abandoned"))
        printf("abandoned true\n");
    if(t.search("aba"))                     //看前缀统计不统计
        printf("aba true\n");
    return 0;
}