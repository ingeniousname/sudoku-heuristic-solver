import numpy as np
import subprocess
import os

if not os.path.exists('sudoku.csv'):
    pass
#    sys.subprocess('wget ')
quizzes = []
solutions = []
for i, line in enumerate(open('sudoku.csv', 'r').read().splitlines()[1:]):
    quiz, solution = line.split(",")
    quizzes.append(quiz)
    solutions.append(solution)

for i in range(1000):
    print(quizzes[i])
    output = subprocess.check_output(['./sudoku/sudoku', quizzes[10 + i]], text=True)
    print(output)
