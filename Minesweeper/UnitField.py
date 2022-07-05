import random as rd

from Unit import Unit


class UnitField:
    def __init__(self, size, count_mines):
        self.size = size
        self.count_mines = count_mines
        self.mines_coords = self.generate_place()
        self.cells = self.generate_field()
        self.put_mines_into_fields()
        self.count_mines_cleared = 0
        self.count_flags = self.count_mines

    def print_units(self):
        for row in self.cells:
            print()
            for col in row:
                print("@" if col.mined else "*", end='\t')

    def generate_place(self):
        coords = set()
        while len(coords) != self.count_mines:
            coords.add((rd.randint(0, self.size - 1), rd.randint(0, self.size - 1)))
        return coords

    def generate_field(self):
        matrix = [[Unit() for _ in range(self.size)] for _ in range(self.size)]
        return matrix

    def put_mines_into_fields(self):
        for row, col in self.mines_coords:
            self.cells[row][col].mined = True

    def show_mines_around(self, row, col):
        value = 0
        for i in range(row - 1, row + 2):
            if self.size > i >= 0:
                for j in range(col - 1, col + 2):
                    if self.size > j >= 0:
                        value += int(self.cells[i][j].mined)
        return value

    def show_data_from_unit(self, row, col):
        cell = self.cells[row][col]
        if cell.opened:
            return
        if not cell.flaged:
            self.cells[row][col].opened = True
            if cell.mined:
                return 'mine'
            else:
                return self.show_mines_around(row, col)

    def put_flag(self, row, col):
        cell = self.cells[row][col]
        if cell.opened:
            return None, None
        elif not cell.flaged and self.count_flags > 0:
            self.cells[row][col].flaged = True
            self.count_flags -= 1
            if cell.mined:
                self.count_mines_cleared += 1
                if self.count_mines_cleared == self.count_mines:
                    return 'win', self.count_flags
            return 'flag', self.count_flags
        elif cell.flaged:
            self.cells[row][col].flaged = False
            self.count_flags += 1
            if cell.mined:
                self.count_mines_cleared -= 1
            return 'opened', self.count_flags
        else:
            return None, None
