import json
import os
from dataclasses import dataclass
from typing import List, Dict, Tuple


@dataclass
class GameSettings:
    difficulty: str = "easy"
    color_mode: str = "color"
    element_count: int = 4
    color_count: int = 2
    time_limit: int = 0
    language: str = "en"

    color_palettes: Dict[str, List[Tuple[int, int, int]]] = None
    current_palette: str = "default"

    sound_enabled: bool = True
    music_enabled: bool = True

    def __post_init__(self):
        self.color_palettes = {
            "default": [
                (151, 125, 255),
                (131, 105, 235),
                (171, 145, 275),
            ],
            "pastel": [
                (255, 209, 220),
                (255, 220, 230),
                (255, 200, 210),
            ],
            "dark": [
                (143, 0, 17),
                (123, 0, 0),
                (163, 0, 37)
            ]
        }

    def set_difficulty(self, level: str):
        self.difficulty = level
        if level == "easy":
            self.element_count = 4
            self.color_count = 2
            self.color_mode = "color"
            self.time_limit = 0
        elif level == "medium":
            self.element_count = 6
            self.color_count = 3
            self.color_mode = "color"
            self.time_limit = 10
        elif level == "hard":
            self.element_count = 9
            self.color_count = 3
            self.color_mode = "both"
            self.time_limit = 7

    def save_settings(self, filename: str = "settings.json"):
        with open(filename, 'w') as f:
            json.dump(self.__dict__, f)

    @classmethod
    def load_settings(cls, filename: str = "settings.json"):
        if os.path.exists(filename):
            with open(filename, 'r') as f:
                data = json.load(f)
                return cls(**data)
        return cls()


settings = GameSettings.load_settings()