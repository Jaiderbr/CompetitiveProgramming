import sys
from math import gcd, lcm, comb, factorial, sqrt, ceil, floor, log2, log10, sin, cos, tan, pi, perm
from itertools import permutations, combinations, product
from collections import deque, defaultdict, Counter
import heapq

# Entrada y salida rapidas
input = sys.stdin.readline
print = sys.stdout.write

# Limite de recursion
sys.setrecursionlimit(10**6)

# Constantes

MOD = 10**9 + 7
INF = 10**18
dirs4 = [(1,0), (-1,0), (0,1), (0,-1)]
dirs8 = [(1,0), (-1,0), (0,1), (0,-1), (1,1), (1,-1), (-1,1), (-1,-1)]

def modinv(a): return pow(a, -1, MOD)  

# n, m = map(int, input().split())
# arr = list(map(int, input().split()))

#estructuras

n, m = 5, 5
lista_1d = [0] * n
lista_2d = [[0] * m for _ in range(n)]
# Aplanar listas 2D en 1D
lista_flat = [0] * (n * m)

# Enumerar
for i, val in enumerate(lista_1d):
    pass
# Pilas, colas y heaps
stack = []
stack.append(1)
stack.pop()

q = deque()
q.append(1)
x = q.popleft()

pq = []
heapq.heappush(pq, 3)
heapq.heappush(pq, 1)
heapq.heappush(pq, 2)
min_val = heapq.heappop(pq)
max_val = -heapq.heappop(pq)  # Usar valores negativos (pq,-3) para max-heap

#set map

s = set()
s.add(5)
if 5 in s:
    s.remove(5)

d = {}
d[1] = 'a'
for k, v in d.items():
    pass

# defaultdict y Counter
graph = defaultdict(list)
freq = Counter([1, 2, 2, 3])

# Obtener valor ASCII
ord('A')  # 65
chr(65)   # 'A'

x = 36
y = 48
g = gcd(x, y)
l = lcm(x, y)

# combinatoria
n, k = 5, 2
c = comb(n, k)
f = factorial(n)

# raices, redondeos y logaritmos
r = sqrt(16)
up = ceil(3.1)
down = floor(3.9)
lg2 = log2(8)
lg10 = log10(1000)

# trigonometria
ang = pi / 4
seno = sin(ang)
coseno = cos(ang)
tangente = tan(ang)


# combinaciones y permutaciones

nums = [1, 2, 3]
for p in permutations(nums):
    pass

for c in combinations(nums, 2):
    pass

for p in product([0,1], repeat=3): #todas combinaciones con repetición de los elementos [0, 1], tomando 3 posiciones.
    pass #(0,0,0), (0,0,1), (0,1,0), (0,1,1), (1,0,0), (1,0,1), (1,1,0), (1,1,1)

#Salida rapida de muchas lineas
outputs = []
for i in range(5):
    outputs.append(str(i))
print('\n'.join(outputs))

# ------------------------------
# sys.stdin = open("input.in", "r")
# sys.stdout = open("output.out", "w")
