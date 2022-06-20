#include <bits/stdc++.h>

using namespace std;

ifstream f;
ofstream g;

class Graf {

    int noduri, muchii;

    vector< vector<int> > lista;

    public:

    Graf(int numar_noduri, int numar_muchii, int aux);

    Graf(int numar_noduri, int numar_muchii);

    Graf(int numar_noduri);

    Graf(int numar_noduri, int numar_muchii, string apm);

    Graf();

    void out();

    void bfs(int start);

    void dfs(vector<bool> &vizitat, int start);

    void biconex();

    void dfs_biconex(int start, vector<bool> &vizitat, int niv, vector<int> &nivel, vector<int> &nivel_intoarcere, vector<int> &parinte, vector < pair <int, int> > &st, int &contor, vector<set<int>> &componeneteBiconexe);

    void componenteTareConexe(int nod, vector<int> &rezultat, vector <int> &nivel, vector <int> &nivelMinim, vector <bool> &stiva, stack <int> &st, vector < vector <int> > &output, int adancime);

    void sortaret(int start, vector<bool> &vizitat, vector<int> &output);

    bool Havel_Hakimi(int n, vector<int> &grade);

    void critical();

    void dfs_critical(int nod, int nodAnterior, vector<int> &nivel, vector<int> &nivelMinim, vector< vector <int> > &output, int adancime);

    void apm();

    int apm_parinte(int parinte[], int nod);

    void disjoint();

    void uniune(vector<int> &parinte, vector<int> &rang, int x, int y);

    int cauta(vector<int> &parinte, int  x);

    void dijkstra();

    void bellmanford();

    void maxflow();

    bool maxflow_bfs(vector<int> &tata, vector<int> &vizitat, vector<vector<int>> capacitate, vector<vector<int>> &flux);

    void royfloyd();

    void darb();

    void bfs_darb(int start, vector<int>& diametru, int& diametruMaxim, int& nodulUrmator);

    int euler();

    void hamilton();

    void cuplaj();

    bool cuplaje(int index, vector<int> &stanga, vector<int> &dreapta, vector<bool> &vizitat);
};

Graf :: Graf()
{
    noduri = 0;
    muchii = 0;
    lista.resize(0);
}

void Graf :: out ()
{
    g << noduri << " " << muchii << endl;

    for(int i = 0; i < noduri + 1; i++)
    {
        g << i << " : ";
        for(unsigned int j = 0 ; j < lista[i].size(); j++)
            g << lista[i][j] << " ";
        g << endl;
    }

}

Graf :: Graf (int numar_noduri, int numar_muchii, int aux)
{
    noduri = numar_noduri;
    muchii = numar_muchii;

    int nod_1, nod_2;

    lista.resize(numar_noduri + 1);

    for(int i = 1; i <= numar_muchii; i++)
    {
        f >> nod_1 >> nod_2;

        lista[nod_1].push_back(nod_2);
    }
}

Graf :: Graf (int numar_noduri, int numar_muchii)
{
    noduri = numar_noduri;
    muchii = numar_muchii;

    int nod_1, nod_2;

    lista.resize(numar_noduri + 1);

    for(int i = 1; i <= numar_muchii; i++)
    {
        f >> nod_1 >> nod_2;

        lista[nod_1].push_back(nod_2);
        lista[nod_2].push_back(nod_1);
    }
}

Graf :: Graf (int numar_noduri)
{
    noduri = numar_noduri;

    int nod_1, nod_2;

    lista.resize(numar_noduri + 1);

    while(f >> nod_1 >> nod_2)
    {
        lista[nod_1].push_back(nod_2);
        lista[nod_2].push_back(nod_1);
    }
}

void Graf :: bfs(int start)
{
    int distanta[noduri + 1];

    for(int index = 1; index <= noduri; index++)
        distanta[index] = -1;

    bool vizitat[noduri + 1] = {false};

    queue<int> q;

    q.push(start);

    distanta[start] = 0;

    vizitat[start] = true;

    while(!q.empty())
    {
        int nod = q.front();
        q.pop();
        for(unsigned int index = 0; index < lista[nod].size(); index++)
            if(vizitat[lista[nod][index]] == false)
            {
                q.push(lista[nod][index]);
                vizitat[lista[nod][index]] = true;
                distanta[lista[nod][index]] = distanta[nod] + 1;
            }
    }

    for(int secondIndex = 1; secondIndex <= noduri; secondIndex++)
        g << distanta[secondIndex] << " ";
}

