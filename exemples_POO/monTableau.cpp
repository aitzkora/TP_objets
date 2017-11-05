#include <cassert>
#include <vector>

using namespace std;
class monTableau 
{
    vector<int> data;
    public:
    monTableau(const vector<int> & x) : data(x) {}
    int computeSum() { int s = 0; for (auto & x : data ) { s+= x; } return s; }
    ~monTableau() {}
};

int main()
{
    monTableau z({1, 2, 3});
    assert( z.computeSum() == 6);
    return 0;
}
