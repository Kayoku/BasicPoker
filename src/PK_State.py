# Enum PK_State

from enum import Enum

class PK_State(Enum):
    START = 0
    FOLD  = 1
    CHECK = 2
    RAISE = 3

class PK_Game_State(Enum):
    BEGIN   = 0
    PLAYING = 1
    ENDED   = 2

class PK_Win(Enum):
    PLAYER1_WIN = 0
    PLAYER2_WIN = 1

def possibles_states():
    return  [(),
             (PK_State.RAISE), 
             (PK_State.RAISE, PK_State.RAISE),
             (PK_State.RAISE, PK_State.RAISE, PK_State.RAISE),
             (PK_State.RAISE, PK_State.RAISE, PK_State.RAISE, PK_State.RAISE),
             (PK_State.CHECK),
             (PK_State.CHECK, PK_State.RAISE),
             (PK_State.CHECK, PK_State.RAISE, PK_State.RAISE),
             (PK_State.CHECK, PK_State.RAISE, PK_State.RAISE, PK_State.RAISE),
             (PK_State.CHECK, PK_State.RAISE, PK_State.RAISE, PK_State.RAISE, PK_State.RAISE)]
