#include <iostream>

#include "Poker_State.h"
#include "Poker_Game.h"
#include "Poker_Player_Basic.h"
#include "Poker_Player_FSP.h"

int main()
{
 poker::Poker_State state;
 poker::Poker_Game game(state, false);
 poker::Poker_Player_FSP p1(1, state);
 poker::Poker_Player_FSP p2(2, state);
 game.add_player(p1);
 game.add_player(p2);

 for (int i = 0 ; i < 100000 ; i++)
 {
  game.reset();
  game.start();
  game.display_stats();
 }

 p1.write_strats("test.txt");

 return 0;
}
