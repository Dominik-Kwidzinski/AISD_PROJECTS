#include <iostream>

using namespace std;

struct Number
{
    char v;
    Number *next;
};

struct Stos
{
    Number *list;
    Stos *down;
};

void printlist(Number list){
    cout<<list.v;
    if (list.next != nullptr) printlist(*list.next);
}

void printstos(Stos top, int i){
    if(top.down != nullptr) printstos(*top.down, i+1);
    cout<<i<<": ";
    if (top.list != nullptr) printlist(*top.list);
    cout<<endl;
}

//działa, nawet dobrze
Number* copy(Number *org){
    if (org == nullptr) {
        return nullptr;
    }
    Number *newlist = new Number;
    newlist->v = org->v;
    //newlist->next = nullptr;
    newlist->next = copy(org->next);
    return newlist;
}


Stos* find(Stos *top, int v, int i){
    if(v == i) return top;
    else return find(top->down, v, i+1);
}

int readV(Number *head, int i){ 
    if (head->next != nullptr) return (int(head->v)-48) * i + readV(head->next, i*10);
    else return (int(head->v)-48) * i;
}


void nega(Number *head) {
    if(head->next->next == nullptr){
        if(head->next->v == '-'){
            head->next = nullptr;
        } else {
            Number *newnum = new Number;
            newnum->v = '-';
            newnum->next = nullptr;
            head->next->next = newnum;
        }
    } else {
        nega(head->next);
    }
}

void betternega(Stos *top) {
    if(top->list == nullptr){
        Number *newnum = new Number;
        newnum->v = '-';
        newnum->next = nullptr;
        top->list = newnum;
    }
    else if(top->list->next == nullptr){
        if(top->list->v == '-'){
            top->list = nullptr;
        }
        else {Number *newnum = new Number;
        newnum->v = '-';
        newnum->next = nullptr;
        top->list->next = newnum;
        }
    } else{
        nega(top->list);
    }
}

void abs(Number *head){
    if(head->next->next == nullptr){
        if(head->next->v == '-'){
            head->next->v = ' ';
            head->next = nullptr;
            return;
        } else return;
    } else {
        abs(head->next);
    }
}

void merge(Number *head, Number *list){
    if (head->next == nullptr){
        head->next = list;
    } else{
        merge(head->next, list);
    }
}

int isnegative(Number *head){
    if(head == nullptr) return 0;
    if(head->next != nullptr){
        return isnegative(head->next);
    } else
    if(head->v == '-'){
        return 1;
    }else return 0;
    return 0;
}

int usuwaniezer(Number *head){
    if(head->next->next != nullptr){
        if(usuwaniezer(head->next)){
            if(head->next->v == '0'){
                head->next = nullptr;
                return 1;
            }else return 0;
        } else return 0;
    }
    if(head->next->v == '0'){
        head->next = nullptr;
        return 1;
    }else return 0;
}

int comparelen(Number *first, Number *second){
    if(first->next != nullptr && second->next != nullptr){
        return comparelen(first->next, second->next);
    }
    else if(first->next != nullptr && second->next == nullptr){
        return 1;
    }
    else if(first->next == nullptr && second->next != nullptr){
        return 2;
    }
    else return 0;
}

int compare_nbyn(Number *first, Number *second){
    if(first->next != nullptr) {
        int res = compare_nbyn(first->next, second->next);
        if (res != 2){
        return res;
        }
    }  
        if( first->v > second->v) return 1;
        if( first->v == second->v) return 2;
        if( second->v > first->v) return 0;
    return 0;
}

int compare_nbynnega(Number *first, Number *second){
    if(first->next != nullptr) {
        int res = compare_nbynnega(first->next, second->next);
        if (res != 2){
        return res;
        }
    }  
        if( first->v > second->v) return 0;
        if( first->v == second->v) return 2;
        if( second->v > first->v) return 1;
    return 0;
}

int compare_nbyn2(Number *first, Number *second){
    if(first->v > second->v) return 0;
    if(second->v > first->v) return 0;
    if(first->next != nullptr && second->next != nullptr)
    {return compare_nbyn2(first->next, second->next);}
    else 
    return 1;
}

int compare(Number *first, Number *second){
    int negf = isnegative(first);
    int negs = isnegative(second);
    if(negf != negs){
        if(negf == 1) {
            return 0;
        } else return 1;
    }
    int res = 0;

    switch ( comparelen(first, second))
    {
    case 0:
        if(negf == 0) res = compare_nbyn(first, second);
        if(negf == 1) res = compare_nbynnega(first, second);
        if(res == 2){ return 0;
        } else{
            return res;
        }
        break;
    case 1:
        if(negf == 0) return 1;
        if(negf == 1) return 0;
        break;
    case 2:
        if(negf == 0) return 0;
        if(negf == 1) return 1;
        break;
    }
    return 0;
}

void addnumber(Number *head, int value){
    if(value > 0) {
        Number *newnum = new Number;
        newnum->next = nullptr;
        newnum->v = value%10 + 48; value = value/10;
        head->next = newnum;
        addnumber(head->next, value);
    }
}

