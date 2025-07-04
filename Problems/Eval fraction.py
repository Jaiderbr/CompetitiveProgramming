# 1/2+1/3 -> 5/6
import math
import sys
from fractions import Fraction
import re
input = sys.stdin.readline
write = sys.stdout.write
def print(x): write(str(x) + '\n')

def main():
    s = input().strip()
    while s != "":        
        s_eval = re.sub(r'(\d+)/(\d+)', r'Fraction(\1,\2)', s)
        ans = eval(s_eval, {'Fraction': Fraction})
        x = ans        
        y = f"{x.numerator}/{x.denominator}"
        print(y)
        s = input().strip()

if __name__ == '__main__':
    main()
