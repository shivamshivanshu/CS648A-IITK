#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <cstdio>
#define ll long long
const ll N = 1000000;
const ll rep = 1;
std::random_device rd;
std::mt19937_64 gen(rd());
std::uniform_real_distribution<> value_dist(0.0f, 1.0f);

std::vector<ll> det(rep, 0), mer(rep, 0);

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
void det_test()
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
void merge(std::vector<double> &v, int l, int mid, int r)
{
    std::vector<double> left(mid - l + 1, 0.0), right(r - mid, 0.0);
    for (int i = 0; i < left.size(); i++)
    {
        left[i] = v[l + i];
    }
    for (int i = 0; i < right.size(); i++)
    {
        right[i] = v[i + mid + 1];
    }
    int i = 0, j = 0, k = l;
    for (i = 0, j = 0, k = l; i < left.size() and j < right.size();)
    {
        if (left[i] <= right[j])
        {
            v[k++] = left[i++];
        }
        else
        {
            v[k++] = right[j++];
        }
    }
    while (i < left.size())
    {
        v[k++] = left[i++];
    }
    while (j < right.size())
    {
        v[k++] = right[j++];
    }
}
void merge_sort(std::vector<double> &v, int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) >> 1;
        merge_sort(v, l, mid);
        merge_sort(v, mid + 1, r);
        merge(v, l, mid, r);
    }
}

void merge_test()
{
    std::vector<double> testVector(N, 0.0);
    for (ll i = 0; i < rep; i++)
    {
        for (int j = 0; j < N; j++)
        {
            testVector[j] = value_dist(gen);
        }
        auto start = std::chrono::high_resolution_clock::now();
        merge_sort(testVector, 0, N - 1);
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        mer[i] = duration.count();
    }
}
int main()
{
    // det_test();
    merge_test();
    std::cout << "Non Random Quick Sort Time(ns): " << std::accumulate(det.begin(), det.end(), 0LL) / rep << std::endl;
    std::cout << "Merge Sort Time(ns): " << std::accumulate(mer.begin(), mer.end(), 0LL) / rep << std::endl;
    return 0;
}
