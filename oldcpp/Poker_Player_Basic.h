#ifndef poker_player_basic_declared
#define poker_player_basic_declared

#include <iostream>
#include <random>
#include "Poker_Player.h"

namespace poker
{
 class Poker_Player_Basic : public Poker_Player
 {
  private:
   std::mt19937 rnd;

  public:
   Poker_Player_Basic(int id,
                      poker::Poker_State &state):
    Poker_Player(id, state),
    rnd(id)
   {}

   void play() override;
 };
}

#endif
