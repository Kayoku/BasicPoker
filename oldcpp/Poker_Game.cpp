#include "Poker_Game.h"

#include <random>
#include <algorithm>
#include <iomanip>

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::add_player(poker::Poker_Player_FSP &p)
////////////////////////////////////////////////////////////////////////////
{
 state.players.push_back(p);
 win_players.push_back(0);
 if (verbose)
  std::cout << "new player: " << p.get_id() << std::endl;
}

////////////////////////////////////////////////////////////////////////////
std::vector<std::reference_wrapper<poker::Poker_Player_FSP>> poker::Poker_Game::get_players()
////////////////////////////////////////////////////////////////////////////
{
 std::vector<std::reference_wrapper<poker::Poker_Player_FSP>> ps;
 for (auto player : state.players)
  if (!player.get().lose_game())
   ps.push_back(player);
 return ps;
}

// Renvoie vrai si
// * Après un RAISE, tout le monde à jouer sans refaire un RAISE
// * Si le nb de raise est à 4 et que tout le monde à fait un tour depuis
//   le dernier raise
// * Si tout le monde à FOLD/CHECK
// * Si il ne reste qu'un joueur en jeu
////////////////////////////////////////////////////////////////////////////
bool poker::Poker_Game::round_end()
////////////////////////////////////////////////////////////////////////////
{
 // Nb de check
 int nb_check = 0;
 for (auto &p : get_players())
  if (p.get().get_move() == poker::Move::CHECK)
   nb_check++;

 if ((state.nb_raise > 0 &&
      state.cpt_until_raise+state.nb_player_fold
      == state.nb_player_in_round-1) ||
     state.nb_player_fold + nb_check == state.nb_player_in_round ||
     state.nb_player_fold == state.nb_player_in_round-1 ||
     (state.nb_raise == 4 &&
      state.cpt_until_raise == state.nb_player_in_round-1))
  return true;

 return false;
}

// Game over si:
// * Plus de 20 rounds
// * S'il ne reste plus qu'un joueur en jeu
////////////////////////////////////////////////////////////////////////////
bool poker::Poker_Game::game_over()
////////////////////////////////////////////////////////////////////////////
{
 if (state.nb_round >= 20)
  return true;

 if (get_players().size() <= 1)
  return true;

 return false;
}

// On joue jusqu'à ce que la partie soit terminé
////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::start()
////////////////////////////////////////////////////////////////////////////
{
 game_played++;

 if (verbose)
  std::cout << "start of the game" << std::endl;

 while (!game_over())
  round();

 end();
}

// Nouveau round, on reset l'état du système et l'état des joueurs
////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::new_round()
////////////////////////////////////////////////////////////////////////////
{
 if (verbose)
  std::cout << "new round" << std::endl;

 // Reset state
 state.new_round((int)get_players().size());

 // Reset players
 for (auto &p : get_players())
  p.get().new_round();
}

// Fonction d'affichage de l'état de la partie
////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::display_state()
////////////////////////////////////////////////////////////////////////////
{
 state.display();

 for (auto &p : state.players)
  p.get().display();

 std::cout << std::endl;
}