void Graf :: dfs(vector<bool> &vizitat, int start)
{
    vizitat[start] = true;
    for(unsigned int index = 0; index < lista[start].size(); index++)
        if(vizitat[lista[start][index]] == false)
            dfs(vizitat, lista[start][index]);
}

void Graf :: biconex()
{
    int contor = 0;

    vector<bool> vizitat;
    vizitat.resize(noduri + 1);

    vector<int> nivel;
    vector<int> nivel_intoarcere;
    vector<int> parinte;
    vector< set <int> > componenteBiconexe;

    nivel.resize(noduri + 1);
    nivel_intoarcere.resize(noduri + 1);
    parinte.resize(noduri + 1);

    vector < pair<int, int>> st;

    for(int index = 1; index <= noduri; index++)
    {
        nivel[index] = 0;
        nivel_intoarcere[index] = 0;
        vizitat[index] = false;
    }


    for(int index = 1; index <= noduri; index++)
    {
        if(vizitat[index] == false)
        {
            dfs_biconex(index, vizitat, 1, nivel, nivel_intoarcere, parinte, st, contor, componenteBiconexe);

            int j = 0;

            set<int> set_aux;

            while(!st.empty())
            {
                j = 1;
                set_aux.insert(st.back().first);
                set_aux.insert(st.back().second);
                st.pop_back();
            }

            componenteBiconexe.push_back(set_aux);

            if(j == 1)
            {
                contor++;
            }
        }
    }

    g << contor << endl;

    for(unsigned int index = 0; index < componenteBiconexe.size(); index++)
    {
        set<int>::iterator it;

        for(it = componenteBiconexe[index].begin(); it != componenteBiconexe[index].end(); it++)
            g << *it << " ";
        g << endl;
    }
}

void Graf :: dfs_biconex(int start, vector<bool> &vizitat, int niv, vector<int> &nivel, vector<int> &nivel_intoarcere, vector<int> &parinte, vector < pair < int, int> > &st, int &contor, vector<set<int>> &componenteBiconexe)
{

    vizitat[start] = true;
    nivel[start] = nivel_intoarcere[start] = niv;

    int copil = 0;

    for(unsigned int index = 0; index < lista[start].size(); index++)
    {
        int nod = lista[start][index];

        if(vizitat[nod] == false)
            {
                copil++;
                parinte[nod] = start;

                pair<int, int> aux;
                aux.first = start;
                aux.second = nod;

                st.push_back(aux);

                dfs_biconex(nod, vizitat, niv + 1, nivel, nivel_intoarcere, parinte, st, contor, componenteBiconexe);

                nivel_intoarcere[start] = min(nivel_intoarcere[start], nivel_intoarcere[nod]);

                if( (nivel[start] == 1 && copil > 1) || (nivel[start] > 1 && nivel_intoarcere[nod] >= nivel[start]) )
                {
                    set<int> set_aux;

                    while(st.back().first != start || st.back().second != nod)
                    {
                        set_aux.insert(st.back().first);
                        set_aux.insert(st.back().second);
                        st.pop_back();
                    }


                    set_aux.insert(st.back().first);
                    set_aux.insert(st.back().second);

                    componenteBiconexe.push_back(set_aux);

                    st.pop_back();
                    contor++;
                }
            }
        else if(nod != parinte[start])
        {
            nivel_intoarcere[start] = min(nivel_intoarcere[start], nivel[nod]);
            if(nivel[nod] < nivel[start])
            {
                pair<int, int> aux;
                aux.first = start;
                aux.second = nod;

                st.push_back(aux);
            }
        }
    }
}

