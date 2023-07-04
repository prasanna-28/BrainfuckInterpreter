lexicon = {'+','-','>','<','.',',','[',']'}

error_occurred = False

def error(message):
    print("\033[91m {}\033[00m" .format(message))
    global error_occurred
    error_occurred = True

class brainfuck:
    def __init__ (self,file):
        self.bytecells = [0] * 30_000
        self.ptr = 0
        self.pos = 0
        self.stack = []
        with open(file, 'r') as file:
            self.content = file.read()
    
    def output(self): print(chr(self.bytecells[self.ptr]), end = '')
    
    def input(self): self.bytecells[self.ptr] = ord(input('\n'))

    def increment(self): self.bytecells[self.ptr] = (self.bytecells[self.ptr] + 1) % 256

    def decrement(self): self.bytecells[self.ptr] = (self.bytecells[self.ptr] - 1) % 256

    def up(self): self.ptr = (self.ptr + 1) % 30_000
    
    def down(self): self.ptr = (self.ptr - 1) % 30_000

    def parser(self, i):
        if i == '+': self.increment()
        if i == '-': self.decrement()
        if i == '>': self.up()
        if i == '<': self.down()
        if i == '.': self.output()
        if i == ',': self.input()

    def execute(self):
        global error_occurred
        while self.pos < len(self.content) and not error_occurred:
            command = self.content[self.pos]
            if command == '[':
                self.stack.append(self.pos)
            elif command == ']':
                if len(self.stack) == 0:
                    error("Closing ']' encountered without previous '['")
                elif self.bytecells[self.ptr] != 0:
                    self.pos = self.stack[-1]
                else:
                    self.stack.pop()
            else:
                self.parser(command)
            self.pos += 1

bf = brainfuck('main.bf')
bf.execute()
