#include <iostream>
#include <fstream>

using namespace std;

int count = 0;  //счетчик элементов списка

struct Node{
    int info;
    struct Node* next;
};
Node* BeginList;
Node* list;

struct Node* Init();    //инициализация
struct Node* Add(Node* &, int); //добавление элемента
void Dispose();        //удаление всего списка
int GetNext(Node*);     //получение следующего элемента
void PrintList();  //вывод списка
void LastToFirst(); //перенос последнего элемента на первое место
void Remove(int);

int main()
{
    ifstream fin;
    fin.open("E:/3 term/SIAOD/lab4/fin.txt");
    if(!fin.is_open())
        cout << "Error! File can't be opened." << endl << endl;
    else
    {
        int a;
        list = NULL;
        Init();
        while(!fin.eof())
        {
            fin >> a;
            if (a == ' ')
                fin >> a;
            Add(list , a);
        }
        PrintList();
        LastToFirst();
        PrintList();
    }
    int x;
    cout << "Enter element to be deleted: ";
    cin >> x;
    Remove(x);
    PrintList();
    Dispose();
    PrintList();
    getchar();
    return 0;
}

struct Node* Init()
{
    list = NULL;
    BeginList = NULL;
    return list;
}

struct Node* Add(Node* &p, int i)
{
    Node* temp = new Node;
    if (temp != NULL)
    {
        temp->info = i;
        if (p == NULL)
        {
            temp->next = NULL;
            p = temp;
        }
        else
        {
            temp->next = p->next;
            p->next = temp;
        }
    }
    else
        cout << "Memory error" << endl;

    if (count == 0)
        BeginList = p;
    list = temp;
    count++;
    return list;
}


void Dispose()
{
    Node *nxt, *tmp;
    tmp = BeginList;
    nxt = BeginList;
    for (int i = count; i != 0; i--)
    {
        nxt = nxt->next;
        free(tmp);
        tmp = nxt;
        count--;
    }
    BeginList = NULL;
}

void PrintList()
{
    if(BeginList == NULL)
        cout << "error!!!" << endl;
    else
    {
        Node* p;
        p = BeginList;
        cout << "List: " << endl;
        int i = count;
        while (1)
        {
            if (p->next == NULL)
            {
                cout << p->info;
                break;
            }
            cout << p->info <<" "; // " p.next.info = " << p->next->info << endl;
            p = p->next;
            i--;
        }
        cout << endl;
    }
}

void LastToFirst()
{
    Node *p, *temp;
    p = BeginList;
    do
    {
        p = p->next;
    } while (p->next->next!=NULL);
    temp = p->next;
    p->next = nullptr;
    temp->next = BeginList;
    BeginList = temp;
}

bool IsEmpty()
{
    return (BeginList == NULL);
}

void Remove(int val)
{
    if (IsEmpty())
        return;
    Node* p = BeginList;
    Node* temp;

    for (int i = 0; i < count-1; i++)
    {
        if (p->next->info == val)
        {
            temp = p->next;
            p->next=temp->next;
            return;
        }
        else
            p = p->next;
    }
}

