import tkinter as tk


class ViewCell(tk.Label):
    def __init__(self, row, col, **kw):
        super().__init__(width=3, bg='grey', relief='raised', fg='yellow', font="Arial 12 bold", **kw)
        self.grid(row=row, column=col)
        self.coords = (row, col)

    def set_color(self, color):
        self.config(bg=color)

    def set_text(self, text):
        self.config(text=text)

    def set_option_default(self):
        self.config(text='', bg='grey')

    def bind_command(self, event, command):
        self.bind(event, lambda e: command(*self.coords))
