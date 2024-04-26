import subprocess
import os
import random
import math
import argparse

n_correct = 0
n_incorrect = 0
n_overall = 1000000
curr_tested_num = 0
idx = random.randint(0, n_overall)
n = 200
quizzes = []
solutions = []
program_path = './out/sudoku/sudoku'
input_path = './sudoku.csv'

parser = argparse.ArgumentParser('test_correctness.py')
parser.add_argument('-n',  help="Number of tested samples")
parser.add_argument('-p', '--program_path', help="Path to the sudoku executable")
parser.add_argument('-i', '--input_path', help="Path to the sudoku.csv file")

args = parser.parse_args()
if args.n:
    n = int(args.n)
if args.program_path:
    program_path = args.program_path
if args.input_path:
    input_path = args.input_path

n_ten_precent = math.ceil(n / 10)

if not os.path.exists(input_path):
    print('Database sudoku.csv not found, you should download it from:')
    print('https://drive.google.com/file/d/1nHPfq_IoLxIyamYs8v4gcaFsoXpDChQ7/view?usp=sharing')
    print('Originally from https://www.kaggle.com/datasets/bryanpark/sudoku')
    exit(-1)

for i, line in enumerate(open(input_path, 'r').read().splitlines()[1:]):
    quiz, solution = line.split(",")
    quizzes.append(quiz)
    solutions.append(solution)

for i in range(n):
    output = subprocess.check_output([program_path, quizzes[idx]], text=True)
    output = output.replace(" ", "").replace("\n", "")
    if output == solutions[idx]:
        n_correct += 1
    else:
        n_incorrect += 1
    idx = (idx + 1) % n_overall
    curr_tested_num += 1
    if curr_tested_num % n_ten_precent == 0:
        print(f'Testing... [{curr_tested_num}/{n}]')

print('Test done')
print(f'Correct: {n_correct}/{n} ({n_correct / n * 100}%)')
print(f'Incorrect: {n_incorrect}/{n} ({n_incorrect / n * 100}%)')
