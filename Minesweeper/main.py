from MainWindow import MainWindow
from ProcessGame import ProcessGame

import configparser

def main():
    config = configparser.ConfigParser()
    config.read("settings.ini")

    window = MainWindow()
    ProcessGame(int(config["Minesweeper"]["height"]), int(config["Minesweeper"]["width"]))
    window.mainloop()


if __name__ == '__main__':
    main()
