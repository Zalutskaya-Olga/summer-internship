import pygame
import sys
import os
from typing import List, Tuple, Optional, Dict
from settings import settings
from game_logic import GameRound, GameElement, GameScore
from statistics import GameStatistics

pygame.init()
pygame.mixer.init()

SCREEN_WIDTH = 1024
SCREEN_HEIGHT = 768
FPS = 60
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
GREEN = (0, 212, 60)
RED = (150, 0, 35)
BLUE = (168, 0, 62)


class GameUI:
    def __init__(self):
        self.screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
        pygame.display.set_caption("Find the Difference")
        self.clock = pygame.time.Clock()

        try:
            self.font = pygame.font.Font(os.path.join("assets", "fonts", "arial.ttf"), 24)
            self.title_font = pygame.font.Font(os.path.join("assets", "fonts", "arial.ttf"), 36)
        except:
            self.font = pygame.font.SysFont("Arial", 24)
            self.title_font = pygame.font.SysFont("Arial", 36)

        self.sounds = {
            "correct": None,
            "wrong": None,
            "click": None
        }

        self.load_assets()

        self.current_round: Optional[GameRound] = None
        self.score: GameScore = GameScore()
        self.stats = GameStatistics()
        self.game_state = "menu"
        self.message = ""
        self.message_timer = 0
        self.time_left = 0
        self.last_update_time = 0
        self.scroll_offset = 0
        self.text_input = ""
        self.active_input = None

    def load_assets(self):
        try:
            sound_path = os.path.join("assets", "sounds")
            if os.path.exists(sound_path):
                self.sounds["correct"] = pygame.mixer.Sound(os.path.join(sound_path, "correct.wav"))
                self.sounds["wrong"] = pygame.mixer.Sound(os.path.join(sound_path, "wrong.wav"))
                self.sounds["click"] = pygame.mixer.Sound(os.path.join(sound_path, "click.wav"))
        except:
            print("Could not load sounds")

    def play_sound(self, sound_name: str):
        if settings.sound_enabled and self.sounds.get(sound_name):
            self.sounds[sound_name].play()

    def start_new_round(self):
        self.current_round = GameRound()
        self.time_left = settings.time_limit
        self.last_update_time = pygame.time.get_ticks()

    def draw_text_input(self, x, y, width, height, text, active):
        color = BLUE if active else BLACK
        pygame.draw.rect(self.screen, WHITE, (x, y, width, height))
        pygame.draw.rect(self.screen, color, (x, y, width, height), 2)

        text_surface = self.font.render(text, True, BLACK)
        self.screen.blit(text_surface, (x + 5, y + 5))

    def draw_menu(self):
        self.screen.fill(WHITE)
        buttons = {}

        title = self.title_font.render("Find the Difference", True, BLACK)
        self.screen.blit(title, (SCREEN_WIDTH // 2 - title.get_width() // 2, 50))

        # Difficulty buttons
        easy_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, 150, 200, 50)
        medium_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, 220, 200, 50)
        hard_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, 290, 200, 50)

        # Other buttons
        stats_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, 360, 200, 50)
        settings_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, 430, 200, 50)
        quit_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, 500, 200, 50)

        # Draw buttons
        pygame.draw.rect(self.screen, (100, 255, 100), easy_btn)
        pygame.draw.rect(self.screen, (255, 255, 100), medium_btn)
        pygame.draw.rect(self.screen, (255, 100, 100), hard_btn)
        pygame.draw.rect(self.screen, BLUE, stats_btn)
        pygame.draw.rect(self.screen, GRAY, settings_btn)
        pygame.draw.rect(self.screen, (200, 200, 200), quit_btn)

        # Button labels
        self.screen.blit(self.font.render("Easy", True, BLACK),
                         (easy_btn.centerx - 25, easy_btn.centery - 10))
        self.screen.blit(self.font.render("Medium", True, BLACK),
                         (medium_btn.centerx - 40, medium_btn.centery - 10))
        self.screen.blit(self.font.render("Hard", True, BLACK),
                         (hard_btn.centerx - 25, hard_btn.centery - 10))
        self.screen.blit(self.font.render("Statistics", True, BLACK),
                         (stats_btn.centerx - 50, stats_btn.centery - 10))
        self.screen.blit(self.font.render("Settings", True, BLACK),
                         (settings_btn.centerx - 45, settings_btn.centery - 10))
        self.screen.blit(self.font.render("Quit", True, BLACK),
                         (quit_btn.centerx - 25, quit_btn.centery - 10))

        return {
            "easy": easy_btn,
            "medium": medium_btn,
            "hard": hard_btn,
            "stats": stats_btn,
            "settings": settings_btn,
            "quit": quit_btn
        }

    def draw_game(self):
        self.screen.fill(WHITE)

        if not self.current_round:
            self.start_new_round()

        # Draw game elements
        element_count = len(self.current_round.elements)
        grid_size = int(element_count ** 0.5)
        if grid_size * grid_size < element_count:
            grid_size += 1

        cell_size = min(150, SCREEN_WIDTH // (grid_size + 2))
        start_x = (SCREEN_WIDTH - (grid_size * cell_size)) // 2
        start_y = 150 + self.scroll_offset

        for i, element in enumerate(self.current_round.elements):
            row = i // grid_size
            col = i % grid_size

            x = start_x + col * cell_size
            y = start_y + row * cell_size

            element.rect = pygame.Rect(x, y, cell_size - 10, cell_size - 10)

            # Draw shapes without borders
            if element.shape == "square":
                pygame.draw.rect(self.screen, element.color, element.rect)
            elif element.shape == "circle":
                pygame.draw.ellipse(self.screen, element.color, element.rect)
            elif element.shape == "triangle":
                points = [
                    (x + cell_size // 2, y + 5),
                    (x + 5, y + cell_size - 5),
                    (x + cell_size - 5, y + cell_size - 5)
                ]
                pygame.draw.polygon(self.screen, element.color, points)

        # Draw score info
        score_text = self.font.render(f"Score: {self.score.score}", True, BLACK)
        streak_text = self.font.render(f"Streak: {self.score.streak}", True, BLACK)
        accuracy_text = self.font.render(f"Accuracy: {self.score.get_accuracy():.1f}%", True, BLACK)

        self.screen.blit(score_text, (20, 20))
        self.screen.blit(streak_text, (20, 50))
        self.screen.blit(accuracy_text, (20, 80))

        # Timer
        if settings.time_limit > 0:
            time_text = self.font.render(f"Time: {self.time_left}s", True, BLACK)
            self.screen.blit(time_text, (SCREEN_WIDTH - 150, 20))

        # Message
        if self.message and self.message_timer > 0:
            msg_color = RED if "Wrong" in self.message else GREEN
            msg_surface = self.font.render(self.message, True, msg_color)
            self.screen.blit(msg_surface, (SCREEN_WIDTH // 2 - msg_surface.get_width() // 2, 100))
            self.message_timer -= 1

        # Back button
        back_btn = pygame.Rect(20, SCREEN_HEIGHT - 70, 100, 50)
        pygame.draw.rect(self.screen, GRAY, back_btn)
        self.screen.blit(self.font.render("Back", True, BLACK),
                         (back_btn.centerx - 25, back_btn.centery - 10))

        return {"back": back_btn}
        # Draw score info
        score_text = self.font.render(f"Score: {self.score.score}", True, BLACK)
        streak_text = self.font.render(f"Streak: {self.score.streak}", True, BLACK)
        accuracy_text = self.font.render(f"Accuracy: {self.score.get_accuracy():.1f}%", True, BLACK)

        self.screen.blit(score_text, (20, 20))
        self.screen.blit(streak_text, (20, 50))
        self.screen.blit(accuracy_text, (20, 80))

        # Timer
        if settings.time_limit > 0:
            time_text = self.font.render(f"Time: {self.time_left}s", True, BLACK)
            self.screen.blit(time_text, (SCREEN_WIDTH - 150, 20))

        # Message
        if self.message and self.message_timer > 0:
            msg_color = RED if "Wrong" in self.message else GREEN
            msg_surface = self.font.render(self.message, True, msg_color)
            self.screen.blit(msg_surface, (SCREEN_WIDTH // 2 - msg_surface.get_width() // 2, 100))
            self.message_timer -= 1

        # Back button
        back_btn = pygame.Rect(20, SCREEN_HEIGHT - 70, 100, 50)
        pygame.draw.rect(self.screen, GRAY, back_btn)
        self.screen.blit(self.font.render("Back", True, BLACK),
                         (back_btn.centerx - 25, back_btn.centery - 10))

        return {"back": back_btn}

    def draw_stats(self):
        self.screen.fill(WHITE)
        buttons = {}

        title = self.title_font.render("Statistics", True, BLACK)
        self.screen.blit(title, (SCREEN_WIDTH // 2 - title.get_width() // 2, 50))

        # Stats table
        headers = ["Metric", "Value"]
        stats_data = [
            ["Total Score", self.score.score],
            ["Correct", self.score.correct],
            ["Incorrect", self.score.incorrect],
            ["Accuracy", f"{self.score.get_accuracy():.1f}%"],
            ["Avg Time", f"{self.score.average_time:.2f}s"],
            ["Best Streak", self.score.streak]
        ]

        # Draw table
        cell_width = 200
        cell_height = 40
        start_x = SCREEN_WIDTH // 2 - cell_width
        start_y = 150

        # Headers
        pygame.draw.rect(self.screen, BLUE, (start_x, start_y, cell_width * 2, cell_height))
        for i, header in enumerate(headers):
            text = self.font.render(header, True, WHITE)
            self.screen.blit(text, (start_x + i * cell_width + cell_width // 2 - text.get_width() // 2,
                                    start_y + cell_height // 2 - text.get_height() // 2))

        # Data rows
        for row_idx, row in enumerate(stats_data):
            y_pos = start_y + (row_idx + 1) * cell_height
            for col_idx, cell in enumerate(row):
                x_pos = start_x + col_idx * cell_width
                pygame.draw.rect(self.screen, GRAY if row_idx % 2 == 0 else WHITE,
                                 (x_pos, y_pos, cell_width, cell_height))
                pygame.draw.rect(self.screen, BLACK, (x_pos, y_pos, cell_width, cell_height), 1)

                text = self.font.render(str(cell), True, BLACK)
                self.screen.blit(text, (x_pos + cell_width // 2 - text.get_width() // 2,
                                        y_pos + cell_height // 2 - text.get_height() // 2))

        # Back button
        back_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, SCREEN_HEIGHT - 100, 200, 50)
        pygame.draw.rect(self.screen, GRAY, back_btn)
        self.screen.blit(self.font.render("Back", True, BLACK),
                         (back_btn.centerx - 25, back_btn.centery - 10))

        return {"back": back_btn}

    def draw_settings(self):
        self.screen.fill(WHITE)
        buttons = {}

        title = self.title_font.render("Settings", True, BLACK)
        self.screen.blit(title, (SCREEN_WIDTH // 2 - title.get_width() // 2, 50))

        # Text input for player name
        name_label = self.font.render("Player Name:", True, BLACK)
        self.screen.blit(name_label, (100, 120))
        name_input = pygame.Rect(300, 120, 200, 30)
        self.draw_text_input(300, 120, 200, 30, self.text_input, self.active_input == "name")

        # Difficulty settings
        diff_label = self.font.render("Difficulty:", True, BLACK)
        self.screen.blit(diff_label, (100, 170))

        easy_btn = pygame.Rect(300, 170, 100, 30)
        medium_btn = pygame.Rect(410, 170, 100, 30)
        hard_btn = pygame.Rect(520, 170, 100, 30)

        pygame.draw.rect(self.screen, (255, 181, 225) if settings.difficulty == "easy" else GRAY, easy_btn)
        pygame.draw.rect(self.screen, (255, 148, 212) if settings.difficulty == "medium" else GRAY, medium_btn)
        pygame.draw.rect(self.screen, (171, 12, 107) if settings.difficulty == "hard" else GRAY, hard_btn)

        self.screen.blit(self.font.render("Easy", True, BLACK),
                         (easy_btn.centerx - 25, easy_btn.centery - 10))
        self.screen.blit(self.font.render("Medium", True, BLACK),
                         (medium_btn.centerx - 40, medium_btn.centery - 10))
        self.screen.blit(self.font.render("Hard", True, BLACK),
                         (hard_btn.centerx - 25, hard_btn.centery - 10))

        # Color palette
        palette_label = self.font.render("Color Palette:", True, BLACK)
        self.screen.blit(palette_label, (100, 220))
        palette_btn = pygame.Rect(300, 220, 100, 30)
        pygame.draw.rect(self.screen, BLUE, palette_btn)
        self.screen.blit(self.font.render(settings.current_palette.capitalize(), True, BLACK),
                         (palette_btn.centerx - 40, palette_btn.centery - 10))

        # Sound settings
        sound_label = self.font.render("Sound:", True, BLACK)
        self.screen.blit(sound_label, (100, 270))
        sound_btn = pygame.Rect(300, 270, 100, 30)
        pygame.draw.rect(self.screen, BLUE, sound_btn)
        sound_text = "ON" if settings.sound_enabled else "OFF"
        self.screen.blit(self.font.render(sound_text, True, BLACK),
                         (sound_btn.centerx - 15, sound_btn.centery - 10))

        # Back button
        back_btn = pygame.Rect(SCREEN_WIDTH // 2 - 100, SCREEN_HEIGHT - 100, 200, 50)
        pygame.draw.rect(self.screen, GRAY, back_btn)
        self.screen.blit(self.font.render("Back", True, BLACK),
                         (back_btn.centerx - 25, back_btn.centery - 10))

        buttons.update({
            "name_input": name_input,
            "easy": easy_btn,
            "medium": medium_btn,
            "hard": hard_btn,
            "palette": palette_btn,
            "sound": sound_btn,
            "back": back_btn
        })

        return buttons

    def update_timer(self):
        current_time = pygame.time.get_ticks()
        if current_time - self.last_update_time >= 1000:
            if self.time_left > 0:
                self.time_left -= 1
                self.last_update_time = current_time
            else:
                self.message = "Time's up! Wrong!"
                self.message_timer = 60
                self.score.add_incorrect()
                self.play_sound("wrong")
                self.start_new_round()

    def handle_keyboard_input(self, event):
        if self.active_input:
            if event.key == pygame.K_BACKSPACE:
                self.text_input = self.text_input[:-1]
            elif event.key == pygame.K_RETURN:
                self.active_input = None
            else:
                self.text_input += event.unicode

    def run(self):
        running = True

        while running:
            buttons = {}

            # Draw current state
            if self.game_state == "menu":
                buttons = self.draw_menu()
            elif self.game_state == "game":
                buttons = self.draw_game()
                if settings.time_limit > 0:
                    self.update_timer()
            elif self.game_state == "stats":
                buttons = self.draw_stats()
            elif self.game_state == "settings":
                buttons = self.draw_settings()

            # Event handling
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

                if event.type == pygame.KEYDOWN:
                    self.handle_keyboard_input(event)

                if event.type == pygame.MOUSEBUTTONDOWN:
                    mouse_pos = pygame.mouse.get_pos()

                    if self.game_state == "menu":
                        for btn_name, btn_rect in buttons.items():
                            if btn_rect.collidepoint(mouse_pos):
                                self.play_sound("click")
                                if btn_name in ["easy", "medium", "hard"]:
                                    settings.set_difficulty(btn_name)
                                    self.game_state = "game"
                                elif btn_name == "stats":
                                    self.game_state = "stats"
                                elif btn_name == "settings":
                                    self.game_state = "settings"
                                elif btn_name == "quit":
                                    running = False

                    elif self.game_state == "game":
                        for btn_name, btn_rect in buttons.items():
                            if btn_rect.collidepoint(mouse_pos) and btn_name == "back":
                                self.game_state = "menu"
                                break

                        if self.current_round:
                            for i, element in enumerate(self.current_round.elements):
                                if element.rect and element.rect.collidepoint(mouse_pos):
                                    if self.current_round.check_answer(i):
                                        time_taken = self.current_round.get_time_elapsed()
                                        self.score.add_correct(time_taken)
                                        self.message = f"Correct! +{100 + max(0, 50 - int(time_taken * 10))}"
                                        self.message_timer = 60
                                        self.play_sound("correct")
                                    else:
                                        self.message = "Wrong! Try again."
                                        self.message_timer = 60
                                        self.score.add_incorrect()
                                        self.play_sound("wrong")
                                    self.start_new_round()

                    elif self.game_state == "stats":
                        for btn_name, btn_rect in buttons.items():
                            if btn_rect.collidepoint(mouse_pos) and btn_name == "back":
                                self.game_state = "menu"

                    elif self.game_state == "settings":
                        for btn_name, btn_rect in buttons.items():
                            if btn_rect.collidepoint(mouse_pos):
                                self.play_sound("click")
                                if btn_name == "back":
                                    self.game_state = "menu"
                                elif btn_name == "name_input":
                                    self.active_input = "name"
                                elif btn_name in ["easy", "medium", "hard"]:
                                    settings.set_difficulty(btn_name)
                                elif btn_name == "palette":
                                    palettes = list(settings.color_palettes.keys())
                                    current_idx = palettes.index(settings.current_palette)
                                    settings.current_palette = palettes[(current_idx + 1) % len(palettes)]
                                elif btn_name == "sound":
                                    settings.sound_enabled = not settings.sound_enabled
                                elif btn_name.startswith("thickness_") or btn_name.startswith("type_"):
                                    settings.line_variation = True

                if event.type == pygame.MOUSEWHEEL:
                    if self.game_state == "game":
                        self.scroll_offset += event.y * 20

            pygame.display.flip()
            self.clock.tick(FPS)

        settings.save_settings()
        pygame.quit()
        sys.exit()


if __name__ == "__main__":
    game = GameUI()
    game.run()