int compare2(Number *first, Number *second){
    int negf = isnegative(first);
    int negs = isnegative(second);
    if(negf != negs){
         return 0;
    }

    switch ( comparelen(first, second))
    {
    case 0:
        return compare_nbyn2(first, second);
        break;
    case 1:
        return 0;
        break;
    case 2:
        return 0;
        break;
    }
    return 0;

}


void sumingac(Number *first, int carry){
    int sum = first->v + carry - 48;
    first->v = sum%10 + 48;
    if(first->next != nullptr){
        sumingac(first->next, sum/10);
    } else if(sum/10 == 1){
        Number *newnum = new Number;
        first->next = newnum;
        newnum->v = '1';
        newnum->next = nullptr;
    }
}

void sumingabc(Number *first, Number *second, int carry){
    int sum = first->v + second->v + carry - 96;
    first->v = sum%10 + 48;
    if(first->next != nullptr && second->next != nullptr){
        sumingabc(first->next, second->next, sum/10);
    } else if(first->next != nullptr){
        sumingac(first->next, sum/10);
    } else if(sum/10 == 1){
        Number *newnum = new Number;
        first->next = newnum;
        newnum->v = '1';
        newnum->next = nullptr;
    }


}

void diffingac(Number *first, int carry){
    int res = first->v + carry - 48;
    int ncar = 0;
    if(res < 0){
        res = res + 10;
        ncar = -1;
    }
    first->v = res%10 + 48;
    if(first->next != nullptr){
        diffingac(first->next, ncar);
    } else if(ncar == -1){
        Number *newnum = new Number;
        first->next = newnum;
        newnum->v = '-';
        newnum->next = nullptr;
    }
}

void diffingabc(Number *first, Number *second, int carry){
    int res = first->v - second->v + carry;
    int ncar = 0;
    if(res < 0){
        res = res + 10;
        ncar = -1;
    }
    first->v = res%10 + 48;
    if(first->next != nullptr && second->next != nullptr){
        diffingabc(first->next, second->next, ncar);
    }else if(first->next != nullptr){
        diffingac(first->next, ncar);
    }else if(ncar == -1){
        Number *newnum = new Number;
        first->next = newnum;
        newnum->v = '-';
        newnum->next = nullptr;
    }
}

void usuwaniezer(Stos *top){
    if(isnegative(top->list)){
        betternega(top);
        if(top->list->next == nullptr){
            if(top->list->v == '0'){
                betternega(top);
            }
        } else {
        usuwaniezer(top->list);
        if(top->list->next == nullptr){
            if(top->list->v == '0'){
                betternega(top);
            }
        }

        }
        betternega(top);
    } else {
        if(top->list != nullptr){
        if(top->list->next == nullptr){
            if(top->list->v == '0'){
            }
        } else {
        usuwaniezer(top->list);

        }
    }
    }
}



