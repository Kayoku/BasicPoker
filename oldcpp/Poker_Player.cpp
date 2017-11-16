#include "Poker_Player.h"

#include <random>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::set_card(int card)
////////////////////////////////////////////////////////////////////////////
{
 current_card_value = card;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::new_round()
////////////////////////////////////////////////////////////////////////////
{
 current_move = poker::Move::START;
 current_bet = 0;
 current_card_value = 0;
 bet(1);
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::new_game()
////////////////////////////////////////////////////////////////////////////
{
 lose = false;
 chips = 10;
 current_bet = 0;
 current_card_value = 0;
 current_move = poker::Move::START;
 all_in = false;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::display()
////////////////////////////////////////////////////////////////////////////
{
 if (!lose_game())
 {
  std::string chips = "(" + std::to_string(get_chips()) + ")";
  std::cout << id
            << std::setw(6) << chips
            << std::setw(4) << get_bet()
            << std::setw(4) << get_card()
            << std::setw(6) << display_move() << std::endl;
 }
 else
  std::cout << id << " LOSE" << std::endl;
}

////////////////////////////////////////////////////////////////////////////
std::string poker::Poker_Player::display_move()
////////////////////////////////////////////////////////////////////////////
{
 switch(current_move)
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
void poker::Poker_Player::bet(int new_bet)
////////////////////////////////////////////////////////////////////////////
{
 if (new_bet >= chips)
 {
  current_bet += chips;
  state.value_pot += chips;
  chips = 0;
  all_in = true;
 }
 else
 {
  current_bet += new_bet;
  state.current_strong_bet = current_bet;
  state.value_pot += new_bet;
  chips -= new_bet;
 }
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::update_move()
////////////////////////////////////////////////////////////////////////////
{
 if (current_move == poker::Move::CALL)
 {
  bet(state.current_strong_bet-current_bet);
  if (state.nb_raise > 0)
   state.cpt_until_raise += 1;
 }
 else if (current_move == poker::Move::CHECK)
 {
  if (state.nb_raise > 0)
   state.cpt_until_raise += 1;
 }
 else if (current_move == poker::Move::RAISE)
 {
  bet((state.current_strong_bet-current_bet)+1);
  state.nb_raise += 1;
  state.cpt_until_raise = 0;
 }
 else if (current_move == poker::Move::FOLD)
  state.nb_player_fold += 1;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::make_win()
////////////////////////////////////////////////////////////////////////////
{
 chips += state.value_pot;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player::make_lose()
////////////////////////////////////////////////////////////////////////////
{
 lose = true;
}
