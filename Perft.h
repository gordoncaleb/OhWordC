#ifndef PERFT_H_
#define PERFT_H_

namespace OhWordC{
class Perft{
private:
	
public:
	int level[20];
	Perft(void);
	void grow(int depth, Board * board);
	~Perft(void);
};
}
#endif

