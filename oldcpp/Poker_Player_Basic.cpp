#include "Poker_Player_Basic.h"

#include <random>

std::string to_move(poker::Move m)
{
 switch(m)
 {
  case poker::Move::CALL:
   return "CALL";
   break;
  case poker::Move::FOLD:
   return "FOLD";
   break;
  case poker::Move::CHECK:
   return "CHECK";
   break;
  case poker::Move::RAISE:
   return "RAISE";
   break;
  default:
   return "START";
 }
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_Basic::play()
////////////////////////////////////////////////////////////////////////////
{
 bool update = true;

 if (all_in)
 {
  if (state.nb_raise == 0)
   current_move = poker::Move::CHECK;
  else
   current_move = poker::Move::CALL;
 }
 else if (current_move == poker::Move::FOLD)
 {
  update = false;
  current_move = poker::Move::FOLD;
 }
 else
 {
  std::vector<poker::Move> possible_moves;
  possible_moves.push_back(poker::Move::FOLD);

  if (state.current_strong_bet == current_bet)
   possible_moves.push_back(poker::Move::CHECK);

  if (state.current_strong_bet > current_bet)
   possible_moves.push_back(poker::Move::CALL);

  if (state.nb_raise < 4 &&
      chips+current_bet > state.current_strong_bet)
   possible_moves.push_back(poker::Move::RAISE);

  int choice = (unsigned int)rnd()%(unsigned int)possible_moves.size();
  current_move = possible_moves[choice];
  display_move();
 }

 if (update)
  update_move();
}
