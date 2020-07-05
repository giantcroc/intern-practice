#include <iostream>
#include <vector>
using namespace std;
class bitSet
{
public:
	bitSet(size_t range)
	{
		_bits.resize((range >> 5) + 1);
	}

	void Set(size_t N)
	{
		size_t index = N >> 5;
		size_t bitNum = N % 32;
		_bits[index] |= (1 << bitNum);
	}
	void Reset(size_t N)
	{
		size_t index = N >> 5;
		size_t bitNum = N % 32;
		_bits[index] &= (~(1 << bitNum));
	}
	bool Test(size_t N)
	{
		size_t index = N >> 5;
		size_t bitNum = N % 32;
		return (_bits[index] >> bitNum) & 1;
	}
private:
	vector<int> _bits;
};

int main()
{
	bitSet bs(1001);
	bs.Set(5);
	bs.Set(63);
	bool ret = bs.Test(5);
	if (ret)
	{
		cout << "它在" << endl;
	}
	else
	{
		cout << "它不在" << endl;
	}
    return 0;
}