// Fonction d'affichage de la fin de partie
////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::end()
////////////////////////////////////////////////////////////////////////////
{
 if (verbose)
  std::cout << "End of the game" << std::endl;
 int id_winner = -1;
 int best_chips = 0;
 for (auto &p : state.players)
  if (p.get().get_chips() > best_chips && !p.get().lose_game())
  {
   id_winner = p.get().get_id();
   best_chips = p.get().get_chips();
  }

 win_players[id_winner-1]++;
 if (verbose)
  std::cout << "Player " << id_winner << " win the game!"
            << std::endl;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::reset()
////////////////////////////////////////////////////////////////////////////
{
 state.new_game();
 for (auto &p : state.players)
  p.get().new_game();
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::display_stats()
////////////////////////////////////////////////////////////////////////////
{
 std::cout << game_played << ": ";
 for (auto v : win_players)
  std::cout << v << " ";
 std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::fictitious(int index_first)
////////////////////////////////////////////////////////////////////////////
{
 ///////////////////////////////////////////////////////////////////////////
 // Joue tous les coups possibles (fictivement) de jouer 
 // et crée la matrice de gain

 std::vector<poker::Move> possibles_moves =
 {
  poker::Move::FOLD,
  poker::Move::CALL,
  poker::Move::RAISE
 };

 if (state.nb_raise == 4)
  possibles_moves.pop_back();

 std::vector<std::vector<int>> gain_matrix;

 int index_p1 = index_first;
 int index_p2 = ((index_first+1)%state.nb_player_in_round);

 poker::Poker_Player_FSP save_p1 = state.players[index_p1].get();
 //std::cout << "first: " << save_p1.get_id() << std::endl;
 poker::Poker_Player_FSP save_p2 = state.players[index_p2].get();
 poker::Poker_State save_state = state;

 for (int move_p1 = 0 ; move_p1 < possibles_moves.size() ; move_p1++)
 {
  gain_matrix.push_back({});
  for (int move_p2 = 0 ; move_p2 < possibles_moves.size() ; move_p2++)
  {
   // Remise à état normal du jeu
   state.players[index_p1].get().reset_like(save_p1);
   state.players[index_p2].get().reset_like(save_p2);
   state.reset_like(save_state); 
 
   // Joue le coup décidé
   bool p1_has_play_decided = false;
   bool p2_has_play_decided = false;

   // Joue jusqu'à la fin
   while (!round_end())
   {
    int index_player = index_first % state.nb_player_in_round;
    auto &p = get_players()[index_player].get();
 
    int m = (save_p1.get_id() == p.get_id()) ? move_p1 : move_p2;

    if (!p1_has_play_decided && p.get_id() == 1)
    {
     p.choose_play(possibles_moves[m]);
     p1_has_play_decided = true;
    }
    else if (!p2_has_play_decided && p.get_id() == 2)
    {
     p.choose_play(possibles_moves[m]);
     p2_has_play_decided = true;
    }
    else 
     p.play();

    state.history.push_back(p.get_move());
    state.round_start = true;
    index_first++;
   }

   // Calcul du gain
   int id_winner = -1;
   int best_card = -1;
   int gain = state.value_pot;
  
   for (auto &player : get_players())
   {
    auto &p = player.get();
    if (!p.fold_round())
    {
     if (p.get_card() > best_card)
     {
      best_card = p.get_card();
      id_winner = p.get_id();
     }
    }
   }

   if (id_winner != state.players[index_p1].get().get_id())
    gain = -gain;

   // Met le gain dans la matrice
   gain_matrix[move_p1].push_back(gain); 
  }
 }

 // Remise à état normal du jeu
 state.players[index_p1].get().reset_like(save_p1);
 state.players[index_p2].get().reset_like(save_p2);
 state.reset_like(save_state);

 // Affichage de la matrice
 /*for (auto v: gain_matrix)
 {
  for (auto u: v)
   std::cout << u << " ";
  std::cout << std::endl;
 }
 std::cout << std::endl;*/

 ///////////////////////////////////////////////////////////////////////////
 // Calculs

 std::vector<std::vector<int>> sk;
 std::vector<float> vk_min;
 std::vector<int> ik;
 int add;
 auto m = save_p1.get_next_move();
 if (m == poker::Move::FOLD)
  add = 0;
 else if (m == poker::Move::CALL || m == poker::Move::CHECK)
  add = 1;
 else
  add = 2;
 ik.push_back(add);

 std::vector<std::vector<int>> tk;
 std::vector<float> vk_max;
 std::vector<int> jk;

 for (int cpt = 0 ; cpt < 100 ; cpt++)
 {
  // Récupération des anciens tk/sk
  std::vector<int> sk_old(3, 0);
  std::vector<int> tk_old(3, 0);

  if (cpt > 0)
  {
   sk_old = sk[cpt-1]; 
   tk_old = tk[cpt-1];
  }

  // Calcul des sk avec ik
  std::vector<int> sk_new; 
  for (int i = 0 ; i < gain_matrix.size() ; i++)
   sk_new.push_back(sk_old[i] + gain_matrix[ik[cpt]][i]);
  sk.push_back(sk_new);

  // Nouvel index jk
  int elem = sk_new[0];
  std::vector<int> jk_v;
  jk_v.push_back(0);
  for (int i = 0 ; i < sk_new.size() ; i++)
  {
   if (sk_new[i] < elem)
   {
    elem = sk_new[i];
    jk_v.clear();
    jk_v.push_back(i);
   }
   else if (sk_new[i] == elem)
    jk_v.push_back(i);
  }
  jk.push_back(jk_v[(unsigned int)rnd()%jk_v.size()]);

  // Calcul de vk_min
  vk_min.push_back(((float)sk_new[jk[cpt]])/(float)(cpt+1));

  // Calcul des tk avec jk
  std::vector<int> tk_new;
  for (int i = 0 ; i < gain_matrix.size() ; i++)
   tk_new.push_back(tk_old[i] + gain_matrix[i][jk[cpt]]);
  tk.push_back(tk_new);

  // Nouvel index ik
  elem = tk_new[0];
  std::vector<int> ik_v;
  jk_v.push_back(0);
  for (int i = 0 ; i < tk_new.size() ; i++)
  {
   if (tk_new[i] > elem)
   {
    elem = tk_new[i];
    ik_v.clear();
    ik_v.push_back(i);
   }
   else if (tk_new[i] == elem)
    ik_v.push_back(i);
  }
  ik.push_back(ik_v[(unsigned int)rnd()%ik_v.size()]);

  // Calcul de vk_max
  vk_max.push_back(((float)tk_new[ik[cpt+1]])/(float)(cpt+1));
 }

 // moyenne ik
 std::array<float, 3> average = {0.0, 0.0, 0.0};
 std::array<float, 3> average2 = {0.0, 0.0, 0.0};

 for (int i = 0 ; i < 3 ; i++)
  for (int j = 0 ; j < ik.size() ; j++)
  {
   if (ik[j] == i)
    average[i]+=1; 
   if (jk[j] == i)
    average2[i]+=1;
  }


 for (int i = 0 ; i < 3 ; i++)
 {
  average[i] = average[i] / ik.size();
  average2[i] = average2[i] / jk.size();
 }

 state.players[index_p1].get().update_strat(average, true);
 state.players[index_p2].get().update_strat(average2, false);

 // Affichage du tableau
 /*std::cout << std::setw(5) << "k"
           << std::setw(5) << "ik"
           << std::setw(5) << "sk0"
           << std::setw(5) << "sk1"
           << std::setw(5) << "sk2"
           << std::setw(10) << "vk_min"
           << std::setw(5) << "jk"
           << std::setw(5) << "tk0"
           << std::setw(5) << "tk1"
           << std::setw(5) << "tk2"
           << std::setw(10) << "vk_max" << std::endl;
 for (int i = 0 ; i < 100 ; i++)
 {
  std::cout << std::setw(5) << i+1
            << std::setw(5) << ik[i];

  for (int j = 0 ; j < sk[i].size() ; j++)
   std::cout << std::setw(5) << sk[i][j]; 

  std::cout << std::setw(10) << vk_min[i]
            << std::setw(5) << jk[i];

  for (int j = 0 ; j < tk[i].size() ; j++)
   std::cout << std::setw(5) << tk[i][j];

  std::cout << std::setw(10) << vk_max[i] << std::endl;
 }*/
}

// Fonction principale qui joue un round complet
////////////////////////////////////////////////////////////////////////////
void poker::Poker_Game::round()
////////////////////////////////////////////////////////////////////////////
{
 new_round();

 // Génération des cartes
 std::vector<unsigned int> random_cards;
 while (random_cards.size() < state.nb_player_in_round)
 {
  unsigned int new_card = (unsigned int)rnd()%170;
  if (std::find(random_cards.begin(), random_cards.end(), new_card) ==
      random_cards.end())
   random_cards.push_back(new_card);
 }

 // Distribution des cartes et mise de départ
 for (auto &p : get_players())
 {
  p.get().set_card(random_cards.back());
  random_cards.pop_back();
 }

 // Choix du joueur de départ
 int start_player = (unsigned int)rnd()%state.nb_player_in_round;

 // Tour de jeu
 while (!round_end())
 {
  int index_player = start_player % state.nb_player_in_round;
  auto &p = get_players()[index_player].get();
  
  // Learning if learning
  if (learning)
   fictitious(index_player);

  p.play();
  if (verbose)
  {
   std::cout << "Player " << p.get_id() << " -> "
             << p.display_move() << std::endl;
   display_state();
   std::getchar();
  }
  state.history.push_back(p.get_move());
  state.round_start = true;
  start_player++;
 }

 // Calcul des scores et récompense
 int id_winner = -1;
 int best_card = -1;

 for (auto &player : get_players())
 {
  auto &p = player.get();
  if (!p.fold_round())
  {
   if (p.get_card() > best_card)
   {
    best_card = p.get_card();
    id_winner = p.get_id();
   }
  }
 }

 // Récompense le gagnant
 for (auto &player : get_players())
 {
  auto &p = player.get();
  if (p.get_id() == id_winner)
  {
   p.make_win();
   if (verbose)
    std::cout << "Player " << p.get_id() << " win the round!" << std::endl;
   break;
  }
 }

 // Fait perdre ceux qui n'ont plus de chip
 for (auto &player : get_players())
 {
  auto &p = player.get();
  if (p.get_chips() == 0)
  {
   p.make_lose();
   if (verbose)
    std::cout << "Player " << p.get_id() << " lose the round!" << std::endl;
  }
 }
}
