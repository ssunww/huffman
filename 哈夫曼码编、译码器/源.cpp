#include<stdio.h>
#define Maxleaf 30
#define Maxnode 1000
#define Max 100000
#define Maxsize 100
typedef struct      
{
    char ch;          
    float weight;    
    int lchild, rchild, parent;   
}hufmtree;
typedef struct
{
    char bits[Maxsize];        
    int start;                 
    char ch;                   
}codetype;
void huffman(hufmtree tree[], int n)   
{
    int i, j, p1, p2;
    float small1, small2, f;
    char c;
    int m = 2 * n - 1;           
    for (i = 0; i < m; i++)        
    {
        tree[i].parent = 0;
        tree[i].lchild = -1;
        tree[i].rchild = -1;
        tree[i].weight = 0.0;
    }
    for (i = 0; i < n; i++)              
    {
        printf("��%d��Ԫ�صĽ��:", i + 1);
        scanf("%c", &c);
        getchar();
        printf("����ýڵ��Ȩֵ��");
        scanf("%f", &f);
        getchar();
        tree[i].ch = c;
        tree[i].weight = f;
    }
    for (i = n; i < m; i++)         
    {
        p1 = 0; p2 = 0;
        small1 = Max; small2 = Max;
        for (j = 0; j < i; j++)
            if (tree[j].parent == 0)         
                if (tree[j].weight < small1)        
                {
                    small2 = small1;
                    small1 = tree[j].weight;
                    p2 = p1;
                    p1 = j;
                }
                else if (tree[j].weight < small2)        
                {
                    small2 = tree[j].weight;
                    p2 = j;
                }
        tree[p1].parent = i;
        tree[p2].parent = i;
        tree[i].lchild = p1;
        tree[i].rchild = p2;
        tree[i].weight = tree[p1].weight + tree[p2].weight;
    }
}
void huffmancode(codetype code[], hufmtree tree[], int n)   
{
    int i, c, p;
    codetype cd;           
    for (i = 0; i < n; i++)         
    {
        cd.start = n;            
        cd.ch = tree[i].ch;        
        c = i;
        p = tree[i].parent;
        while (p != 0)             
        {
            cd.start--;
            if (tree[p].lchild == c)     
                cd.bits[cd.start] = '0';     
            else
                cd.bits[cd.start] = '1';     
            c = p;
            p = tree[p].parent;
        }
        code[i] = cd;                     
    }
}
void decode(hufmtree tree[], int m)     
{
    int i, j = 0, k = 0;
    char b[Maxsize];
    char endflag = '#';
    i = m - 1;
    getchar();
    gets_s(b);                                                  
    printf("������������룺\n");
    while (b[j] != '#')
    {
        if (b[j] == '0')                                        
            i = tree[i].lchild;                                 
        else
        {
            if (b[j] == '1')

                i = tree[i].rchild;   
            else
                printf("ERROR\n");
        }
        if (tree[i].lchild == -1)        
        {
            printf("%c", tree[i].ch);    
            i = m - 1;                        
        }
        j++;
    }
    printf("\n");
    if (tree[i].parent != 0)
        printf("\nERROR\n");
}
void Menu()
{
    printf("������������������������������������������������\n");
    printf("*********����������/������*********\n");
    printf("*         1.������������;         *\n");
    printf("*         2.���й���������;       *\n");
    printf("*         3.���й���������;        *\n");
    printf("*         4.�˳�;                 *\n");
    printf("������������������������������������������������\n");
}
int main()
{
    int i, j, n, m;
    int choose;
    hufmtree tree[Maxnode];
    codetype code[Maxleaf];
    Menu();
    while (1)
    {
        printf("\n������Ҫ���еĹ��ܣ�");
        scanf("%d", &choose);
        switch (choose)
        {
        case 1:
            printf("������Ԫ�ظ�����");
            scanf("%d", &n);
            getchar();
            huffman(tree, n);                               
            printf("�ɹ���������������\n");
            break;
        case 2:
            printf("��������������룺\n");
            huffmancode(code, tree, n);           
            for (i = 0; i < n; i++)                           
            {
                printf("%c:", code[i].ch);
                for (j = code[i].start; j < n; j++)
                    printf("%c", code[i].bits[j]);
                printf("\n");
            }
            break;
        case 3:
            m = 2 * n - 1;
            printf("��������룬��#Ϊ������־��\n");
            decode(tree, m);                             
            break;
        case 4:
            return 0;
        }
    }
    return 0;
}