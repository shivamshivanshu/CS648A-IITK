#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#define ll long long
const ll N = 1000000;
const ll rep = 500;
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_real_distribution<> value_dist(0.0f, 1.0f);

std::vector<ll> det(rep, 0), ran(rep, 0);

int partition(std::vector<double> &v, int l, int r)
{
        int i = l - 1;
        double pivot = v[r];
        for (int j = l; j < r; j++)
        {
                if (v[j] <= pivot)
                {
                        ++i;
                        std::swap(v[i], v[j]);
                }
        }
        std::swap(v[i + 1], v[r]);
        return (i + 1);
}
void qs_det(std::vector<double> &v, int l, int r)
{
        if (l < r)
        {
                auto i = partition(v, l, r);
                qs_det(v, l, i - 1);
                qs_det(v, i + 1, r);
        }
}
void qs_rand(std::vector<double> &v, int l, int r)
{
        if (l < r)
        {
                std::uniform_int_distribution<> index_dist(l, r);
                int idx = index_dist(gen);
                std::swap(v[idx], v[r]);

                auto i = partition(v, l, r);
                qs_rand(v, l, i - 1);
                qs_rand(v, i + 1, r);
        }
}
void detTest()
{
        std::vector<double> testVector(N, 0.0);
        for (ll i = 0; i < rep; i++)
        {
                for (auto &x : testVector)
                {
                        x = value_dist(gen);
                }
                auto start = std::chrono::high_resolution_clock::now();
                qs_det(testVector, 0, N - 1);
                auto end = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                det[i] = duration.count();
        }
}
void randTest()
{
        std::vector<double> testVector(N, 0.0);
        for (auto &x : testVector)
        {
                x = value_dist(gen);
        }
        for (ll i = 0; i < rep; i++)
        {
                auto start = std::chrono::high_resolution_clock::now();
                qs_rand(testVector, 0, N - 1);
                auto end = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                ran[i] = duration.count();
        }
}
int main()
{
        detTest();
        randTest();
        std::cout << "Non Random Quick Sort Time(ns): " << std::accumulate(det.begin(), det.end(), 0LL) / rep << std::endl;
        std::cout << "Randomized Quick Sort Time(ns): " << std::accumulate(ran.begin(), ran.end(), 0LL) / rep << std::endl;
        return 0;
}
