#include <iostream>
#include <cstdio>

using namespace std;

struct Escalator{
    int DH, DW, TT, WT;
    Escalator *next = nullptr;
};

struct Pos{
  int val = 0;
  int cost = 999999999;
  bool visited = false;
  Escalator *winda = nullptr;
};

struct Node{
  int priority = 999999999;
  int H, W;
};

struct Pqueue {
    Node* tab;
    int size;
    Pqueue(int n) {
        tab = new Node[n];
        size = 0;
    }

};

void insert(Pqueue* kolejka, Node n){
    kolejka->size += 1;
    int i = kolejka->size;
    while (i>1 && kolejka->tab[i/2-1].priority > n.priority) {
        kolejka->tab[i-1] = kolejka->tab[i/2-1];
        i = i/2;
    }
    kolejka->tab[i-1] = n;
}

void heapify(Pqueue *kolejka){
    bool h = true;
    int i = 0;
    while(h && i*2+2 < kolejka->size){
        int lower = i*2+1;
        if(kolejka->tab[lower].priority > kolejka->tab[lower+1].priority){
            lower += 1;
        }

        if(kolejka->tab[i].priority > kolejka->tab[lower].priority){
            Node temp = kolejka->tab[i];
            kolejka->tab[i] = kolejka->tab[lower];
            kolejka->tab[lower] = temp;
            i = lower;
        } else h = false;
    }
}

Node pop(Pqueue* kolejka){
    Node max = kolejka->tab[0];
    kolejka->tab[0] = kolejka->tab[kolejka->size-1];
    kolejka->size--;
    heapify(kolejka);
    return max;
}


void Esc(Pos* pozycja){
    Escalator* temp = new Escalator;
    cin >> temp->DW >> temp->DH >> temp->TT >> temp->WT;

    temp->next = pozycja->winda;
    pozycja->winda = temp;
}


int main()
{
    //input
    int  W, H, StartW, StartH, EndW, EndH, EscCount;
    cin>>W>>H>>StartW>>StartH>>EndW>>EndH>>EscCount;

    //alokacja mapy
    Pos** map = new Pos*[H];
    for (int i = 0; i < H; i++){
        map[i] = new Pos[W];
    }

    //ustawienia miejsca startu
    map[StartH][StartW].cost = 0;

    while(EscCount){
        int SH, SW;
        cin >> SW>>SH;
        Esc(&map[SH][SW]);
        EscCount--;
    }

    //input mapy
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            int v;
            scanf("%d", &v);
            map[i][j].val = v;
        }
    }

    Pqueue kolejka((W*H)+EscCount);
    Node Start;
    Start.priority = 0;
    Start.H = StartH;
    Start.W = StartW;
    kolejka.tab[0] = Start;
    kolejka.size = 1;


    bool run = true;
    while(run){
        Node lowest = pop(&kolejka);
        int LH = lowest.H;
        int LW = lowest.W;
        //cout<<LW<<" - "<<LH<<"\n";
        if(!map[LH][LW].visited){

        //up
        if(LH != 0){
            if(!map[LH-1][LW].visited){
                int nc = map[LH][LW].cost+1;
                if(map[LH-1][LW].val > map[LH][LW].val){
                    nc += map[LH-1][LW].val - map[LH][LW].val;
                }
                if(map[LH-1][LW].cost > nc){
                    map[LH-1][LW].cost = nc;
                    Node North;
                    North.priority = nc;
                    North.H = LH-1;
                    North.W = LW;
                    insert(&kolejka, North);
                }
            }
        }
        //down
        if(LH != H-1){
            if(!map[LH+1][LW].visited){
                int nc = map[LH][LW].cost+1;
                if(map[LH+1][LW].val > map[LH][LW].val){
                    nc += map[LH+1][LW].val - map[LH][LW].val;
                }
                if(map[LH+1][LW].cost > nc){
                    map[LH+1][LW].cost = nc;
                    Node South;
                    South.priority = nc;
                    South.H = LH+1;
                    South.W = LW;
                    insert(&kolejka, South);
                }
            }
        }
        //left
        if(LW != 0){
            if(!map[LH][LW-1].visited){
                int nc = map[LH][LW].cost+1;
                if(map[LH][LW-1].val > map[LH][LW].val){
                    nc += map[LH][LW-1].val - map[LH][LW].val;
                }
                if(map[LH][LW-1].cost > nc){
                    map[LH][LW-1].cost = nc;
                    Node West;
                    West.priority = nc;
                    West.H = LH;
                    West.W = LW-1;
                    insert(&kolejka, West);
                }
            }
        }
        //right
        if(LW != W-1){
            if(!map[LH][LW+1].visited){
                int nc = map[LH][LW].cost+1;
                if(map[LH][LW+1].val > map[LH][LW].val){
                    nc += map[LH][LW+1].val - map[LH][LW].val;
                }
                if(map[LH][LW+1].cost > nc){
                    map[LH][LW+1].cost = nc;
                    Node East;
                    East.priority = nc;
                    East.H = LH;
                    East.W = LW+1;
                    insert(&kolejka, East);
                }
            }
        }

        Escalator *kolej = map[LH][LW].winda;
        while(kolej != nullptr){
            int KDH = kolej->DH;
            int KDW = kolej->DW;
            if(!map[kolej->DH][kolej->DW].visited){
                int np = map[LH][LW].cost;
                if(np%kolej->WT == 0) np = kolej->TT + np;
                else np = kolej->WT - np%kolej->WT + kolej->TT + np;
                Node K;
                K.priority = np;
                K.H = kolej->DH;
                K.W = kolej->DW;
                if (map[kolej->DH][kolej->DW].cost > np) {
                    map[kolej->DH][kolej->DW].cost = np;
                }
                insert(&kolejka, K);
            }
            kolej = kolej->next;
        }

        map[LH][LW].visited = true;

        if(map[EndH][EndW].visited){
            cout<<map[EndH][EndW].cost;
            run = false;
        }
        }
    }

    delete[] map;
    delete[] kolejka.tab;


    return 0;
}
