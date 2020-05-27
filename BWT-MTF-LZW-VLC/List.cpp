#include <iostream>

class ListNode
{
public:
    unsigned char data;
    ListNode *next, *prev;
    ListNode(unsigned char v, ListNode *p, ListNode *n) : data(v), prev(p), next(n){};
    ListNode()
    {
        data = 0;
        prev = next = NULL;
    }
};

class List
{
public:
    ListNode *tail, *head;
    ListNode **list;
    int SZ;
    List()
    {
        tail = head = NULL;
        SZ = 0;
        list = new ListNode *[256];
        for (int i = 0; i < 256; i++)
            list[i] = NULL;
    };
    ~List()
    {
        for (int i = 0; i < 256; i++)
            if (list[i] != NULL)
                delete list[i];
        // if (list != NULL)
        //     delete list;
        // if (tail != NULL)
        //     delete tail;
        // if (head != NULL)
        //     delete head;
    }
    int size() { return SZ; };
    void push_back(unsigned char v)
    {
        if (!tail)
        {
            tail = head = new ListNode(v, NULL, NULL);
            SZ = 1;
            list[v] = tail;
        }
        else
        {
            tail->next = new ListNode(v, tail, NULL);
            SZ++;
            tail = tail->next;
            list[v] = tail;
        }
    };

    void swap_to_front(unsigned char v)
    {
        if (head == list[v])
            return;
        if (tail == list[v])
        {
            list[v]->prev->next = NULL;
            tail = list[v]->prev;
            list[v]->prev = NULL;
            list[v]->next = head;
            head->prev = list[v];
            head = list[v];
        }
        else
        {
            ListNode *node = list[v];
            if (node->prev->next != node)
            {
                std::cout << '\n';
            }
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = NULL;
            node->next = head;
            head->prev = node;
            head = node;
        }
    };
};