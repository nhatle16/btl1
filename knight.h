#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"
void check_HP_Level_1To5(int & HP, int & phoenixdown, int & level, int level0, float & damage, int maxHP, int & rescue);
void check_HP_Level_6(int & HP, int & remedy, int & level, int level0, int & rescue);
void check_HP_Level_7(int & HP, int & maidenkiss, int & level, int level0, int & rescue);
int mushFibo(int n);
bool isPrime(int n);
int nearestPrime(int n);
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);


#endif // __KNIGHT_H__