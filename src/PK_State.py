# Enum PK_State

from enum import Enum

class PK_State(Enum):
    START = 0
    FOLD  = 1
    CHECK = 2
    RAISE = 3
