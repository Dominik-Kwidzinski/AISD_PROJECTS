#include <iostream>
#include <cstdio>

using namespace std;

struct Node
{
    int key;
    Node **children;

    Node()
    {
        key = -1;
        children = nullptr;
    }

    void Childspace(int count)
    {
        if (!children)
        {
            children = new Node *[count];
            for (int i = 0; i < count; i++)
            {
                children[i] = nullptr;
            }
        }
    }

    bool leaf(int count)
    {
        if (!children)
        {
            return true;
        }
        for (int i = 0; i < count; ++i)
            if (children[i])
                return true;
        return false;
    }
};

void insert(Node *node, int val, bool isRoot, bool &exists, int n, int k)
{
    int oper = val;
    while (true)
    {
        if (node->key == val)
        {
            exists = true;
            return;
        }
        if (node->key == -1)
        {
            node->key = val;
            exists = false;
            return;
        }

        int mod, count;
        if (isRoot)
        {
            mod = oper % n;
            oper = oper / n;
            count = n;
        }
        else
        {
            mod = oper % k;
            oper = oper / k;
            count = k;
        }
        if (!node->children) {
            node->Childspace(count);
        }
        if (!node->children[mod])
        {
            node->children[mod] = new Node();
        }
        node = node->children[mod];
        isRoot = false;
    }
}

Node *find(Node *node, int val, bool isRoot, Node **path, int &pathLen, int n, int k, int Maxdepth = 1000)
{
    pathLen = 0;
    int oper = val;
    while (node && pathLen < Maxdepth)
    {
        path[pathLen++] = node;
        if (node->key == val)
        {
            return node;
        }
        int mod, count;
        if (isRoot)
        {
            mod = oper % n;
            oper = oper / n;
            count  = n;
        }
        else
        {
            mod = oper % k;
            oper = oper / k;
            count = k;
        }
        if (!node->children || mod < 0 || mod >= count || !node->children[mod])
        {
            return nullptr;
        }
        node = node->children[mod];
        isRoot = false;
    }
    return nullptr;
}

void deletekey(Node* &root, int val, int n, int k) {
    const int Maxdepth = 1000;
    Node* path[Maxdepth];
    int pathLen = 0;

    Node* node = find(root, val, true, path, pathLen, n, k, Maxdepth);

    if (!node) {
        printf("%d not exist\n", val);
        return;
    }

    int count = k;
    if (node == root) count = n;

    if (node == root && !root->leaf(n)) {
        root->key = -1;
        if (root->children) {
            delete[] root->children;
            root->children = nullptr;
        }
        return;
    }

    if (!node->leaf(k)) {
        if (pathLen > 1) {
            Node* parent = path[pathLen-2];
            for (int i = 0; i < count; ++i) {
                if (parent->children[i] == node) {
                    delete node;
                    parent->children[i] = nullptr;
                    break;
                }
            }
        }
        return;
    }

    Node* current = node;
    int depth = pathLen;

    while (true) {
        current->Childspace(k);
        bool found = false;

        for (int i = 0; i < k; ++i) {
            if (current->children[i]) {
                if (depth < Maxdepth) {
                    path[depth++] = current->children[i];
                }
                current = current->children[i];
                found = true;
                break;
            }
        }

        if (!found) break;
    }

    node->key = current->key;

    if (depth > 1) {
        Node* parent = path[depth-2];
        for (int i = 0; i < k; ++i) {
            if (parent->children[i] == current) {
                delete parent->children[i];
                parent->children[i] = nullptr;
                break;
            }
        }
    }
}

bool lookup(Node *node, int val, bool isRoot, int n, int k)
{
    int oper = val;
    while (node)
    {
        if (node->key == val)
        {
            return true;
        }
        int mod, count;
        if (isRoot)
        {
            mod = oper % n;
            oper = oper / n;
            count = n;
        }
        else
        {
            mod = oper % k;
            oper = oper / k;
            count = k;
        }
        if (!node->children || mod < 0 || mod >= count)
        {
            return false;
        }
        node = node->children[mod];
        isRoot = false;
    }
    return false;
}



void Print(Node *node, bool isRoot, int n, int k)
{
    if (!node)
        return;
    if (node->key != -1)
    {
        printf("%d ", node->key);
    }

    int limit;
    if (isRoot)
    {
        limit = n;
    }
    else
    {
        limit = k;
    }

    if (node->children)
    {
        for (int i = 0; i < limit; i++)
        {
            Print(node->children[i], false, n, k);
        }
    }
}

int main()
{
    int testcases;
    scanf("%d", &testcases);
    int min, max;
    scanf("%d %d", &min, &max);
    int n, k;
    scanf("%d %d", &n, &k);

    Node *root = new Node();
    int val;
    bool exists;

    while (testcases--)
    {
        char command;
        scanf(" %c", &command);
        switch (command)
        {
        case 'I':
            scanf("%d", &val);
            exists = false;
            insert(root, val, true, exists, n, k);
            if (exists)
            {
                printf("%d exist\n", val);
            }
            break;
        case 'L':
            scanf("%d", &val);
            if (lookup(root, val, true, n, k))
            {
                printf("%d exist\n", val);
            }
            else
            {
                printf("%d not exist\n", val);
            }
            break;
        case 'D':
            scanf("%d", &val);
            deletekey(root, val, n, k);
            break;
        case 'P':
            Print(root, true, n, k);
            printf("\n");
            break;
        }
    }

    return 0;
}
