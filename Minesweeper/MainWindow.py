import tkinter as tk


class MainWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title('Minesweeper')
        self.resizable(width=0, height=0)
        self.config(bg='light green')
