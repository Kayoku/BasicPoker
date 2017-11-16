#include "Poker_Player_FSP.h"

#include <random>
#include <iostream>
#include <fstream>


////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_FSP::choose_play(poker::Move move)
////////////////////////////////////////////////////////////////////////////
{
 if (move == poker::Move::CALL && get_current_state() == Possible_State::P1)
  move = poker::Move::CHECK;

 current_move = move;
 update_move();
}

////////////////////////////////////////////////////////////////////////////
poker::Move poker::Poker_Player_FSP::get_next_move()
////////////////////////////////////////////////////////////////////////////
{
 std::uniform_real_distribution<> dis(0, 1);
 float p = (float) dis(rnd);
 bool p1 = true;
 
 // j1 ou j2 ?
 if (state.history.size() % 2 == 1)
  p1 = false;
 
 int index = get_current_state();
 float pi = 0.0;
 std::vector<poker::Move> possibles_moves =
 {
  Move::FOLD,
  Move::CALL,
  Move::RAISE
 };
 if (index == Possible_State::P1C_P2R_P1R_P2R_P1R ||
     index == Possible_State::P1R_P2R_P1R_P2R)
  possibles_moves.pop_back();
  
 if (p1)
 {
  for (int i = 0 ; i < possibles_moves.size() ; i++)
  { 
   pi += strats_p1[current_card_value][index][i];
  
   if (p < pi)
   {
    poker::Move m = possibles_moves[i];
    if (index == Possible_State::P1 && current_move == Move::CALL)
     m = Move::CHECK;
    return m;
   } 
  } 
 }  
 else
 {
  index -= 5;
 
  for (int i = 0 ; i < possibles_moves.size() ; i++)
  {
   pi += strats_p2[current_card_value][index][i];
 
   if (p < pi)
    return possibles_moves[i];
  }
 }
 return possibles_moves[0];
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_FSP::play()
////////////////////////////////////////////////////////////////////////////
{
 auto next_move = get_next_move();
 if (get_current_state() == Possible_State::P1 && next_move == Move::CALL)
  next_move = Move::CHECK;
 current_move = next_move;
 update_move();
}

////////////////////////////////////////////////////////////////////////////
poker::Poker_Player_FSP::Possible_State 
poker::Poker_Player_FSP::get_current_state()
////////////////////////////////////////////////////////////////////////////
{
 if (state.history.empty())
  return poker::Poker_Player_FSP::P1;
 else if (state.history.size() == 1)
 {
  if (state.history[0] == poker::Move::RAISE)
   return poker::Poker_Player_FSP::P1R;
  else if (state.history[0] == poker::Move::CHECK)
   return poker::Poker_Player_FSP::P1C;
  else
   return poker::Poker_Player_FSP::END_ROUND;
 }
 else if (state.history.size() == 2)
 {
  if (state.history[1] != poker::Move::RAISE)
   return poker::Poker_Player_FSP::END_ROUND;
  else if (state.history[0] == poker::Move::RAISE)
   return poker::Poker_Player_FSP::P1R_P2R;
  else
   return poker::Poker_Player_FSP::P1C_P2R;
 }
 else if (state.history.size() == 3)
 {
  if (state.history[2] != poker::Move::RAISE)
   return poker::Poker_Player_FSP::END_ROUND;
  else if (state.history[0] == poker::Move::RAISE)
   return poker::Poker_Player_FSP::P1R_P2R_P1R;
  else
   return poker::Poker_Player_FSP::P1C_P2R_P1R;
 }
 else if (state.history.size() == 4)
 {
  if (state.history[3] != poker::Move::RAISE)
   return poker::Poker_Player_FSP::END_ROUND;
  else if (state.history[0] == poker::Move::RAISE)
   return poker::Poker_Player_FSP::P1R_P2R_P1R_P2R;
  else
   return poker::Poker_Player_FSP::P1C_P2R_P1R_P2R;
 }
 else
  return poker::Poker_Player_FSP::P1C_P2R_P1R_P2R_P1R;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_FSP::write_strats(std::string filename)
////////////////////////////////////////////////////////////////////////////
{
 std::ofstream file(filename);
 std::string new_line;

 for (int i = 0 ; i < 170 ; i++)
 {
  for (int j = 0 ; j < 5 ; j++)
  {
   new_line = "";
   for (int k = 0 ; k < 3 ; k++)
    new_line += std::to_string(strats_p1[i][j][k]) + ',';
   new_line.pop_back();
   file << new_line  << '\n';
  }
 }

 for (int i = 0 ; i < 170 ; i++)
 { 
  for (int j = 0 ; j < 5 ; j++)
  { 
   new_line = "";
   for (int k = 0 ; k < 3 ; k++)
    new_line += std::to_string(strats_p2[i][j][k]) + ',';
   new_line.pop_back();
   file << new_line  << '\n';
  } 
 }
}

// To fix
////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_FSP::read_strats(std::string filename)
////////////////////////////////////////////////////////////////////////////
{
 std::ifstream file(filename);
 if (!file.is_open())
 {
  std::cerr << "File: " << filename << " doesn't exist." << std::endl;
  exit(-1);
 }

 for (int i = 0 ; i < 170 ; i++)
  for (int j = 0 ; j < 5 ; j++)
   for (int k = 0 ; k < 3 ; k++)
    file >> strats_p1[i][j][k];

 for (int i = 0 ; i < 170 ; i++)
  for (int j = 0 ; j < 5 ; j++)
   for (int k = 0 ; k < 3 ; k++)
    file >> strats_p2[i][j][k];
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_FSP::reset_like(poker::Poker_Player_FSP &player)
////////////////////////////////////////////////////////////////////////////
{
 chips = player.get_chips();
 current_bet = player.get_bet();
 current_card_value = player.get_card();
 current_move = player.get_move();
 all_in = player.get_all_in();
}


////////////////////////////////////////////////////////////////////////////
void poker::Poker_Player_FSP::update_strat(std::array<float, 3> average, bool p1)
////////////////////////////////////////////////////////////////////////////
{
 int index = get_current_state();

 if (p1)
 {
  for (int i = 0 ; i < average.size() ; i++)
  {
   int cpt = strats_p1_count[get_card()][index];
   float n = (strats_p1[get_card()][index][i] * cpt + average[i]) / (cpt+1); 
   strats_p1[get_card()][index][i] = n;
   strats_p1_count[get_card()][index]++;
  }
 }
 else
 {
  index -= 5;
  for (int i = 0 ; i < average.size() ; i++)
  {
   int cpt = strats_p2_count[get_card()][index];
   float n = (strats_p2[get_card()][index][i] * cpt + average[i]) / (cpt+1);
   strats_p2[get_card()][index][i] = n;
   strats_p2_count[get_card()][index]++;
  }
 }
}