void Graf :: componenteTareConexe(int nod, vector<int> &rezultat, vector <int> &nivel, vector <int> &nivelMinim, vector <bool> &stiva, stack <int> &st, vector < vector <int> > &output, int adancime)
{
    nivel[nod] = adancime;
    nivelMinim[nod] = adancime;

    st.push(nod);

    stiva[nod] = true;

    for(unsigned int index = 0; index < lista[nod].size(); index++)
    {
        if(nivel[lista[nod][index]] == -1)
        {
            componenteTareConexe(lista[nod][index], rezultat, nivel, nivelMinim, stiva, st, output, adancime + 1);
            nivelMinim[nod] = min(nivelMinim[nod], nivelMinim[lista[nod][index]]);
        }
        else if(stiva[lista[nod][index]])
            nivelMinim[nod] = min(nivelMinim[nod], nivelMinim[lista[nod][index]]);
    }

    if(nivel[nod] == nivelMinim[nod])
    {
        rezultat.clear();
        int node;
        do
        {
            rezultat.push_back(node = st.top());
            st.pop();
            stiva[node] = false;
        }
        while(node != nod);

        output.push_back(rezultat);
    }
}

void Graf :: sortaret(int start, vector<bool> &vizitat, vector<int> &output)
{
    vizitat[start] = true;

    for(unsigned int index = 0; index < lista[start].size(); index++)
        if(vizitat[lista[start][index]] == false)
            sortaret(lista[start][index], vizitat, output);

    output.push_back(start);
}

bool Graf :: Havel_Hakimi(int n, vector<int> &grade)
{
    while(true)
    {
        sort(grade.begin(), grade.end(), greater<>());

        if(grade[0] == 0)
            return true;

        unsigned int nod = grade[0];

        grade.erase(grade.begin() + 0);

        if(nod > grade.size())
            return false;

        for(unsigned int index = 0; index < nod; index++)
        {
            grade[index]--;

            if(grade[index] < 0)
                return false;
        }
    }
}

void Graf :: critical()
{
    vector<int> nivel;
    vector<int> nivelMinim;
    vector< vector <int> > output;

    nivel.resize(noduri);
    nivelMinim.resize(noduri);

    int adancime = 1;

    dfs_critical(0, -1, nivel, nivelMinim, output, adancime);

    for(unsigned int index = 0; index < output.size(); index++)
    {
        for(unsigned int secondIndex = 0; secondIndex < output[index].size(); secondIndex++)
            g << output[index][secondIndex] << " ";
        g << endl;
    }
}

void Graf :: dfs_critical(int nod, int nodAnterior, vector<int> &nivel, vector<int> &nivelMinim, vector< vector <int> > &output, int adancime)
{
    nivel[nod] = nivelMinim[nod] = adancime;

    for(unsigned int index = 0; index < lista[nod].size(); index++)
    {
        int nodUrmator = lista[nod][index];

        if (nivel[nodUrmator] == 0)
        {
            dfs_critical(nodUrmator, nod, nivel, nivelMinim, output, adancime + 1);
            nivelMinim[nod] = min(nivelMinim[nod], nivelMinim[nodUrmator]);
        }
        else
            if (nodUrmator != nodAnterior)
                nivelMinim[nod] = min(nivelMinim[nod], nivel[nodUrmator]);

        if (nivelMinim[nodUrmator] > nivel[nod])
            output.push_back({nod, nodUrmator});
        }
}

void Graf :: apm()
{
    int rezultat = 0, cost, x, y, parinte[noduri + 1], rang[noduri + 1], numar_muchii = 0;  // parinte[i] - parintele lui i | rang[i] - rangul lui i (inaltime)

    f >> noduri >> muchii;

    vector<pair<int, pair<int, int>>> edges;
    vector<pair<int, int>> rez;

    edges.resize(noduri + 1);

    for(int index = 0; index < noduri + 1; index++)
    {
        parinte[index] = 0;
        rang[index] = 1;
    }

    for(int index = 0; index < muchii; index++)
    {
        f >> x >> y >> cost;
        edges.push_back(make_pair(cost, make_pair(x, y)));
    }

    sort(edges.begin(), edges.end());

    for(unsigned int index = 0; index < edges.size() && numar_muchii != noduri - 1; index++)
    {
        x = edges[index].second.first;
        y = edges[index].second.second;
        cost = edges[index].first;

        int parinte_x = apm_parinte(parinte, x);
        int parinte_y = apm_parinte(parinte, y);
        int aux;

        if(parinte_x != parinte_y)
        {
            numar_muchii++;

            rez.push_back(make_pair(x, y));

            rezultat += cost;

            int rang_x = rang[parinte_x], rang_y = rang[parinte_y];

            if(rang_x < rang_y)
            {
                parinte[parinte_x] = parinte_y;
                rang[parinte_y] = max(rang_y, rang_x + 1);
            }
            else
            {
                parinte[parinte_y] = parinte_x;
                rang[parinte_x] = max(parinte_x, parinte_y + 1);
            }
        }

        while(x != parinte_x)
        {
            aux = parinte[x];
            parinte[x] = parinte_x;
            x = aux;
        }

        while(y != parinte_y)
        {
            aux = parinte[y];
            parinte[y] = parinte_y;
            y = aux;
        }

    }

    g << rezultat << endl << noduri - 1 << endl;

    for(unsigned int index = 0; index < rez.size(); index++)
        g << rez[index].first << " " << rez[index].second << endl;
}