int main(){
    char inp;
    char pro[20000];
    int proread = 1;
    int propos = 0;
    //WCZYTANIE WEJSCIA

    while(proread == 1){
        scanf("%c", &inp);
        if(inp == '\n'){
            proread = 0;
        } else{
            pro[propos] = inp;
            propos++;
        }
    }


    int prorunpos = 0;

    prorunpos++;
    Stos *top = new Stos;
    top->down = nullptr;
    top->list = nullptr;

    if(pro[0] == '~'){
        Number *newnum = new Number;
        top->list = newnum;
        top->list->v = '0';
        top->list->next = nullptr;
    }


    //MAIN LOOOOOP
    while(prorunpos < propos)
    {
        char com = pro[prorunpos++];

        if(com == '\''){
            Stos *newtop = new Stos;
            newtop->list = nullptr;
            newtop->down = top;
            top = newtop;
        } else if(com == '.'){
                Number *newnum = new Number;
                cin.get(newnum->v);
                newnum->next = top->list;
                top->list = newnum;
        } else if(com =='&'){
            if(top == nullptr){}
            else printstos(*top, 0);

        } else if(com == ','){
            top = top->down;//działa 
        } else if(com == ':'){
            Stos *newtop = new Stos;
            newtop->list = nullptr;
            newtop->down = top;
            top = newtop;

            top->list = copy(top->down->list);
        } else if(com == ';'){
            Number *temp = top->list;
            top->list = top->down->list;
            top->down->list = temp;
        } else if(com == '@'){

            int value = readV(top->list, 1); //czytaj v

            top = top->down; //usuń top

            Stos *newtop = new Stos; //new stos
            newtop->list = nullptr;
            newtop->down = top;
            top = newtop;

            Stos *orig = find(top, value, -1);

            top->list = copy(orig->list);
            orig = nullptr;
        } else if(com == '>'){
            cout<<top->list->v;
            top = top->down; //działa,  działa
        } else if(com =='['){
            int value = top->list->v;
            top->list->v = value%10 + 48; value = value/10;
            top->list->next = nullptr;
            addnumber(top->list, value);
        } else if(com ==']'){
            int value = readV(top->list, 1);
            top->list->v = value;
            top->list->next = nullptr;
        } else if(com =='#'){
            merge(top->down->list, top->list);
            top = top->down;
        } else if(com =='$'){
            char temp = top->list->v;
            top->list = top->list->next;
            Number *newnum = new Number;
            newnum->v = temp;
            newnum->next = nullptr;
                Stos *newtop = new Stos; //new stos
                newtop->list = newnum;
                newtop->down = top;
                top = newtop;
        } else if(com =='-'){
           betternega(top);
        }else if(com =='^'){
            if(top->list == nullptr){}
            else if(top->list->next == nullptr){
                if(top->list->v == '-'){
                    top->list = nullptr;
                }
            } else{
                abs(top->list);
            }
        }else if(com == '<') {
            //usuwanie zer stos n
            usuwaniezer(top);

            //usuwanie zer stos n-1
            usuwaniezer(top->down);

            //porownanie <
            int result = compare(top->list, top->down->list);
            top = top->down;
            top->list->next = nullptr;
            top->list->v = result + 48;

            
        }else if(com == '='){
            //usuwanie zer stos n
            
            if(top->list == nullptr)
            {
                Number* newnum = new Number;
                top->list = newnum;
                newnum->next = nullptr;
            }
            usuwaniezer(top);

            //usuwanie zer stos n-1

            if(top->down->list == nullptr)
            {
                Number* newnum = new Number;
                top->down->list = newnum;
                newnum->next = nullptr;
            }
            
            usuwaniezer(top->down);

            //porownie =
            int result = compare2(top->list, top->down->list);
            top = top->down;
            top->list->next = nullptr;
            top->list->v = result + 48;

        }else if(com == '!'){
            if(top->list == nullptr){
                Number *newnum = new Number;
                newnum->next = nullptr;
                newnum->v = '1';
                top->list = newnum;
            } else if(top->list->next == nullptr && top->list->v == '0'){
                top->list->v = '1';
            } else {
                top->list->next = nullptr;
                top->list->v = '0';
            } 

        }else if(com == '~'){
            Stos *newstos = new Stos;
            newstos->down = top;
            newstos->list = nullptr;
            top = newstos;
            int value = prorunpos-1;
            Number *newnum = new Number;
            newnum->v = value%10+48; value = value/10;
            newnum->next = nullptr;
            top->list = newnum;
            addnumber(top->list, value);
        }else if(com == '?'){
            int booooool = 0;
            if(top->down->list == nullptr){
                booooool = 0;
            } else if(top->down->list->next == nullptr && top->down->list->v == '0'){
                booooool = 0;
            } else {
                booooool = 1;
            } 
            int value = readV(top->list, 1);
            top = top->down->down;
            if(booooool){
                prorunpos = value;
            }

        }else if(com == '+'){

            //usuwanie zer stos n
            usuwaniezer(top);

            //usuwanie zer stos n-1
            usuwaniezer(top->down);


            int negf = isnegative(top->list);
            int negs = isnegative(top->down->list);
            if(negf == 0 && negs == 0) { //both positive
                
                switch ( comparelen(top->list, top->down->list))
                {
                case 0:
                    sumingabc(top->list, top->down->list, 0);
                    top->down = top->down->down;
                    break;
                case 1:
                    sumingabc(top->list, top->down->list, 0);
                    top->down = top->down->down;
                    break;
                case 2:
                    sumingabc(top->down->list, top->list, 0);
                    top = top->down;
                    break;
                }


            } else if(negf == 1 && negs == 1) { //both negative
                //change num to positive
                betternega(top);
                betternega(top->down);

                switch ( comparelen(top->list, top->down->list))
                {
                case 0:
                    sumingabc(top->list, top->down->list, 0);
                    top->down = top->down->down;
                    break;
                case 1:
                    sumingabc(top->list, top->down->list, 0);
                    top->down = top->down->down;
                    break;
                case 2:
                    sumingabc(top->down->list, top->list, 0);
                    top = top->down;
                    break;
                }
                betternega(top);
            } else { //one positive and one negative
                if(negf == 1){ betternega(top);}
                if(negs == 1){ betternega(top->down);}
                int equal = compare2(top->list, top->down->list); 
                int bigger = compare(top->list, top->down->list);
                if(equal){
                    top->list->v = '0';
                    top->list->next = nullptr;
                    top->down = top->down->down;
                }

                if(equal == 0){
                    if(bigger == 1){
                        diffingabc(top->list, top->down->list, 0);
                        if(negf == 1) betternega(top);
                        top->down = top->down->down;
                    } else {
                        diffingabc(top->down->list, top->list, 0);
                        if(negs == 1) betternega(top->down);
                        top = top->down;
                    }
                }

                //usuwanie zer stos n
            usuwaniezer(top);

            }
        }else {
            Number *newnum = new Number;
            newnum->v = com;
            newnum->next = top->list;
            top->list = newnum;
        }

    }
    return 0;
}
