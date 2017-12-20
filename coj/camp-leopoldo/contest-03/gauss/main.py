from fractions import Fraction as F
from pprint import pprint as p

def gauss(A):
    n = len( A )
    # p( A )
    for row in xrange(n):
        piv = row
        while A[piv][row] == F(0):
            piv += 1

        if piv > row:
            A[piv], A[row] = A[row], A[piv]
    
        for nrow in xrange(row + 1, n):
            f = A[nrow][row] / A[row][row]

            for col in xrange(row, n + 1):
                A[nrow][col] = A[nrow][col] - A[row][col] * f

    x = [0] * n

    for i in xrange(n - 1, -1, -1):
        value = A[i][n]
        for j in xrange(i + 1, n):
            value -= x[j] * A[i][j]
        value /= A[i][i]
        x[i] = value

    return x

def solve():
    n, g, k = map( int, raw_input().split() )
    g -= 1

    adj = [[] for _ in xrange(n)]
    dist = [[0 if u == v else 1 for u in xrange(n)] for v in xrange(n)]

    for _ in xrange(k):
        u, v = map( int, raw_input().split() )
        u -= 1
        v -= 1
        adj[u].append( v )
        adj[v].append( u )

        dist[u][v] = 0
        dist[v][u] = 0

    for k in xrange(n):
        for i in xrange(n):
            for j in xrange(n):
                dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] )
    
    if dist[0][g] == 1:
        print "NO ROUTE"
        return

    node_id = [-1] * n
    nodes = []
    total = 0

    for u in xrange(n):
        if dist[0][u] == 0:
            node_id[u] = total
            nodes.append( u )
            total += 1

    mat = [[F(0) for _ in xrange(total + 1)] for _ in xrange(total)]

    for i in xrange(total):
        mat[i][i] = -F(1)
        if i == node_id[g]: continue

        u = nodes[i]

        f = F(1, len( adj[u] ))
        for v in adj[u]:
            mat[i][ node_id[v] ] = f
        mat[i][total] = -F(1)

    # p(mat)

    x = gauss( mat )

    # p(x)

    print round( float(x[0]) + 1e-5, 1 )

if __name__ == '__main__':
    n = input()

    for i in xrange(n):
        solve()
