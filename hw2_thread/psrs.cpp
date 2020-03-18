#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

const int it = 1000;
const std::vector<int> N{48, 480, 4800, 48000, 480000, 4800000, 48000000};

class psrsThread
{
public:
    std::vector<int> data;
    std::vector<int> sample;
    std::vector<std::vector<int>> divided;
    std::vector<int> result;
    psrsThread(std::vector<int> data): data(data) {}
};

int currentN;
int currentT;

void test(const int& n);
std::vector<int>& generateTest(const int& n);
void PSRS(const std::vector<int>& dataset, int num_thread);
bool testPSRS(const std::vector<int>& dataset, int num_thread);
void PSRS_real(std::vector<int>& dataset, int num_thread);
void sortThread(std::shared_ptr<psrsThread> t);
void divideThread(std::shared_ptr<psrsThread> t, const std::vector<int>& mainSamples);

int main()
{
    std::for_each(N.begin(), N.end(), test);
}

void test(const int& n)
{
    std::cout<<"Dataset size: "<<n<<'\n';
    currentN = n;
    auto testData = generateTest(n);
    for (int i = 1; i <= 4; ++i)
    {
        std::cout<<"Number of threads: "<<i<<'\t';
        currentT = i;
        if (!testPSRS(testData, i))
        {
            std::cout<<"Wrong result!\n";
            exit(0);
        }
        int N = it;
        std::chrono::duration<double> t_span;
        std::chrono::steady_clock::time_point t_start, t_end;
        t_start = std::chrono::steady_clock::now();
        while (N--)
        {
            std::cerr<<n<<'\t'<<i<<'\t'<<it - N<<'\n';
            PSRS(testData, i);
        }
        t_end = std::chrono::steady_clock::now();
        t_span = std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start);
        std::cout<<"Time: "<<t_span.count()<<'\n';
    }
    std::cout<<'\n';
}

void PSRS(const std::vector<int>& dataset, int num_thread)
{
    std::vector<int> data = dataset;
    PSRS_real(data, num_thread);
}

void sortThread(std::shared_ptr<psrsThread> t)
{
    std::sort(t->data.begin(), t->data.end());
    for (int i = 0; i < currentT; ++i)
    {
        t->sample.push_back(t->data[i * t->data.size() / currentT]);
    }
}

void divideThread(std::shared_ptr<psrsThread> t, const std::vector<int>& mainSamples)
{
    int index1 = 0, index2 = 0;;
    for (int i = 0; i < currentT; ++i)
    {
        if (i == currentT - 1)
        {
            t->divided.push_back(std::vector<int>(t->data.begin() + index1, t->data.end()));
            break;
        }
        std::vector<int> tmp;
        while (t->data[index2] <= mainSamples[i])
        {
            ++index2;
        }
        if (index1 < index2)
        {
            tmp.insert(tmp.end(), t->data.begin() + index1, t->data.begin() + index2);
        }
        t->divided.push_back(tmp);
        index1 = index2;
    }
}

void finalThread(std::shared_ptr<psrsThread> t, int num, const std::vector<std::shared_ptr<psrsThread>>& PSRSes)
{
    for (int i = 0; i < PSRSes.size(); ++i)
    {
        t->result.insert(t->result.end(), PSRSes[i]->divided[num].begin(), PSRSes[i]->divided[num].end());
    }
    std::sort(t->result.begin(), t->result.end());
}

