#include "Array.h"

class RangeArray : public Array{

	protected:
		int l;
		int h;
	public:
		RangeArray(int,int);
		~RangeArray();

		int baseValue();
		int endValue();

		int& operator[](int);
		int operator[](int) const;
};
