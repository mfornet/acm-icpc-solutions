#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <algorithm>
using namespace std;

const int LOGV = 17;
const int NODOS = 40010;
const int QUER = 100010;
typedef pair<int, int> Par;

int N, Q, raiz;
int pesos[ NODOS ];
Par copiaPesos[NODOS];
vector<int> arbol[NODOS];
Par mapeo[ NODOS ];
int repetidos[NODOS];
int aplanado[NODOS*3], top = 0, aux;
int level[NODOS], P[NODOS][LOGV];
int cubeta[NODOS], respuesta = 0, res[QUER];

struct query{
	int ini, fin, pos, bloque, lca, pesoU, pesoV;
	inline bool operator<(const query& q) const {
		if (bloque != q.bloque) return bloque < q.bloque;
		return fin < q.fin;
	}
};

query queries[QUER];

void AgregarArista( int u, int v ){
	arbol[u].push_back( v );
	arbol[v].push_back( u );
}

void aplanar( int u, int p ){
	mapeo[u].first = top;
	aplanado[top] = pesos[u];
	top++;
	for( auto v : arbol[u] ){
		if( v == p ) continue;
		aplanar( v, u );
	}
	mapeo[u].second = top;
	aplanado[top] = pesos[u];
	top++;
}

void PRE(){
	for( int i = 1; ( 1 << i ) <= N; i++ ){
		for( int u = 0; u < N; u++ ){
			P[u][i] = P[P[u][i-1]][i-1];
		}
	}
}

int LCA( int p, int q ){
	if( level[p] < level[q] ) swap(p, q);
	int lg;
	for( lg = 1; (1 << lg) <= level[p]; ++lg );
	lg--;
	for( int i = lg; i >= 0; i-- ){
		if( level[p] - (1 << i) >= level[q] )
			p = P[p][i];
	}
	if( p == q ) return p;
	for( int i = lg; i >= 0; i-- ){
		if( P[p][i] != -1 && P[p][i] != P[q][i] ){
			p = P[p][i];
			q = P[q][i];
		}
	}
	return P[p][0];
}

void Busqueda( int u, int p, int l ){
	level[u] = l;
	P[u][0] = p;
	for( auto v : arbol[u] ){
		if( v == p ) continue;
		Busqueda( v, u, l+1 );
	}
}

void Agregar( int pos ){
	if( cubeta[aplanado[pos]] & 1 ){
		cubeta[aplanado[pos]] = 0;
		respuesta--;
	}
	else{
		cubeta[aplanado[pos]] = 1;
		respuesta++;
	}
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int x, y;

	cin >> N >> Q;
	raiz = sqrt( N );
	for( int i = 0; i < N; i++ ){
		cin >> copiaPesos[i].first;
		copiaPesos[i].second = i;
	}

	sort( copiaPesos, copiaPesos+N );

	int ant = copiaPesos[0].first;
	pesos[ copiaPesos[0].second ] = 1;
	int aux = 1;
	for( int i = 1; i < N; i++ ){
		if( copiaPesos[i].first != ant ) ant = copiaPesos[i].first, ++aux;
		pesos[copiaPesos[i].second] = aux;
	}

	for( int i = 1; i < N; i++ ){
		cin >> x >> y;
		AgregarArista( x-1, y-1 );
	}

	aplanar( 0, -1 );

	// for( int i = 0; i < N; i++ ){
	// 	cout << mapeo[i].first << " " << mapeo[i].second << endl;
	// }
	// cout << endl;

	// for( int i = 0; i < top; i++ ){
	// 	cout << aplanado[i] << "/" << i << " ";
	// }
	// cout << endl;

	Busqueda( 0, 0, 0 );
	PRE();
	for( int i = 0; i < Q; i++ ){
		cin >> queries[i].ini >> queries[i].fin;
		queries[i].ini--; queries[i].fin--;
		queries[i].lca = LCA( queries[i].ini, queries[i].fin );
		queries[i].pos = i;
		queries[i].pesoU = pesos[queries[i].ini];
		queries[i].pesoV = pesos[queries[i].fin];
		// cout << mapeo[ queries[i].ini ].first << " " << mapeo[ queries[i].ini ].second << endl;
		// cout << mapeo[ queries[i].fin ].first << " " << mapeo[ queries[i].fin ].second << endl;

		if( mapeo[queries[i].ini].first > mapeo[ queries[i].fin ].first  ){
			swap( queries[i].ini, queries[i].fin );
		}
		if( mapeo[ queries[i].ini ].second > mapeo[ queries[i].fin ].second ){
			queries[i].ini = mapeo[ queries[i].ini ].first;
			queries[i].fin = mapeo[ queries[i].fin ].first;
		}
		else{
			queries[i].ini = min(mapeo[ queries[i].ini ].first, mapeo[ queries[i].fin ].first);
			queries[i].fin = max(mapeo[ queries[i].ini ].second, mapeo[ queries[i].fin ].second);
		}
		//cout << queries[i].pesoU << " " << queries[i].pesoV << endl;
		// cout << queries[i].ini << " "  << queries[i].fin << endl << endl;
		queries[i].bloque = queries[i].ini/raiz;
	}

	sort( queries, queries+Q );

	int actI = 0, actD = -1, metaD, metaI;
	for( int i = 0; i < Q; i++ ){
		metaD = queries[i].fin;
		metaI = queries[i].ini;

		// cout << endl;
		// cout << queries[i].pos << " " << queries[i].ini << " " << queries[i].fin << endl; 

		while( actD < metaD ){
			//cout << "Derecha D\n";
			actD++;
			Agregar(actD);
			//cout << respuesta << endl;
		}
		while( actD > metaD ){
			//cout << "Izquierda D\n";
			Agregar( actD );
			actD--;
			//cout << respuesta << endl;
		}
		while( actI < metaI ){
			//cout << "Derecha I\n";
			Agregar(actI);
			actI++;
			//cout << respuesta << endl;
		}
		while( actI > metaI ){
			//cout << "Izquierda I\n";
			actI--;
			Agregar( actI );
			//cout << respuesta << endl;
		}

		int tmp = 0;
		set<int> conj;
		conj.insert( pesos[ queries[i].lca ] );
		conj.insert( queries[i].pesoV );
		conj.insert( queries[i].pesoU );

		for( auto it : conj ){
			if( cubeta[it] == 0 ) tmp++;
		}

		res[ queries[i].pos ] = respuesta+tmp;
	}

	for( int i = 0; i < Q; i++ ){
		cout << res[i] << '\n';
	}

	return 0;
}