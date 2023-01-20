#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#define ll long long
const ll N = 100000;
const ll rep = 2000;
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_real_distribution<> value_dist(0.0f, 1.0f);

std::vector<ll> det(rep, 0), ran(rep, 0);

int partition(std::vector<double> &v, int l, int r, ll &ops)
{
    int i = l - 1;
    double pivot = v[r];
    for (int j = l; j < r; j++)
    {
        ++ops;
        if (v[j] <= pivot)
        {
            ++i;
            std::swap(v[i], v[j]);
        }
    }
    std::swap(v[i + 1], v[r]);
    return i + 1;
}
void qs_det(std::vector<double> &v, int l, int r, ll &ops)
{
    if (l < r)
    {
        int i = partition(v, l, r, ops);
        qs_det(v, l, i - 1, ops);
        qs_det(v, i + 1, r, ops);
    }
}
void qs_rand(std::vector<double> &v, int l, int r, ll &ops)
{
    if (l < r)
    {
        std::uniform_int_distribution<> index_dist(l, r);
        int idx = index_dist(gen);
        std::swap(v[idx], v[r]);

        auto i = partition(v, l, r, ops);
        qs_rand(v, l, i - 1, ops);
        qs_rand(v, i + 1, r, ops);
    }
}
void detTest()
{
    std::vector<double> testVector(N, 0.0);
    for (int i = 0; i < rep; i++)
    {
        for (int j = 0; j < N; j++)
        {
            testVector[j] = value_dist(gen);
        }
        ll ops = 0;
        qs_det(testVector, 0, N - 1, ops);
        det[i] = ops;
    }
}
void randTest()
{
    std::vector<double> testVector(N, 0.0);
    for (auto &x : testVector)
    {
        x = value_dist(gen);
    }
    for (int i = 0; i < rep; i++)
    {
        ll ops = 0;
        qs_rand(testVector, 0, N - 1, ops);
        ran[i] = ops;
    }
}
int main()
{
    detTest();
    randTest();
    std::cout << "Non Random Quick Sort Comparisions: " << std::accumulate(det.begin(), det.end(), 0LL) / rep << std::endl;
    std::cout << "Randomized Quick Sort Comparisions: " << std::accumulate(ran.begin(), ran.end(), 0LL) / rep << std::endl;
    return 0;
}
