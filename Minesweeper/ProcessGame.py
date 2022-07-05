import tkinter as tk
import tkinter.messagebox as mb

from MatrixCell import MatrixCell
from UnitField import UnitField
from ViewCell import ViewCell


class ProcessGame:
    def __init__(self, size, count_mines):
        self.size = size
        self.count_mines = count_mines
        self.mf = UnitField(size, count_mines)
        self.matrix = MatrixCell(size)
        self.lbl = tk.Label(text=f'мин = {self.mf.count_mines} | флагов = {self.mf.count_flags}', bg='light green')
        self.lbl.pack(side='top')
        for i in range(self.mf.size):
            for j in range(self.mf.size):
                self.matrix.cells[i][j].bind_command('<ButtonRelease - 1>', self.on_right)
                self.matrix.cells[i][j].bind_command('<ButtonRelease - 2>', self.on_middle)
                self.matrix.cells[i][j].bind_command('<ButtonRelease - 3>', self.on_left)

    def on_right(self, row, col):
        cell = self.matrix.cells[row][col]
        value = self.mf.show_data_from_unit(row, col)
        if value is None:
            return
        if value == 'mine':
            self.show_mine(cell)
            self.show_game_over()
            return True
        else:
            if value == 0:
                self.show_zero(cell)
                self.on_middle(row, col)
            else:
                self.show_value(cell, value)

    def on_left(self, row, col):
        cell = self.matrix.cells[row][col]
        value, count_flags = self.mf.put_flag(row, col)
        if value is None:
            return
        self.lbl['text'] = f'min = {self.mf.count_mines} | flags = {count_flags}'
        if value == 'flag':
            self.show_flag(cell)
        elif value == 'opened':
            cell.set_option_default()
        elif value == 'win':
            self.show_flag(cell)
            self.show_win()

    def on_middle(self, row, col):
        for i in range(row - 1, row + 2):
            if 0 <= i < self.mf.size:
                for j in range(col - 1, col + 2):
                    if 0 <= j < self.mf.size:
                        if self.on_right(i, j):
                            return

    def show_mine(self, cell: ViewCell):
        cell.set_color('red')

    def show_value(self, cell: ViewCell, value):
        cell.set_text(value)
        cell.set_color('brown')

    def show_zero(self, cell):
        cell.set_color('green')

    def show_flag(self, cell):
        cell.set_color('yellow')

    def show_win(self):
        mb.showinfo("Well done", "You win!")
        self.matrix.destroy()
        self.lbl.destroy()
        self.__init__(self.size + 1, self.count_mines + 5)

    def show_game_over(self):
        mb.showinfo("Boom", "You lose")
        self.matrix.destroy()
        self.lbl.destroy()
        self.__init__(self.size, self.count_mines)