void PSRS_real(std::vector<int>& dataset, int num_thread)
{
    std::vector<std::shared_ptr<psrsThread>> PSRSes;
    for (int i = 0; i < num_thread; ++i)
    {
        PSRSes.push_back(std::make_shared<psrsThread>(std::vector<int>(dataset.begin() + i * (dataset.size() / num_thread),
                                                            dataset.begin() + (i + 1) * (dataset.size() / num_thread))));
    }
    switch (num_thread)
    {
    case 1:
        {
            std::thread t0(sortThread, PSRSes[0]);
            t0.join();
            break;
        }
    case 2:
        {
            std::thread t0(sortThread, PSRSes[0]);
            std::thread t1(sortThread, PSRSes[1]);
            t0.join();
            t1.join();
            break;
        }
    case 3:
        {
            std::thread t0(sortThread, PSRSes[0]);
            std::thread t1(sortThread, PSRSes[1]);
            std::thread t2(sortThread, PSRSes[2]);
            t0.join();
            t1.join();
            t2.join();
            break;
        }
    case 4:
        {
            std::thread t0(sortThread, PSRSes[0]);
            std::thread t1(sortThread, PSRSes[1]);
            std::thread t2(sortThread, PSRSes[2]);
            std::thread t3(sortThread, PSRSes[3]);
            t0.join();
            t1.join();
            t2.join();
            t3.join();
            break;
        }
    }
    std::vector<int> samples;
    for (const auto& it: PSRSes)
    {
        samples.insert(samples.end(), it->sample.begin(), it->sample.end());
    }
    std::sort(samples.begin(), samples.end());
    std::vector<int> mainSamples;
    for (int i = 1; i < num_thread; ++i)
    {
        mainSamples.push_back(i * num_thread);
    }
    switch (num_thread)
    {
    case 1:
        {
            std::thread t0(divideThread, PSRSes[0], mainSamples);
            t0.join();
            break;
        }
    case 2:
        {
            std::thread t0(divideThread, PSRSes[0], mainSamples);
            std::thread t1(divideThread, PSRSes[1], mainSamples);
            t0.join();
            t1.join();
            break;
        }
    case 3:
        {
            std::thread t0(divideThread, PSRSes[0], mainSamples);
            std::thread t1(divideThread, PSRSes[1], mainSamples);
            std::thread t2(divideThread, PSRSes[2], mainSamples);
            t0.join();
            t1.join();
            t2.join();
            break;
        }
    case 4:
        {
            std::thread t0(divideThread, PSRSes[0], mainSamples);
            std::thread t1(divideThread, PSRSes[1], mainSamples);
            std::thread t2(divideThread, PSRSes[2], mainSamples);
            std::thread t3(divideThread, PSRSes[3], mainSamples);
            t0.join();
            t1.join();
            t2.join();
            t3.join();
            break;
        }
    }
    switch (num_thread)
    {
    case 1:
        {
            std::thread t0(finalThread, PSRSes[0], 0, PSRSes);
            t0.join();
            break;
        }
    case 2:
        {
            std::thread t0(finalThread, PSRSes[0], 0, PSRSes);
            std::thread t1(finalThread, PSRSes[1], 1, PSRSes);
            t0.join();
            t1.join();
            break;
        }
    case 3:
        {
            std::thread t0(finalThread, PSRSes[0], 0, PSRSes);
            std::thread t1(finalThread, PSRSes[1], 1, PSRSes);
            std::thread t2(finalThread, PSRSes[2], 2, PSRSes);
            t0.join();
            t1.join();
            t2.join();
            break;
        }
    case 4:
        {
            std::thread t0(finalThread, PSRSes[0], 0, PSRSes);
            std::thread t1(finalThread, PSRSes[1], 1, PSRSes);
            std::thread t2(finalThread, PSRSes[2], 2, PSRSes);
            std::thread t3(finalThread, PSRSes[3], 3, PSRSes);
            t0.join();
            t1.join();
            t2.join();
            t3.join();
            break;
        }
    }
    dataset.clear();
    for (int i = 0; i < num_thread; ++i)
    {
        dataset.insert(dataset.end(), PSRSes[i]->result.begin(), PSRSes[i]->result.end());
    }
}

bool testPSRS(const std::vector<int>& dataset, int num_thread)
{
    std::vector<int> data = dataset;
    PSRS_real(data, num_thread);
    for (int i = 0; i < data.size() - 1; ++i)
    {
        if (data[i] > data[i + 1])
        {
            return false;
        }
    }
    return true;
}

std::vector<int>& generateTest(const int& n)
{
    static std::vector<int> testData;
    testData.resize(n);
    for (int i = 0; i < n; ++i)
    {
        testData[i] = i;
    }
    srand(19260817);
    for (int i = n - 1; i > 0; --i)
    {
        std::swap(testData[i], testData[rand() % i]);
    }
    return testData;
}