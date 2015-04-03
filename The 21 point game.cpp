#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
static int cards[52]={0};

void initial_cards(int cards[]); //Reset the cards.
void deal_cards(int get_card[],int); //Get a new card.
void show_cards(int get_card[],int n);//Display the cards.
float counting(int get_card[],int n);//Count the score;
int computer_round(float score,int amount);
char checking(int);//Check the input.

int main()
{
	char answer='y',answer2='y';//Two flags in the game.
	do{
        initial_cards(cards);
        int get_card[21]={0},result;
        float score=0.0;
        deal_cards(get_card,0);
        deal_cards(get_card,1);
        cout <<"Player's stage\nPlayer gets cards ";
        show_cards(get_card,1);
        score = counting(get_card,1);
        int amount=2;//The amount of cards.
        while (answer=='y' || answer=='Y')
        {
            answer=checking(0);
            if (answer=='n' || answer=='N') break;
            else
            {
                deal_cards(get_card,amount);
                cout << "Hit another card: ";
                show_cards(get_card,amount);
                score = counting(get_card,amount);
            if (score>21) break;
            }
            ++amount;
        }
        cout <<endl;
        if (score>21)
            cout <<"The player loses.";
        else
        {
            result = computer_round(score,amount);
            switch (result){
                case 0: cout << "The player wins."; break;
                case 1: cout << "The player loses.";break;
                default: cout << "No one wins.";
            }
        }
		answer2=checking(1);
		answer = 'y'; //Reset the flag.
		if (answer2=='n' || answer=='N') break;
    }while(answer2=='y' || answer2=='Y');
}

void deal_cards(int get_card[],int i)
{
    int a=0;
    srand(time(NULL));
    do{
        a = rand()*52 /(RAND_MAX+1)+1;
        if (cards[a]!=0) break;
    }while(true);
    get_card[i] = cards[a];
    cards[a]=0; //After choosing the card, set it to 0.
}
void show_cards(int get_card[],int n)
{
    char const *suit[4]={"heart","diamond","spade","club"};
    int Suit, points;
    char sign[3]={'J','Q','K'};
    for (int j=0;j<=n;++j)
    {
        Suit = (get_card[j]-1)/13;
        points = get_card[j]-Suit*13;
        cout << suit[Suit]<<' ';
        switch ((points+7)/9){
            case 0: cout <<"A "; break;
            case 2: cout << sign[points-11]<<' '; break;
            default: cout << points <<' ';
        }
    }
}
char checking(int k)
{
    char answer;
    bool flag=true;
    char const *str[2] = {"\nNeed another card?(y/n): ",
                        "\nContinue?(y/n): "};
    do{
        try
        {
            cout << str[k];
            char test[50];
            cin >>test;
            answer = test[0];
            if (answer!='y'&&answer!='Y'
              &&answer!='n'&&answer!='N')
              {
                cout<<"You should input y/n.";
                flag = true;
                throw answer;
              }
            else flag = false;
        }
        catch(char){}
    }while(flag);
    return answer;
}
void initial_cards(int card[52])
{
    for (int j=0;j<52;++j)
        card[j]=j+1;
}
float counting(int get_card[10],int n)
{
    float score=0;
    for (int j=0;j<=n;++j)
        score += ((get_card[j]-1)%13/10) ? 0.5 : get_card[j]%13;
    return score;
}
int computer_round(float score,int amount)
{
    int card_get[21]={0},com_amount=2,result=1;
    float com_score=0.0;
    cout <<"computer's stage\nComputer gets cards ";
    deal_cards(card_get,0);
    deal_cards(card_get,1);
    show_cards(card_get,1);
    cout <<endl;
    com_score = counting(card_get,1);
    while(com_score<=score)
    {
        deal_cards(card_get,com_amount);
        cout <<"Hit another card: ";
        show_cards(card_get,com_amount);
        cout << endl;
        com_score = counting(card_get,com_amount);
        ++com_amount;
        if (com_score>21)
        {result = 0; break;} //The player wins.
        if (com_score==21.0 && com_amount==amount)
        { result = 2; break;} //No one wins.
    }
    return result;
}
