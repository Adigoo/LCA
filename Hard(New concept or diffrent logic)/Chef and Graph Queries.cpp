#include <bits/stdc++.h>

using namespace std;

const int N = 2e5+5;

int p[N], ran[N], kolkomp;
vector <pair <pair <int, int>, int>> otkat = {};


int get( int ver ) {
    if( p[ver] == ver ) {
        return ver;
    } else {
        return get( p[ver] );
    }
}

int unite( int a, int b ) {
    a = get( a );
    b = get( b );
    if( a != b ) {
        kolkomp--;
        int flag = 0;

        if( ran[a] < ran[b] ) {
            swap( a, b );
        }

        p[b] = a;

        if( ran[a] == ran[b] ) {
            ran[a]++;
            flag++;
        }
        otkat.push_back( {{a, b}, flag} );

        return 1;
    } else {
        return 0;
    }
}

void otkatit() {

    int a = otkat[otkat.size()-1].first.first, b = otkat[otkat.size()-1].first.second;

    p[b] = b;

    if( otkat[otkat.size()-1].second ) {
        ran[a]--;
    }

    kolkomp++;

    otkat.pop_back();
}

int main()
{
    ios_base::sync_with_stdio(0);
    //freopen( "input.txt", "r", stdin );

    int testkol;

    cin >> testkol;

    for( int testnum = 0; testnum < testkol; testnum++ ) {

        int n, m, q, inpf, inps, globin = 0, locin = 0, razm, ost = 0;

        cin >> n >> m >> q;

        razm = sqrt(m);
        if( m % razm ) {
            ost++;
        }
        vector <pair <pair <int,int>, int>> razdreb[m/(razm)+ost];
        vector <pair <int,int>> reb = {};
        vector <int> ans = {};

        for( int i = 0; i < m / razm + ost; i++ ) {
            razdreb[i] = {};
        }

        for( int i = 1; i <= n; i++ ) {
            p[i] = i;
            ran[i] = 1;
        }

        for( int i = 0; i < m; i++ ) {
            cin >> inpf >> inps;
            reb.push_back( {inpf, inps} );
        }

        for( int i = 0; i < q; i++ ) {
            ans.push_back( 0 );

            cin >> inpf >> inps;
            inpf--;
            inps--;

            if( razm == 1 ) {
                razdreb[inpf].push_back( {{inps, inpf}, i} );
            } else {
                razdreb[inpf/razm].push_back( {{inps, inpf}, i} );
            }
        }

        for( int i = 0; i < m / razm + ost; i++ ) {
            if( razdreb[i].size() ) {
                sort( razdreb[i].begin(), razdreb[i].end() );
            }
        }

        for( int i = 0; i < m / razm + ost; i++ ) {

            if( razdreb[i].size() ) {
                kolkomp = n;
                globin = 0;

                while( globin < razdreb[i].size() && razdreb[i][globin].first.first / razm == i ) {
                    int l = razdreb[i][globin].first.second, r = razdreb[i][globin].first.first;

                    for( int in = l; in <= r; in++ ) {
                        unite( reb[in].first, reb[in].second );
                    }

                    ans[razdreb[i][globin].second] = kolkomp;

                    while( otkat.size() ) {
                        otkatit();
                    }

                    globin++;
                }

                locin = razm * (i + 1);

                while( globin < razdreb[i].size() ) {
                    int kolotkat = 0;

                    for( ; locin <= razdreb[i][globin].first.first; locin++ ) {
                        unite( reb[locin].first, reb[locin].second );
                    }

                    for( int in = razdreb[i][globin].first.second; in < razm * (i + 1); in++ ) {
                        kolotkat += unite( reb[in].first, reb[in].second );
                    }

                    ans[razdreb[i][globin].second] = kolkomp;

                    while( otkat.size() && kolotkat ) {
                        otkatit();

                        kolotkat--;
                    }

                    globin++;
                }

                while( otkat.size() ) {
                    otkatit();
                }
            }
        }

        for( auto i : ans ) {
            cout << i << '\n';
        }
    }

    return 0;
}
