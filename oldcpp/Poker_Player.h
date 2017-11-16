#ifndef poker_player_declared
#define poker_player_declared

#include <iostream>
#include <random>
#include "Poker_State.h"

namespace poker
{
 class Poker_Player
 {
  protected:
   // Global infos
   int id;
   poker::Poker_State &state;
   bool lose;

   //memoryRL       <- liste des comportements adverses
   //memorySL       <- liste des meilleurs choix
   //average_policy <- réseau de neurone
   //action_value   <- réseau de neurone

   // Round infos
   int chips;
   int current_bet;
   int current_card_value;
   poker::Move current_move;
   bool all_in;

  public:
   Poker_Player(int id,
                poker::Poker_State &state):
    id(id),
    state(state),
    lose(false),
    chips(10),
    current_bet(0),
    current_card_value(0),
    current_move(poker::Move::START),
    all_in(false)
   {}

   int get_id() { return id; }
   int get_card() { return current_card_value; }
   int get_chips() { return chips; }
   int get_bet() { return current_bet; }
   poker::Move get_move() { return current_move; }
   bool lose_game() { return lose; }
   bool fold_round() { return current_move == poker::Move::FOLD; }
   bool get_all_in() { return all_in; }

   void display();
   std::string display_move();

   void new_round();
   void new_game();
   void set_card(int card);

   void bet(int new_bet);
   void update_move();
   void make_win();
   void make_lose();

   virtual void play() = 0;
 };
}

#endif
