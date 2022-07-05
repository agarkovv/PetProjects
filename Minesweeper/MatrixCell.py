import tkinter as tk

from ViewCell import ViewCell


class MatrixCell(tk.Frame):
    def __init__(self, size, **kw):
        super().__init__(**kw)
        self.cells = [[ViewCell(row, col, master=self) for col in range(size)] for row in range(size)]
        self.pack(side='bottom')
