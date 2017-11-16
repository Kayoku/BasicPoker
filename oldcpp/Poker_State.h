#ifndef poker_state_declared
#define poker_state_declared

#include <iostream>
#include <vector>
#include <functional>

namespace poker
{
 class Poker_Player_FSP;

 enum class Move
 {
  START,
  FOLD,
  CHECK,
  CALL,
  RAISE
 };

 struct Poker_State
 {
  // Global infos
  std::vector<std::reference_wrapper<poker::Poker_Player_FSP>> players;
  int nb_round;

  // Round infos
  int nb_raise;           // Nb de raise déjà fait dans le round (max 4)
  int current_strong_bet; // La mise la plus grande actuelle
  int nb_player_fold;     // Nombre de joueur ayant abandonné le round
  int value_pot;          // Valeur totale de la mise
  int nb_player_in_round; // Nombre de joueur ayant débuté ce round
  int cpt_until_raise;    // Compteur depuis le dernier raise
  bool round_start;     // Permet de savoir si tous les joueurs ont au moins joué 1 coup
  std::vector<poker::Move> history; // Historique des coups du round

  Poker_State():
   nb_round(0),
   nb_raise(0),
   current_strong_bet(0),
   nb_player_fold(0),
   value_pot(0),
   nb_player_in_round(0),
   cpt_until_raise(0)
  {}

  void new_game()
  {
   nb_round = 0;
  }

  void new_round(int nb_player)
  {
   nb_round++;
   nb_raise = 0;
   current_strong_bet = 0;
   nb_player_fold = 0;
   value_pot = 0;
   cpt_until_raise = -1;
   nb_player_in_round = nb_player;
   round_start = false;
   history.clear();
  }

  void display()
  {
   std::cout << "nb_round: " << nb_round
             << " nb_raise: " << nb_raise
             << " cpt_until_raise: " << cpt_until_raise
             << std::endl
             << "current_strong_bet: " << current_strong_bet
             << " value_pot: " << value_pot
             << std::endl
             << "nb_player_fold: " << nb_player_fold
             << " nb_player_in_round: " << nb_player_in_round
             << std::endl;
  }

  bool round_started()
  {
   return round_start;
  }

  void reset_like(Poker_State &state)
  {
   nb_round = state.nb_round; 
   nb_raise = state.nb_raise;
   current_strong_bet = state.current_strong_bet;
   nb_player_fold = state.nb_player_fold;
   value_pot = state.value_pot;
   nb_player_in_round = state.nb_player_in_round;
   cpt_until_raise = state.cpt_until_raise;
   round_start = state.round_start;
   history.clear();
   std::copy(state.history.begin(), state.history.end(), std::back_inserter(history));
  }
 };
}

#endif
