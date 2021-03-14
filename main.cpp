#include <bits/stdc++.h>
#define prim 70009

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int n, MOD, nr_teste;
int interval_tim = 32;
int f[100000003];
double asteptare = -1.00;
double medstl, medbubble, medquick1, medquick2, medcount, medtim;
double cntstl, cntbubble, cntquick1, cntquick2, cntcount, cnttim;
vector<int>a;
vector<int>v;
vector<int>h[prim];
mt19937 nr_random(time(0));

void Citire();
void AfisareMedii();
int Verifica();

int Pivot1(int st, int dr); // nr random
int Pivot2(int st, int dr); // mediana din 3
int Mutare(int st, int dr, int pivot);

int BubbleSort(int st, int dr);
int QuickSort(int st, int dr, int pivot, auto timp);
void CountSort();
void InsertionSort(int st, int dr); // pentru TimSort
void MergeTim(int st, int mij, int dr);
void TimSort();

void TestareSTL();
void TestareBubbleSort();
void TestareQuickSort1();
void TestareQuickSort2();
void TestareCountSort();
void TestareTimSort();

int main()
{
    int i, j, x;

    Citire();

    for(i = 1; i <= nr_teste; i++)
    {
        cout << "\n\n--------------------------- TEST " << i << " ---------------------------\n";

        ///testez sortarile pentru numere random:
        cout << "1. Elementele sunt numere random:\n";

        v.clear();
        a.clear();
        for(j = 0; j < prim; j++)
            h[j].clear();

        for(j = 0; j < n; j++)
        {
            x = nr_random() % MOD;
            v.push_back(x);
            a.push_back(x);
            h[x % prim].push_back(x);
        }
        TestareQuickSort1();

        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareQuickSort2();


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareBubbleSort();


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareCountSort();


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareTimSort();

        TestareSTL();

        ///testez sortarile pentru numere deja sortate crescator:

        cout << "\n2. Elementele sunt numere deja sortate crescator:\n";


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareQuickSort1();

        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareQuickSort2();


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareBubbleSort();


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareCountSort();


        for(j = 0; j < n; j++)
            a[j] = v[j];
        TestareTimSort();

    }
    AfisareMedii();

    return 0;
}

void Citire()
{
    ifstream fin("proiect.in");

    unsigned long long nr, nrm;
    try
    {
        cout << "Numar de teste = ";
        cin >> nr_teste;
        cout << "Numar de elemente = ";
        cin >> nr;
        if(nr > INT_MAX)
        {
            throw 1;
        }
        else
        {
            cout << "Valoarea maxima a unui element = ";
            cin >> nrm;
            cout << "\n";
            if(nrm > INT_MAX)
                throw 2;
            else
            {
                cout << "Introdu timpul maxim pe care esti dispus sa il astepti pentru fiecare sortare (in secunde): ";
                cin >> asteptare;
                asteptare *= 1000;
            }
        }

    }
    catch(int x)
    {
        if(x == 1)
        {
            cout << "Numarul de elemente e prea mare!\n";
            exit(0);
        }
        if(x == 2)
        {
            cout << "Elementul maxim este prea mare!\n";
            exit(0);
        }
        if(x == 3)
        {
            cout << "Timpul maxim este prea mare!\n";
            exit(0);
        }
    }

    n = nr;
    MOD = nrm + 1;
    fin.close();
}

void AfisareMedii()
{
    cout << "\n\n------------------------- TIMPI MEDII -------------------------\n\n";
    if(cntstl != 0)
    {
        medstl /= cntstl;
        cout << "Sortare STL -> " << medstl << " ms\n";
    }
    else cout << "Sortare STL -> nu s-a putut face media\n";

    if(cntbubble != 0)
    {
        medbubble /= cntbubble;
        cout << "BubbleSort -> " << medbubble << " ms\n";
    }
    else cout << "BubbleSort -> nu s-a putut face media\n";

    if(cntquick1 != 0)
    {
        medquick1 /= cntquick1;
        cout << "QuickSort1 -> " << medquick1 << " ms\n";
    }
    else cout << "QuickSort1 -> nu s-a putut face media\n";

    if(cntquick2 != 0)
    {
        medquick2 /= cntquick2;
        cout << "QuickSort2 -> " << medquick2 << " ms\n";
    }
    else cout << "QuickSort2 -> nu s-a putut face media\n";

    if(cntcount != 0)
    {
        medcount /= cntcount;
        cout << "CountSort -> " << medcount << " ms\n";
    }
    else cout << "CountSort -> nu s-a putut face media\n";

    if(cnttim != 0)
    {
        medtim /= cnttim;
        cout << "TimSort -> " << medtim << " ms\n";
    }
    else cout << "TimSort -> nu s-a putut face media\n";
}