int Graf :: apm_parinte(int parinte[], int nod)
{
    if(parinte[nod] == 0)
        return nod;

    return apm_parinte(parinte, parinte[nod]);
}

void Graf :: disjoint()
{
    int numar_noduri, numar_comenzi, op, x, y;

    f >> numar_noduri >> numar_comenzi;

    vector<int> rang;
    vector<int> parinte;

    rang.resize(numar_noduri + 1);
    parinte.resize(numar_noduri + 1);

    for(int index = 0; index < numar_noduri + 1; index++)
    {
        parinte[index] = index;
        rang[index] = 0;
    }

    for(int index = 0; index < numar_comenzi; index++)
    {
        f >> op >> x >> y;

        if(op == 1)
        {
            uniune(parinte, rang, x, y);
        }
        else if(op == 2)
            {
                if(cauta(parinte, x) == cauta(parinte, y) )
                    g << "DA\n";
                else
                    g << "NU\n";
            }
    }
}

void Graf :: uniune(vector<int> &parinte, vector<int> &rang, int x, int y)
{
    int xset = cauta(parinte, x);
    int yset = cauta(parinte, y);

    if(xset == yset)
        return;

    if(rang[xset] < rang[yset])
        parinte[xset] = yset;
    else if(rang[xset] > rang[yset])
            parinte[yset] = xset;
        else
        {
            parinte[yset] = xset;
            rang[xset] = rang[xset] + 1;
        }
}

int Graf :: cauta(vector<int>  &parinte, int x)
{
    if(parinte[x] != x)
        parinte[x] = cauta(parinte, parinte[x]);

    return parinte[x];
}

