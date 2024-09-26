
class Counter {
public:
	virtual void inc() = 0;
	virtual void dec() = 0;
	virtual operator int() = 0;
	virtual ~Counter() {};
};


void UseCounter(Counter& ctr, int num);

int main(int argc, char** argv) {
	LimitedCounter lc(0, 5);
	OverflowCounter oc(5, 9);

	std::cout << oc << std::endl;
	UseCounter(oc, 5);
	std::cout << oc << std::endl; // should display zero
	UseCounter(oc, -1);
	std::cout << oc << std::endl; // should display 9
	oc.dec();
	std::cout << oc << std::endl; // should display 8

	std::cout << lc << std::endl;
	lc.inc();
	std::cout << lc << std::endl;
	lc.dec();
	std::cout << lc << std::endl;
	for(int i = 0; i < 10; ++i) lc.inc();
	std::cout << lc << std::endl;
	UseCounter(lc, -9);
	std::cout << lc << std::endl;

	return 0;
}
