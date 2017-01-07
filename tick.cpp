// tick.cpp
// Jonathan Pierson
// admin@kinix.net
// http://kinix.net

// you may wish to consult my terribly-handwritten version of some of the
// concepts here in the github repo:
// https://github.com/piersonjon/tbsdemos

// a demonstration of an implementation of speed as a player stat in a
// turn-based game. with this setup, we'll be able to show how this
// setup can be used as a "charge bar," similar to that in games like
// Final Fantasy 4. we'll also address the issue in our system where
// multiple people can arrive at a full bar on the same tick, using
// simple math to determine who should go first on a tick. (in the event
// of a total tie, we have the computer flip a coin.)

// please use this code as reference, and modify to any degree.
// any use of this code is only permitted in any form when directly
// cited as by Jonathan Pierson, reachable at admin@kinix.net and on
// the web at http://kinix.net. any feedback is welcome!

// RIP original tick.cpp 1/6/17 1am-4am
// "g++ -o tick.cpp tick.exe"

#include <cstdio>         // printf, scanf
#include <cstdlib>        // srand, rand
#include <string>         // string type
#include <ctime>          // time

using namespace std;

int main() {
  srand(time(NULL));      // initializes the random seed to the current time
  int p1[2] = {0,0};      // creates 2 characters with 0 speed and 0 pool.
  int p2[2] = {0,0};
  printf("TBS Speed Stat Demo\n\n");
  int gear[2];            // for the sake of video games, we get gear!
  gear[0]=rand()%20;      // it's up to chance who gets better gear, though.
  gear[1]=rand()%25;      // you can't win every battle!
  p1[0] = 20+gear[0];   // character 1 has a speed of 20+(0~20 from gear).
  p2[0] = 15+gear[1];   // character 2 has a speed of 15+(0~25 from gear).
  printf("P1 has %i(20+%i) speed.\nP2 has %i(15+%i) speed.\n\n",p1[0],gear[0],p2[0],gear[1]);
  int turn = 0;           // starts the turn counter at 0.
  int garbage;            // worthless, just use it to slow the code
  while (true) {          // infinite. we can limit this w/(garbage==0), etc.
    turn++;               // increment turn
    printf("It's game turn %i.\n",turn);
    printf("P1: %i + %i = ",p1[1],p1[0]);
    p1[1]+=p1[0];         // adds speed to pool for P1
    printf("%i\n",p1[1]);
    printf("P2: %i + %i = ",p2[1],p2[0]);
    p2[1]+=p2[0];         // repeat this process for P2
    printf("%i\n",p2[1]);
    if (p1[1]>=100) {
      if (p2[1]>=100) {
        printf("Both characters have reached the Ready state!\n");
        p1[1]-=100;       // reduce pool by 100 (full) for both players
        p2[1]-=100;
        // from here, to determine who acts first, we must divide the
        // remainder of the bar by the speed to determine what percent
        // of the bar was used to reach 100 pool for each character.
        // we must also assume our engine has a SPD limit of 99 or 100,
        // since this math won't work properly beyond that point.
        // theoretically, we could run the check recursively, but in the
        // interest of keeping things simple, we're going to leave it out.
        // remember that to get accurate results, we need to declare that
        // our integers are regarded as floats for this check.

        // frac is the amount of the bar that was over 100 pool.
        // whoever has a higher frac reached 100 pool at a lower percentage.
        // this lets us sort multiple actors on the same turn, or tick.
        // a tie will naturally occur every x rounds, where x is
        // the size of the pool.
        float frac1=(float(p1[1])/float(p1[0]));
        float frac2=(float(p2[1])/float(p2[0]));
        if (frac1>frac2) {
          printf("P1 will act first!\nP2 will act after.\n");
        }
        else if (frac1<frac2) {
          printf("P2 will act first!\nP1 will act after.\n");
        }
        else {
          printf("It's a tie!\nA coin is flipped...\n");
          int tb=rand()%100;
          printf("COIN: %i\n",tb);
          if (tb%2==0) {
            printf("P1 (evens) has won the toss!\n");
            printf("P1 will act first!\nP2 will act after.\n");
          }
          else {
            printf("P2 (odds) has won the toss!\n");
            printf("P2 will act first!\nP1 will act after.\n");
          }
        }
        printf("P1: %f\nP2: %f\n",frac1,frac2);
        scanf("%i",&garbage);
      }
      else {
        printf("P1 is acting this turn.\n");
        p1[1]-=100;       // reduce P1 pool by 100 (full)
      }
    }
    else if (p2[1]>=100) {
      printf("P2 is acting this turn.\n");
      p2[1]-=100;         // reduce P2 pool by 100 (full)
    }

  }
  return 0;
}
