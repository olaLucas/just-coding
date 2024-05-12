class Ponto:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def setx(self, x):
        self.x = x

    def sety(self, y):
        self.y = y

    def get(self):
        return (x, y)

    def __repr__(self):
        return f'Ponto({self.x}, {self.y})'

    def __str__(self):
        return f'x = {self.x}, y = {self.y}'
