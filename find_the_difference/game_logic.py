import pygame
import random
import time
from typing import List, Tuple, Dict
from dataclasses import dataclass
from settings import settings


@dataclass
class GameElement:
    color: Tuple[int, int, int]
    shape: str = "square"
    rect: pygame.Rect = None
    is_different: bool = False


class GameRound:
    def __init__(self):
        self.elements: List[GameElement] = []
        self.different_index: int = -1
        self.start_time: float = 0
        self.generate_round()

    def generate_round(self):
        self.elements = []
        self.start_time = time.time()

        element_count = settings.element_count
        color_count = min(settings.color_count, len(settings.color_palettes[settings.current_palette]))

        palette = settings.color_palettes[settings.current_palette]
        colors = palette[:color_count]

        main_color = colors[0]
        different_color = colors[1] if len(colors) > 1 else (255, 0, 0)

        self.different_index = random.randint(0, element_count - 1)

        for i in range(element_count):
            if i == self.different_index:
                color = different_color
                is_diff = True
            else:
                color = main_color
                is_diff = False

            shape = "square"
            if settings.color_mode == "both" and settings.difficulty == "hard":
                shapes = ["square"]
                shape =  "square"

            self.elements.append(GameElement(
                color=color,
                shape=shape,
                is_different=is_diff
            ))

    def check_answer(self, index: int) -> bool:
        return index == self.different_index

    def get_time_elapsed(self) -> float:
        return time.time() - self.start_time






class GameScore:
    def __init__(self):
        self.score = 0
        self.streak = 0
        self.correct = 0
        self.incorrect = 0
        self.total_time = 0.0
        self.average_time = 0.0

    def add_correct(self, time_taken: float):
        self.correct += 1
        self.streak += 1
        self.total_time += time_taken
        self.average_time = self.total_time / self.correct

        base_points = 100
        speed_bonus = max(0, 50 - int(time_taken * 10))
        streak_bonus = min(200, self.streak * 20)

        self.score += base_points + speed_bonus + streak_bonus

    def add_incorrect(self):
        self.incorrect += 1
        self.streak = 0
        self.score = max(0, self.score - 50)

    def get_accuracy(self) -> float:
        total = self.correct + self.incorrect
        return (self.correct / total) * 100 if total > 0 else 0.0

