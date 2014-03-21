/*
�ֵ������ֳƵ��ʲ�������Trie������һ�����νṹ������Ӧ��������ͳ�ƣ�����ͱ���������ַ��������Ծ�������������ϵͳ�����ı���Ƶͳ�ơ������ŵ��ǣ������ַ����Ĺ���ǰ׺����Լ�洢�ռ䣬����޶ȵļ�����ν���ַ����Ƚϣ���ѯЧ�ʱȹ�ϣ��ߡ�

�ֵ�����Ӧ�ã�

�ַ����Ŀ��ټ���
��ϣ
�����ǰ׺
*/



//Trie��ģ��   by AbandonZHANG


int words_num;

struct Trie_node
{
    int Ch_Count;   //ͳ�Ƶ��ʸ��������Ϊ0��ʾû�иô���
    int hash;       //����hash��ı�ʶ��
    Trie_node *next[26];//ָ�����������ָ��,�±�0-25����26�ַ�,��������ָĳ�10������
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
    void insert(char *word);                 //�����µ���
    int search(char * word);                 //���ص��ʸ��������Ϊ0��ʾ�����ڸõ���
private:
    Trie_node* root;
};

Trie::Trie()
{
    root = new Trie_node();
}

void Trie::insert(char * word)			//��ʱ����Բ����ѯһ�����
{
    Trie_node *p = root;
    int len=strlen(word);
    if(len==0)return ;
    for (int i=0;i<len;i++)
    {
        if(p->next[word[i]-'a'] == NULL)      //��������ڵĻ������Ǿͽ���һ���µĽڵ�
        {
            Trie_node *tmp = new Trie_node();
            p->next[word[i]-'a'] = tmp;
            p = p->next[word[i]-'a'];         //ÿ����һ�����൱����һ���´�������ָ��Ҫ�����ƶ�
        }
        else                                //�������ڵ�֮ǰ���Ѿ�������������ֻ��Ҫ��ͳ�ƴ�������1
            p=p->next[word[i]-'a'];
        //p->Ch_Count++;                      //������������ǰ׺���ֵĴ��������ֻ���������ʳ��ִ������ú�һ��
    }
    p->Ch_Count++;                        //���������ʵĳ��ִ���
    /*
    if (p->hash<0)
        p->hash=words_num++;
    */
    return ;
}

int Trie::search(char * word)                //���ص��ʸ��������Ϊ0��ʾ�����ڸõ���
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
    //return p->hash;                       //���ص��ʵ�hash��ʶ�������Ϊ0��ʾ�����ڸõ���
}

int main() 		//�򵥲���
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
    if(t.search("aba"))                     //��ǰ׺ͳ�Ʋ�ͳ��
        printf("aba true\n");
    return 0;
}