void Graf :: dijkstra()
{
    int x, y, cost;

    f >> noduri >> muchii;

    vector<vector<pair<int, int>>> edges;
    vector<int> distanta;
    vector<bool> ales;

    edges.resize(noduri + 1);
    distanta.resize(noduri + 1);
    ales.resize(noduri + 1);

    for(int index = 0; index < muchii; index++)
    {
        f >> x >> y >> cost;
        edges[x].push_back(make_pair(y, cost));
    }

    for(int index = 0; index < noduri + 1; index++)
    {
        distanta[index] = INT_MAX;
        ales[index] = false;
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distanta[1] = 0;

    pq.push(make_pair(0, 1));

    while(!pq.empty())
    {
        int nod = pq.top().second;

        pq.pop();

        if(ales[nod])
            continue;

        ales[nod] = true;

        for(unsigned int index = 0; index < edges[nod].size(); index++)
        {
            int nod_2 = edges[nod][index].first;
            cost = edges[nod][index].second;

            if(distanta[nod_2] > distanta[nod] + cost)
            {
                distanta[nod_2] = distanta[nod] + cost;
                pq.push(make_pair(distanta[nod_2], nod_2));
            }
        }
    }

    for(int index = 2; index < noduri + 1; index++)
        if(distanta[index] != INT_MAX)
            g << distanta[index] << " ";
        else
            g << 0 << " ";
}

void Graf :: bellmanford()
{
    int x, y, cost;

    f >> noduri >> muchii;

    vector<vector<pair<int, int>>> edges;
    vector<int> distanta;
    vector<int> aparitii;
    vector<bool> ales;

    edges.resize(noduri + 1);
    distanta.resize(noduri + 1);
    aparitii.resize(noduri + 1);
    ales.resize(noduri + 1);

    for(int index = 0; index < this->muchii; index++)
    {
        f >> x >> y >> cost;
        edges[x].push_back(make_pair(y, cost));
    }

    for(int index = 0; index < noduri + 1; index++)
    {
        distanta[index] = INT_MAX;
        ales[index] = false;
        aparitii[index] = 0;
    }

    queue<int> q;

    distanta[1] = 0;

    q.push(1);

    aparitii[1] = 1;

    while(!q.empty())
    {

        int nod = q.front();

        q.pop();

        ales[nod] = false;

        for(unsigned int index = 0; index < edges[nod].size(); index++)
        {
            int nod_2 = edges[nod][index].first;
            cost = edges[nod][index].second;

            if(distanta[nod_2] > distanta[nod] + cost)
            {
                distanta[nod_2] = distanta[nod] + cost;

                if(!ales[nod_2])
                {
                    if(aparitii[nod_2] > noduri)
                    {
                        g << "Ciclu negativ!";
                        return;
                    }

                    q.push(nod_2);
                    ales[nod_2] = true;
                    aparitii[nod_2]++;
                }
            }
        }
    }

    for(int index = 2; index < noduri + 1; index++)
        if(distanta[index] == INT_MAX)
            g << "0 ";
        else
            g << distanta[index] << " ";

}

void Graf :: maxflow()
{
    int x, y, cost, flow = 0;

    f >> noduri >> muchii;

    vector<vector<int>> capacitate;
    vector<vector<int>> flux;
    vector<int> tata, vizitat;

    capacitate.resize(noduri + 1);
    flux.resize(noduri + 1);
    tata.resize(noduri + 1, 0);
    vizitat.resize(noduri + 1, 0);

    for(int index = 0; index <= noduri; index++)
    {
        capacitate[index].resize(noduri + 1);
        flux[index].resize(noduri + 1);
    }

    lista.resize(noduri + 1);

    for(int index = 0; index < muchii; index++)
    {
        f >> x >> y >> cost;
        lista[x].push_back(y);
        lista[y].push_back(x);
        capacitate[x][y] = cost;
    }

   for(flow = 0; maxflow_bfs(tata, vizitat, capacitate, flux);)
    {
        for(auto nod : lista[noduri])
        {
            if(flux[nod][noduri] != capacitate[nod][noduri] && vizitat[nod])
            {
                tata[noduri] = nod;
                int flowmin = INT_MAX, aux = noduri;

                if(flux[nod][noduri] == capacitate[nod][noduri] || !vizitat[nod])
                    continue;

                while(aux != 1)
                {
                    flowmin = min(capacitate[tata[aux]][aux] - flux[tata[aux]][aux], flowmin);
                    aux = tata[aux];
                }

                if(flowmin == 0)
                    continue;

                aux = noduri;

                while(aux != 1)
                {
                    flux[tata[aux]][aux] += flowmin;
                    flux[aux][tata[aux]] -= flowmin;
                    aux = tata[aux];
                }

                flow += flowmin;
            }
        }
    }

    g << flow;
}

bool Graf :: maxflow_bfs(vector<int> &tata, vector<int> &vizitat, vector<vector<int>> capacitate, vector<vector<int>> &flux)
{
    queue<int> coada;

    int element;

    for(int index = 0; index <= noduri; index++)
        vizitat[index] = 0;

    vizitat[1] = 1;
    coada.push(1);
    tata[noduri] = 0;

    while(!coada.empty() && tata[noduri] == 0)
    {
        element = coada.front();

        coada.pop();

        if(element == noduri)
            continue;

        for(auto nod : lista[element])
            if(capacitate[element][nod] - flux[element][nod] > 0 && !vizitat[nod])
            {
                vizitat[nod] = 1;
                coada.push(nod);
                tata[nod] = element;
            }
    }

    return tata[noduri];
}

void Graf :: royfloyd()
{
    f >> noduri;

    vector<vector<int>> matrix;

    matrix.resize(noduri + 1);

    for(int index = 0; index <= noduri; index++)
        matrix[index].resize(noduri + 1);

    for(int index = 1; index <= noduri; index++)
        for(int secondIndex = 1; secondIndex <= noduri; secondIndex++)
        {
            f >> matrix[index][secondIndex];
            if(matrix[index][secondIndex] == 0)
                matrix[index][secondIndex] = INT_MAX;
        }

    for(int k = 1; k < noduri + 1; k++)
        for(int i = 1; i < noduri + 1; i++)
            for(int j = 1; j < noduri + 1; j++)
                if(matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX && matrix[i][j] > matrix[i][k] + matrix[k][j])
                    matrix[i][j] = matrix[i][k] + matrix[k][j];

    for(int i = 1; i < noduri + 1; i++)
    {
        for(int j = 1; j < noduri + 1; j++)
            if(matrix[i][j] == INT_MAX || i == j)
                g << "0 ";
            else
                g << matrix[i][j] << " ";
        g << "\n";
    }

}

void Graf :: darb()
{
    int x, y, diametruMaxim = -1, nodulUrmator = -1;

    vector<int> diametru;

    f >> noduri;

    diametru.resize(noduri + 1);
    lista.resize(noduri + 1);

    for(int index = 1; index <= noduri; index++)
    {
        f >> x >> y;
        lista[x].push_back(y);
        lista[y].push_back(x);
    }

    bfs_darb(1, diametru, diametruMaxim, nodulUrmator);

    bfs_darb(nodulUrmator, diametru, diametruMaxim, nodulUrmator);

    g << diametruMaxim + 1;
}

void Graf :: bfs_darb(int start, vector<int>& diametru, int& diametruMaxim, int& nodulUrmator)
{
    for(int index = 1; index <= noduri; index++)
        diametru[index] = -1;

    unsigned int index = 0;

    vector<int> coada;

    coada.push_back(start);

    diametru[start] = 0;

    while(index < coada.size())
    {
        int nod = coada[index++];

        for(unsigned int secondIndex = 0; secondIndex < lista[nod].size(); secondIndex++)
            if(diametru[lista[nod][secondIndex]] == -1)
            {
                coada.push_back(lista[nod][secondIndex]);
                diametru[lista[nod][secondIndex]] = diametru[nod] + 1;
            }
    }

    for(int index = 1; index <= noduri; index++)
        if(diametru[index] > diametruMaxim)
        {
            diametruMaxim = diametru[index];
            nodulUrmator = index;
        }
}

int Graf :: euler()
{
    int x, y;

    f >> noduri >> muchii;

    lista.resize(noduri + 1);

    int from[muchii], to[muchii];
    bool vizitat[muchii];

    for(int index = 0; index < muchii; index++)
    {
        f >> x >> y;

        lista[x].push_back(index);
        lista[y].push_back(index);

        from[index] = x;
        to[index] = y;
        vizitat[index] = false;
    }

    for(int index = 1; index < noduri + 1; index++)
        if(lista[index].size() % 2 != 0 || lista[index].size() == 0)
        {
            g << "-1\n";
            return 0;
        }

    vector<int> raspuns;

    stack<int> stiva;

    stiva.push(1);

    while(!stiva.empty())
    {
        int node = stiva.top();

        if(lista[node].size() > 0)
        {
            int muchie = lista[node].back();

            lista[node].pop_back();

            if(!vizitat[muchie])
            {
                int aux;

                if(node != from[muchie])
                    aux = from[muchie];
                else
                    aux = to[muchie];

                vizitat[muchie] = true;

                stiva.push(aux);
            }
        }
        else
        {
            stiva.pop();

            raspuns.push_back(node);
        }
    }

    for(unsigned int index = 0; index < raspuns.size() - 1; index++)
        g << raspuns[index] << " ";

    return 1;
}

void Graf :: hamilton()
{
    int x, y, c, sol = INT_MAX, index, secondIndex, nrNoduri, nrMuchii;

    f >> nrNoduri >> nrMuchii;

    noduri = nrNoduri;
    muchii = nrMuchii;

    lista.resize(noduri + 1);

    int cost[nrNoduri][nrNoduri];
    int rezultat[nrNoduri][nrNoduri];

    for(index = 0; index < nrNoduri; index++)
        for(secondIndex = 0; secondIndex < nrNoduri; secondIndex++)
            cost[index][secondIndex] = INT_MAX;

    for(index = 0; index < (1 << nrNoduri); index++)
        for(secondIndex = 0; secondIndex < nrNoduri; secondIndex++)
            rezultat[index][secondIndex] = INT_MAX;

    for(secondIndex = 0; secondIndex < nrMuchii; secondIndex++)
    {
        f >> x >> y >> c;

        lista[y].push_back(x);

        cost[x][y] = c;
    }

    rezultat[1][0] = 0;

    for(int index = 0; index < 1 << nrNoduri; index++)
        for(int secondIndex = 0; secondIndex < nrNoduri; secondIndex++)
            if(index & (1 << secondIndex))
                for(unsigned int aux = 0; aux < lista[secondIndex].size(); aux++)
                    {
                        int nod = lista[secondIndex][aux];

                        if(index & (1 << nod))
                            rezultat[index][secondIndex] = min(rezultat[index][secondIndex], rezultat[index^(1 << secondIndex)][nod] + cost[nod][secondIndex]);
                    }

    for(unsigned int aux = 0; aux < lista[0].size(); aux++)
    {
        int nod = lista[0][aux];

        sol = min(sol, rezultat[(1 << noduri) - 1][nod] + cost[nod][0]);
    }
    if(sol == INT_MAX)
        g << "Nu exista solutie";
    else
        g << sol;
}

void Graf :: cuplaj()
{
    int e, x, y;

    f >> noduri >> muchii >> e;

    lista.resize(noduri + 1);

    for(int index = 0; index < e; index++)
    {
        f >> x >> y;

        lista[x].push_back(y);
    }

    vector<int> stanga, dreapta;
    int rez = 0;
    vector<bool> vizitat;
    bool ok = true;

    stanga.resize(noduri + 1);
    dreapta.resize(noduri + 1);
    vizitat.resize(noduri + 1);

    for(int index = 0; index < noduri + 1; index++)
    {
        stanga[index] = 0;
        dreapta[index] = 0;
    }

    while(ok)
    {
        ok = 0;

        for(int index = 1; index < noduri + 1; index++)
            vizitat[index] = false;
        for(int index = 1; index < noduri + 1; index++)
            if(stanga[index] == 0 && cuplaje(index, stanga, dreapta, vizitat) == true)
            {
                rez++;
                ok = 1;
            }
    }

    g << rez << endl;

    for(int index = 1; index < noduri + 1; index++)
        if(stanga[index] > 0)
            g << index << " " << stanga[index] << endl;

    return;
}

bool Graf :: cuplaje(int index, vector<int> &stanga, vector<int> &dreapta, vector<bool> &vizitat)
{
    if(vizitat[index] == true)
        return false;

    vizitat[index] = true;

    for(int secondIndex : lista[index])
        if(dreapta[secondIndex] == 0)
        {
            stanga[index] = secondIndex;
            dreapta[secondIndex] = index;
            return true;
        }

    for(int secondIndex : lista[index])
        if(cuplaje(dreapta[secondIndex], stanga, dreapta, vizitat))
        {
            stanga[index] = secondIndex;
            dreapta[secondIndex] = index;
            return true;
        }

    return false;
}

int main()
{
    int problema = 2;

    if(problema == 1)   // 100
    {
        f.open ("bfs.in", std::ifstream::in);
        g.open ("bfs.out", std::ifstream::out);

        int n, m, s;

        f >> n >> m >> s;

        Graf graf(n, m, s);

        graf.bfs(s);

        f.close();

        g.close();

    }

    if(problema == 2)   // 100
    {
        int n, m;

        f.open ("dfs.in", std::ifstream::in);
        g.open ("dfs.out", std::ifstream::out);

        f >> n >> m;

        vector<bool> vizitat;

        vizitat.resize(n + 1);

        for(int index = 1; index <= n; index++)
            vizitat[index] = false;

        Graf graf(n, m);

        int contor = 0;

        for(int index = 1; index <= n; index++)
        {
            if(vizitat[index] == false)
                {
                    graf.dfs(vizitat, index);
                    contor++;
                }
        }

        g << contor;

        f.close();
        g.close();
    }

    if(problema == 3)   // 90 - TLE
    {
        int n, m;

        f.open ("biconex.in", std::ifstream::in);
        g.open ("biconex.out", std::ifstream::out);

        f >> n >> m;

        Graf graf(n, m);

        graf.biconex();

        f.close();
        g.close();
    }

    if(problema == 4)   // 70
    {
        int n, m;

        f.open ("ctc.in", std::ifstream::in);
        g.open ("ctc.out", std::ifstream::out);

        f >> n >> m;

        Graf graf(n, m, 0);

        vector<int> rezultat;
        vector<int> nivel;
        vector<int> nivelMinim;
        vector<bool> stiva;
        vector< vector <int> > output;
        stack<int> st;

        nivel.resize(n + 1);
        nivelMinim.resize(n + 1);
        stiva.resize(n + 1);

        for(int index = 1; index <= n; index++)
        {
            nivel[index] = -1;
            stiva[index] = false;
        }

        for(int index = 1; index <= n; index++)
            if(nivel[index] == -1)
                graf.componenteTareConexe(index, rezultat, nivel, nivelMinim, stiva, st, output, 0);

        g << output.size() << "\n";

        for(unsigned int index = 0; index < output.size(); index++)
        {
            for(unsigned int secondIndex = 0; secondIndex < output[index].size(); secondIndex++)
                g << output[index][secondIndex] << " ";
            g << "\n";
        }

        f.close();
        g.close();
    }

    if(problema == 5)   // 100
    {
        int n, m;

        f.open ("sortaret.in", std::ifstream::in);
        g.open ("sortaret.out", std::ifstream::out);

        f >> n >> m;

        Graf graf(n, m, 0);

        vector<int> output;
        vector<bool> vizitat;

        vizitat.resize(n + 1);

        for(int index = 1; index <= n; index++)
            vizitat[index] = false;

        for(int index = 1; index <= n; index++)
            if(vizitat[index] == false)
                    graf.sortaret(index, vizitat, output);

        for(int index = output.size() - 1; index >= 0; index --)
            g << output[index] << " ";

    }

    if(problema == 6)   // 100
    {
        f.open ("havelhakimi.in", std::ifstream::in);
        g.open ("havelhakimi.out", std::ifstream::out);

        vector<int> grade;

        int n, grad;

        f >> n;

        grade.resize(n);

        for(int index = 0; index < n; index++)
        {
            f >> grad;
            grade.push_back(grad);
        }

        Graf graf(0, 0, 0);

        if(graf.Havel_Hakimi(n, grade))
            g << "Secventa de numere poate forma un graf.";
        else
            g << "Secventa de numere nu poate forma un graf.";

    }

    if(problema == 7)   // 100
    {
        f.open ("critical.in", std::ifstream::in);
        g.open ("critical.out", std::ifstream::out);

        int n;

        f >> n;

        Graf graf(n);

        graf.critical();
    }

    if(problema == 8)
    {
        f.open ("apm.in", std::ifstream::in);
        g.open ("apm.out", std::ifstream::out);

        Graf graf;

        graf.apm();
    }

    if(problema == 9)
    {
        f.open ("disjoint.in", std::ifstream::in);
        g.open ("disjoint.out", std::ifstream::out);

        Graf graf;

        graf.disjoint();
    }

    if(problema == 10)
    {
        f.open ("dijkstra.in", std::ifstream::in);
        g.open ("dijkstra.out", std::ifstream::out);

        Graf graf;

        graf.dijkstra();
    }

    if(problema == 11)
    {
        f.open ("bellmanford.in", std::ifstream::in);
        g.open ("bellmanford.out", std::ifstream::out);

        Graf graf;

        graf.bellmanford();
    }

    if(problema == 12)
    {
        f.open ("maxflow.in", std::ifstream::in);
        g.open ("maxflow.out", std::ifstream::out);

        Graf graf;

        graf.maxflow();
    }

    if(problema == 13)
    {
        f.open ("royfloyd.in", std::ifstream::in);
        g.open ("royfloyd.out", std::ifstream::out);

        Graf graf;

        graf.royfloyd();
    }

    if(problema == 14)
    {
        f.open ("darb.in", std::ifstream::in);
        g.open ("darb.out", std::ifstream::out);

        Graf graf;

        graf.darb();
    }

    if(problema == 15)
    {
        f.open ("ciclueuler.in", std::ifstream::in);
        g.open ("ciclueuler.out", std::ifstream::out);

        Graf graf;

        graf.euler();
    }

    if(problema == 16)
    {
        f.open ("hamilton.in", std::ifstream::in);
        g.open ("hamilton.out", std::ifstream::out);

        Graf graf;

        graf.hamilton();
    }

    if(problema == 17)
    {
        f.open ("cuplaj.in", std::ifstream::in);
        g.open ("cuplaj.out", std::ifstream::out);

        Graf graf;

        graf.cuplaj();
    }
    return 0;
}