int Verifica()
{
    int i, j, k, x, gasit;

    gasit = 0;
    k = a[0] % prim;
    for(j = 0; j < h[k].size(); j++)
        if(h[k][j] == a[0])
            gasit = 1;
    if(gasit == 0)
        return 0;

    for(i = 1; i < n; i++)
    {
        if(a[i] < a[i - 1])
            return 0;

        gasit = 0;
        k = a[i] % prim;
        for(j = 0; j < h[k].size(); j++)
            if(h[k][j] == a[i])
                gasit = 1;
        if(gasit == 0)
            return 0;
    }
    return 1;
}

int BubbleSort(int st, int dr)
{
    auto timp = high_resolution_clock::now();
    for(int i = st; i < dr; i++)
    {
        auto timp_acum = high_resolution_clock::now();
        duration<double, std::milli> durata_sort = timp_acum - timp;
        if(double(durata_sort.count()) > asteptare)
            return -1;

        for(int j = i + 1; j <= dr; j++)
            if(a[i] > a[j])
                swap(a[i], a[j]);
    }
}

int Pivot1(int st, int dr) // nr random
{
    int poz;
    poz = nr_random() % (dr - st + 1);
    swap(a[st], a[st + poz]);
    return a[st];
}

int Pivot2(int st, int dr) // mediana din 3
{
    int poz1, poz2, poz3;
    poz1 = st + (nr_random() % (dr - st + 1));
    poz2 = st + (nr_random() % (dr - st + 1));
    poz3 = st + (nr_random() % (dr - st + 1));

    if((a[poz1] <= a[poz2] && a[poz2] <= a[poz3]) ||
       (a[poz3] <= a[poz2] && a[poz2] <= a[poz1]))
        swap(a[st], a[poz2]);

    if((a[poz2] <= a[poz1] && a[poz1] <= a[poz3]) ||
       (a[poz3] <= a[poz1] && a[poz1] <= a[poz2]))
        swap(a[st], a[poz1]);

    if((a[poz1] <= a[poz3] && a[poz3] <= a[poz2]) ||
       (a[poz2] <= a[poz3] && a[poz3] <= a[poz1]))
        swap(a[st], a[poz3]);

    return int(a[st]);
}

int Mutare(int st, int dr, int pivot)
{
    int i,j,p;
    if(pivot == 1)
        p = Pivot1(st, dr);
    else
        p = Pivot2(st, dr);

    i = st+1;
    j = dr;
    while(i <= j)
    {
        if(a[i] <= p) i++;
        if(a[j] > p) j--;
        if(i < j && a[i] > p && p >= a[j])
        {
            swap(a[i],a[j]);
            i++;
            j--;
        }
    }
    swap(a[st],a[i-1]);
    return i-1;
}

int QuickSort(int st, int dr, int pivot, auto timp)
{
    auto timp_acum = high_resolution_clock::now();
    duration<double, std::milli> durata_sort = timp_acum - timp;
    if(double(durata_sort.count()) > asteptare)
        return -1;


    if(dr - st + 1 <= 32)
        BubbleSort(st, dr);
    else
        if(st < dr)
        {
            //int p = Pivot1(st, dr);
            int m = Mutare(st, dr, pivot);

            QuickSort(st, m - 1, pivot, timp);
            QuickSort(m + 1, dr, pivot, timp);
        }
}

int CountSort(auto timp)
{
    int i, k;
    for(i = 0; i < n; i++)
        f[a[i]]++;

    k = 0;
    for(i = 0; i <= MOD; i++)
    {
        auto timp_acum = high_resolution_clock::now();
        duration<double, std::milli> durata_sort = timp_acum - timp;
        if(double(durata_sort.count()) > asteptare)
            return -1;

        while(f[i] != 0)
        {
            a[k++] = i;
            f[i]--;
        }
    }
}

void InsertionSort(int st, int dr)
{
    int i, j, nr;
    for(i = st; i < dr; i++)
    {
        nr = a[i];
        j = i - 1;

        while(j >= st && a[j] > nr)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = nr;
    }
}

void MergeTim(int st, int mij, int dr)
{
    int i, j, k, lg1, lg2;

    lg1 = mij - st;
    lg2 = dr - mij + 1;
    int ast[lg1], adr[lg2];

    for(i = 0; i < lg1; i++)
        ast[i] = a[st + i];

    for(i = 0; i <= lg2; i++)
        adr[i] = a[mij + i];

    i = j = 0;
    k = st;
    while(i < lg1 && j < lg2)
        if(ast[i] <= adr[j])
            a[k++] = ast[i++];
        else
            a[k++] = adr[j++];


    while(i < lg1)
        a[k++] = ast[i++];

    while(j < lg2)
        a[k++] = adr[j++];
}

void TimSort()
{
    int i, lg, st, dr, mij;

    for(i = 0; i < n; i += interval_tim)
        InsertionSort(i, min(i + interval_tim, n));

    for(lg = interval_tim; lg < n; lg *= 2)
        for(st = 0; st < n; st += 2 * lg)
        {
            mij = st + lg;
            dr = min(st + 2 * lg - 1, n - 1);

            MergeTim(st, mij, dr);
        }
}

