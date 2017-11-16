#ifndef poker_player_fsp_declared
#define poker_player_fsp_declared

#include <iostream>
#include <random>
#include "Poker_Player.h"

namespace poker
{
 class Poker_Player_FSP : public Poker_Player
 {
  private:
   std::mt19937 rnd;
   // 0 = Fold / 1 = Call/Check / 2 = Raise
   float strats_p1[170][5][3]; // 170 = Nb de cartes; 5 = Etats possibles p1   
   float strats_p2[170][5][3]; // 170 = Nb de cartes; 5 = Etats possibles p2 

   int strats_p1_count[170][5];
   int strats_p2_count[170][5];

  public:
   Poker_Player_FSP(int id,
                    poker::Poker_State &state):
    Poker_Player(id, state),
    rnd(id)
   {
    for (int i = 0 ; i < 170 ; i++)
    {
     for (int j = 0 ; j < 5 ; j++)
     {
      for (int k = 0 ; k < 3 ; k++)
      {
       strats_p1[i][j][k] = (float)0.333333; 
       strats_p2[i][j][k] = (float)0.333333; 
      }

      strats_p1_count[i][j] = 1;
      strats_p2_count[i][j] = 1;
     }
    }

    // Dernier choix P1 et P2, pas de raise possible
    for (int i = 0 ; i < 170 ; i++)
    {
     strats_p1[i][4][0] = 0.5;
     strats_p1[i][4][1] = 0.5;
     strats_p1[i][4][2] = 0;
    } 

    for (int i = 0 ; i < 170 ; i++)
    {
     strats_p2[i][4][0] = 0.5;
     strats_p2[i][4][1] = 0.5;
     strats_p2[i][4][2] = 0;
    }
   }

   /////////////////////////////////////////
   enum Possible_State
   {
    // P1
    P1,                  // p1 first move
    P1R_P2R,             // p1 raise, then p2 raise
    P1C_P2R,             // p1 check, then p2 raise
    P1C_P2R_P1R_P2R,     // p1 check, then p2 raise, then p1, then p2
    P1R_P2R_P1R_P2R,     // p1 raise, then p2 raise, then p1, then p2
    // P2
    P1R,                 // p1 raise
    P1C,                 // p1 check
    P1R_P2R_P1R,         // p1 raise, then p2 raise, then p1 raise
    P1C_P2R_P1R,         // p1 raise, then p2 raise, then p1 raise
    P1C_P2R_P1R_P2R_P1R, // p1 check, then p2 raise, then p1, then p2, then p1 
    //
    END_ROUND,
    possible_state
   };
   /////////////////////////////////////////

   /////////////////////////////////////////
   // F = Fold; C = Check/Call; R = Raise
   /*enum Strategy
   {
    P1_F,
    P1_C_F,
    P1_C_C,
    P1_C_R_F,
    P1_C_R_C,
    P1_C_R_R,
    P1_R_F,
    P1_R_C,
    P1_R_R_F,
    P1_R_R_C,
    P2_F,
    P2_C,
    P2_R_F,
    P2_R_C,
    P2_R_R_F,
    P2_R_R_C,
    strategy
   };*/
   /////////////////////////////////////////

   void play() override;
   void choose_play(poker::Move move);
   poker::Move get_next_move();
   Possible_State get_current_state();

   void write_strats(std::string filename);
   void read_strats(std::string filename);

   void reset_like(Poker_Player_FSP &player);
   void update_strat(std::array<float, 3> average, bool p1);
 };
}

#endif
