#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
#include <time.h>
#include <random>
using namespace std;

struct card{
    int number;
    char symbol[20];
};

class Player{
    public:
        stack<card> hand;
        stack<card> collected;

};

void display(card a){
    cout<<a.number<<" of "<<a.symbol;
}

void collect(Player &p,card c1,card c2){
    p.collected.push(c1);
    p.collected.push(c2);
}

void collect_table(vector<card> table,Player &p){
    for(int i=0;i<table.size();i++){
        p.collected.push(table[i]);
    }
}

void show_results(Player &p1,Player &p2){
    int k1 = 0,k2 = 0;
    while(!p1.collected.empty()){
        p1.collected.pop();
        k1++;
    }
    cout<<"Player 1's score is: "<<k1<<endl;
    while(!p2.collected.empty()){
        p2.collected.pop();
        k2++;
    }
    cout<<"Player 2's score is: "<<k2<<endl;
    if(k1>k2){cout<<"You won!"<<endl;}
    else if(k1 < k2){cout<<"Player 2 won!"<<endl;}
    else{cout<<"It's a draw"<<endl;}
}

int war(Player &p1,Player &p2){
    vector<card> table;
    table.push_back(p1.hand.top());
    table.push_back(p2.hand.top());
    p1.hand.pop();
    p2.hand.pop();
    table.push_back(p1.hand.top());
    table.push_back(p2.hand.top());
    p1.hand.pop();
    p2.hand.pop();
    table.push_back(p1.hand.top());
    cout<<"You  drew ";display(p1.hand.top());cout<<endl;
    table.push_back(p2.hand.top());
    cout<<"Player 2 drew ";display(p2.hand.top());cout<<endl;
    if(p1.hand.top().number > p2.hand.top().number){cout<<"You win the cards!"<<endl;collect_table(table,p1);return 0;}
    if(p1.hand.top().number < p2.hand.top().number){cout<<"Player 2 wins the cards!"<<endl;collect_table(table,p2);return 0;}
    p1.hand.pop();
    p2.hand.pop();
    war(p1,p2);
    return 0;
}

int myrandom(int i){return rand() % i;}

class Deck{
    public:
        stack<card> deck;
        const char symbols[4][20] = {"Hearts","Clubs","Diamonds","Spades"};
        void initialize(){
            for(int i=1;i<14;i++){
                for(int j=0;j<4;j++){
                    card temp;
                    temp.number = i;
                    strcpy(temp.symbol,symbols[j]);
                    deck.push(temp);
                }
            }
        }
        void shuffle(){
            vector<card> temp;
            while(!deck.empty()){
                temp.push_back(deck.top());
                deck.pop();
            }
            deck = stack<card>();
            random_shuffle(temp.begin(),temp.end(),myrandom);
            for(int i=0;i<temp.size();i++){
                deck.push(temp[i]);
            }
            temp.clear();

        }
        void split(Player &p1,Player &p2){
            while(!deck.empty()){
                p1.hand.push(deck.top());
                deck.pop();
                p2.hand.push(deck.top());
                deck.pop();
            }
        }
};

int main(){
    int ok = 0;
    cout<<"Enter 1 to play: ";cin>>ok;cout<<endl;
    if(ok != 1){return 0;}
    srand(time(0));
    Deck deck1;
    Player p1,p2;
    deck1.initialize();
    deck1.shuffle();
    deck1.split(p1,p2);
    while(!p1.hand.empty()){int draw = 0;
        cout<<"Enter 1 to draw hand: ";cin>>draw;cout<<endl;
        if(draw != 1){return 0;}
        display(p1.hand.top());
        cout<<" vs ";
        display(p2.hand.top());
        cout<<endl;
        if(p1.hand.top().number > p2.hand.top().number){collect(p1,p1.hand.top(),p2.hand.top());cout<<"You win the cards!"<<endl;}
        else if(p1.hand.top().number < p2.hand.top().number){collect(p2,p1.hand.top(),p2.hand.top());cout<<"Player 2 wins the cards!"<<endl;}
        else{cout<<"It's war"<<endl;war(p1,p2);}
        p1.hand.pop();
        p2.hand.pop();
    }
    show_results(p1,p2);
    

    return 0;
}