void TestareSTL()
{
    auto start1 = high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto sfarsit1 = high_resolution_clock::now();
    duration<double, std::milli> durata = sfarsit1 - start1;

    cout << "Sortare STL -> " << durata.count() << " ms\n";
    if(durata.count() != 0)
    {
        medstl += double(durata.count());
        cntstl++;
    }
}

void TestareBubbleSort()
{
    int r;
    try
    {
        auto start1 = high_resolution_clock::now();
        r = BubbleSort(0, n-1);
        auto sfarsit1 = high_resolution_clock::now();
        duration<double, std::milli> durata = sfarsit1 - start1;

        if(r != -1)
        {
            if(Verifica() == 1)
            {
                cout << "BubbleSort -> corect -> " << durata.count() << " ms\n";
                if(durata.count() != 0)
                {
                    medbubble += double(durata.count());
                    cntbubble++;
                }
            }
            else
                throw 1;
        }
        else
            throw 2;
    }
    catch(int x)
    {
        if(x == 1)
            cout << "BubbleSort nu a sortat corect numerele! ( conform Verifica() )\n";
        else
            cout << "Nu se poate efectua BubbleSort in timpul introdus!\n";
    }
}

void TestareQuickSort1()
{
    int r;
    /// random
    try
    {
        auto start1 = high_resolution_clock::now();
        r = QuickSort(0, n - 1, 1, start1);
        auto sfarsit1 = high_resolution_clock::now();
        duration<double, std::milli> durata = sfarsit1 - start1;

        if(r != -1)
        {
            if(Verifica() == 1)
            {
                cout << "QuickSort cu pivot ales random -> corect -> " << durata.count() << " ms\n";
                if(durata.count() != 0)
                {
                    medquick1 += double(durata.count());
                    cntquick1++;
                }
            }
            else
                throw 1;
        }
        else
            throw 2;
    }
    catch(int x)
    {
        if(x == 1)
            cout << "QuickSort cu pivot random nu a sortat corect numerele! ( conform Verifica() )\n";
        else
            cout << "Nu se poate efectua QuickSort cu pivotul random in timpul introdus!\n";
    }
}

void TestareQuickSort2()
{
    /// mediana din 3
    int r;
    try
    {
        auto start1 = high_resolution_clock::now();
        r = QuickSort(0, n - 1, 2, start1);
        auto sfarsit1 = high_resolution_clock::now();
        duration<double, std::milli> durata = sfarsit1 - start1;

        if(r != -1)
        {
            if(Verifica() == 1)
            {
                cout << "QuickSort cu pivot ales mediana din 3 -> corect -> " << durata.count() << " ms\n";
                if(durata.count() != 0)
                {
                    medquick2 += double(durata.count());
                    cntquick2++;
                }
            }
            else
                throw 1;
        }
        else
            throw 2;
    }
    catch(int x)
    {
        if(x == 1)
            cout << "QuickSort cu pivot mediana din 3 nu a sortat corect numerele! ( conform Verifica() )\n";
        else
            cout << "Nu se poate efectua QuickSort cu pivot mediana din 3 in timpul introdus!\n";
    }
}

void TestareCountSort()
{
    int r;
    try
    {
        if(MOD > 1e8 + 1)
            throw 1;

        auto start1 = high_resolution_clock::now();
        r = CountSort(start1);
        auto sfarsit1 = high_resolution_clock::now();
        duration<double, std::milli> durata = sfarsit1 - start1;

        if(r != -1)
        {
            if(Verifica() == 1)
            {
                cout << "CountSort -> corect -> " << durata.count() << " ms\n";
                if(durata.count() != 0)
                {
                    medcount += double(durata.count());
                    cntcount++;
                }
            }
            else
                throw 3;
        }
        else
            throw 2;
    }
    catch(int x)
    {
        if(x == 1)
            cout << "Nu se poate efectua CountSort cu numarul maxim introdus\n";
        else
        if(x == 2)
            cout << "Nu se poate efectua CountSort in timpul introdus\n";
        else
            cout << "CountSort nu a sortat corect numerele! ( conform Verifica() )\n";
    }
}

void TestareTimSort()
{
    try
    {
        int ok = 0;
        for(int i = 1; i <= 18; i++)
            if(n == 1 << i)
            {
                ok = 1;
                i = 20;
            }
        if(ok == 0)
            throw 1;

        auto start1 = high_resolution_clock::now();
        TimSort();
        auto sfarsit1 = high_resolution_clock::now();
        duration<double, std::milli> durata = sfarsit1 - start1;

        if(Verifica() == 1)
        {
            cout << "TimSort -> corect -> " << durata.count() << " ms\n";
            if(durata.count() != 0)
            {
                medtim += double(durata.count());
                cnttim++;
            }
        }
        else
            throw 2;
    }
    catch(int x)
    {
        if(x == 1)
            cout << "Nu se poate efectua TimSort decat pe n = 2^k numere (k <= 18) :)\n";
        else
            cout << "TimSort nu a sortat corect numerele! ( conform Verifica() )\n";
    }
}
