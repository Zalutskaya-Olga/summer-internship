import json
import os
from datetime import datetime
from typing import List, Dict
import matplotlib.pyplot as plt
import pandas as pd


class GameStatistics:
    def __init__(self):
        self.filename = "game_stats.json"
        self.stats: List[Dict] = []
        self.load_stats()

    def load_stats(self):
        if os.path.exists(self.filename):
            with open(self.filename, 'r') as f:
                self.stats = json.load(f)

    def save_stats(self):
        with open(self.filename, 'w') as f:
            json.dump(self.stats, f)

    def add_session(self, score: int, correct: int, incorrect: int, difficulty: str):
        session = {
            "date": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            "score": score,
            "correct": correct,
            "incorrect": incorrect,
            "accuracy": correct / (correct + incorrect) * 100 if (correct + incorrect) > 0 else 0,
            "difficulty": difficulty
        }
        self.stats.append(session)
        self.save_stats()

    def get_best_score(self, difficulty: str = None) -> int:
        if not self.stats:
            return 0

        if difficulty:
            scores = [s["score"] for s in self.stats if s["difficulty"] == difficulty]
        else:
            scores = [s["score"] for s in self.stats]

        return max(scores) if scores else 0

    def get_average_accuracy(self, difficulty: str = None) -> float:
        if not self.stats:
            return 0.0

        if difficulty:
            accuracies = [s["accuracy"] for s in self.stats if s["difficulty"] == difficulty]
        else:
            accuracies = [s["accuracy"] for s in self.stats]

        return sum(accuracies) / len(accuracies) if accuracies else 0.0

    def plot_progress(self):
        if not self.stats:
            print("No statistics to plot")
            return

        df = pd.DataFrame(self.stats)
        df['date'] = pd.to_datetime(df['date'])
        df = df.sort_values('date')

        plt.figure(figsize=(10, 5))

        plt.subplot(1, 2, 1)
        plt.plot(df['date'], df['score'], 'b-')
        plt.title('Score Over Time')
        plt.xlabel('Date')
        plt.ylabel('Score')

        plt.subplot(1, 2, 2)
        plt.plot(df['date'], df['accuracy'], 'g-')
        plt.title('Accuracy Over Time')
        plt.xlabel('Date')
        plt.ylabel('Accuracy (%)')

        plt.tight_layout()
        plt.show()

    def reset_stats(self):
        self.stats = []
        if os.path.exists(self.filename):
            os.remove(self.filename)