#include <iostream>
#include <bitset>
#include <ctime>
using namespace std;

#define MAX_BITSET_SIZE 15

#define FIRST_POLINOMIAL_SIZE 2
#define SECOND_POLINOMIAL_SIZE 5
#define THIRD_POLINOMIAL_SIZE 11
#define SEED 0 //time(0), 23, 34, 38, 192, 218, 245, 284, 322, 355, 356, 387

class Lfsr{
private:
    bitset<MAX_BITSET_SIZE> mask;
    bitset<MAX_BITSET_SIZE> values;

    int size = 0;

    enum Mode{
        started,
        notStarted
    };

    Mode mode = notStarted;
public:

    Lfsr(bitset<MAX_BITSET_SIZE> m, int s){
        size = s;
        for(int i = 1; i <= size; i++){
            mask[i - 1] = m[i];
        }
    }

    bool getNext(){
        if(mode == notStarted){
            initializeLfrs();
            mode = started;
        }

        bool res = values[size - 1] == 1 ? true : false;

        bitset<MAX_BITSET_SIZE> tmp;
        
        tmp.reset();

        for(int i = 0; i < size; i++) 
        {
            tmp[i] = mask[i] & values[i];
        }

        for(int i = 1; i < size; i++) {
            tmp[0] = tmp[0] ^ tmp[i];
        }

        values <<= 1;
        values[size] = 0;
        values[0] = tmp[0] == 1 ? true : false;

        return res;
    }

    void initializeLfrs(){
        srand(SEED); 
        for(int i = 0; i < size; i++) values[i] = rand() % 2;
    }
};

int main(){
    //степени многочленов 2,5,11
    bitset<MAX_BITSET_SIZE> firstPolinomial{"111"};
    bitset<MAX_BITSET_SIZE> secondPolinomial{"101001"};
    bitset<MAX_BITSET_SIZE> thirdPolinomial{"101000000001"};

    Lfsr* lfsr1 = new Lfsr(firstPolinomial, FIRST_POLINOMIAL_SIZE); //x^2 + x + 1
    Lfsr* lfsr2 = new Lfsr(secondPolinomial, SECOND_POLINOMIAL_SIZE); //x^5 + x^2 + 1
    Lfsr* lfsr3 = new Lfsr(thirdPolinomial, THIRD_POLINOMIAL_SIZE); //x^11 + x^2 + 1

    int limit = 100;
    cout << "lfsr ---> ";
    for(int i = 0; i < limit; i++){
        bool res1 = lfsr1->getNext();
        bool res2 = lfsr2->getNext();
        bool res3 = lfsr3->getNext();

        bool res = (res1 & res2) ^ (res2 & res3) ^ res3;

        cout << res << ", ";
    }
    return 0;
}