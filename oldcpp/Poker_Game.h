#ifndef poker_game_declared
#define poker_game_declared

#include <iostream>
#include <vector>
#include <random>

#include "Poker_State.h"
#include "Poker_Player.h"
#include "Poker_Player_FSP.h"

namespace poker
{
 class Poker_Game
 {
  private:
   poker::Poker_State &state;
   bool verbose;
   bool learning;
   std::mt19937 rnd;

   // Stats
   int game_played;
   std::vector<int> win_players;

  public:
   Poker_Game(poker::Poker_State &state, bool verbose=true, bool learning=true):
    state(state),
    verbose(verbose),
    learning(learning),
    rnd(3),
    game_played(0)
   {}

   void add_player(poker::Poker_Player_FSP &p);
   std::vector<std::reference_wrapper<poker::Poker_Player_FSP>> get_players();

   void end();
   void display_state();
   bool game_over();
   bool round_end();

   void start();

   void new_round();
   void round();

   void reset();
   void display_stats();

   void fictitious(int index_first);
 };
}

#endif
