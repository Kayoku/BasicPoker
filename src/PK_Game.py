# Class PK_Game

import random
from PK_State import PK_State, PK_Game_State, PK_Win
from PK_Player import PK_Player

class PK_Game_Saver:

    def __init__(self, hand_player1, hand_player2, history, state_player1, state_player2, next_player, game_state):
        self.hand_player1 = hand_player1
        self.hand_player2 = hand_player2
        self.history = history
        self.state_player1 = state_player1
        self.state_player2 = state_player2
        self.next_player = next_player
        self.game_state = game_state

class PK_Game:

    def __init__(self):
        self.player1 = PK_Player(self)
        self.player2 = PK_Player(self)
        self.reset_state()

    """
    Permet de savoir si le round en cours est terminé
     - Fold
     - raise + 1 coup check 
     - double check
    """
    def game_end(self):
        if len(self.history) > 0 and self.history[-1] == PK_State.FOLD:
            return True
        elif (len(self.history) > 1 and (self.history[-1] == PK_State.CHECK and (self.history[-2] == PK_State.CHECK or self.history[-2] == PK_State.RAISE))):
            return True
        else:
            return False

    """
    Permet de reset l'état du jeu à son état initial
    """
    def reset_state(self):
        self.history = []
        self.next_player = random.randint(0, 1) 
        self.random_card()
        self.player1.state = PK_State.START
        self.player2.state = PK_State.START
        self.game_state = PK_Game_State.BEGIN

    """
    Distribue deux cartes aux deux joueurs
    """
    def random_card(self):
        card1 = random.randint(1, 170)
        card2 = random.randint(1, 170)
        while card1 == card2:
            card2 = random.randint(1, 170)        
        self.player1.hand = card1
        self.player2.hand = card2

    """
    Permet de savoir qui a gagné
    Renvoie PK_Win.PLAYER1_WIN ou PK_Win.PLAYER2_WIN 
    """
    def winner(self):
        if self.player1.state == PK_State.FOLD:
            return PK_Win.PLAYER2_WIN 
        elif self.player2.state == PK_State.FOLD:
            return PK_Win.PLAYER1_WIN 
        else:
            if self.player1.hand > self.player2.hand:
                return PK_Win.PLAYER1_WIN 
            else:
                return PK_Win.PLAYER2_WIN 

    """
    Permet d'avoir le gain du joueur gagnant
    si game fini
     - 0 raise : 20
     - 1 raise : 40
     - 2 raise : 60
     - 3 raise : 80
     - 4 raise : 100
    sinon
     - 0
    """
    def gain(self):
        nb_raise = self.history.count(PK_State.RAISE)

        if self.game_state == PK_Game_State.ENDED:
            if nb_raise == 0:
                return 20
            elif nb_raise == 1:
                return 40
            elif nb_raise == 2:
                return 60
            elif nb_raise == 3:
                return 80
            else
                return 100
        else:
            return 0

    """
    Permet de remettre le jeu dans un état voulu
    """
    def set_state(self, saver):
        self.reset_state()
        self.player1.hand = saver.hand_player1
        self.player2.hand = saver.hand_player2
        if len(saver.history) % 2 == 0:
            self.next_player = saver.start_player
        else:
            self.next_player = (saver.start_player + 1) % 2
        self.history = saver.history 
        self.game_state = saver.game_state

    """
    Permet de jouer le prochain coup de la partie
    Ne fait rien si la partie est terminée
    Retourne 1 si la partie est en cours
             0 si la partie est terminé
    """
    def run_one_move(self):
        if self.game_state == PK_Game_State.ENDED:
            return 0

        if self.game_state == PK_Game_State.BEGIN:
            self.game_state = PK_Game_State.PLAYING

        if self.next_player:
            self.history.append(self.player1.play())
        else:
            self.history.append(self.player2.play())

        self.next_player = (self.next_player + 1) % 2

        if self.game_end():
            self.game_state = PK_Game_State.ENDED

    """
    Joue une partie avec tous les joueurs
    """
    def run_game(self):
        while self.game_state != PK_Game_State.ENDED:
            self.run_one_move()
            self.display_state()
 
    """
    Affiche l'état du jeu
    """
    def display_state(self):
        print("Player 1: ", end='')
        print(self.player1.hand, end=' ')
        print(self.player1.state)
        print("Player 2: ", end='')
        print(self.player2.hand, end=' ')
        print(self.player2.state)
