# Enum PK_State

from enum import Enum

class PK_State(Enum):
    START = 0
    FOLD  = 1
    CHECK = 2
    RAISE = 3

class PK_Win(Enum):
    PLAYER1_WIN = 0
    PLAYER2_WIN = 1
