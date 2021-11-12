#include <cstdio>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::puts("Err 1 : No File Mentioned !");
		return -1;
	}
	
	std::ios::sync_with_stdio(false);
	std::fstream f(argv[1]);
	
	if (f.bad())
	{
		std::puts("Err 2 : Unable to Open File !");
		return -2;
	}
	
	char buf[524288/*512KB*/] = {};
	unsigned long long rs, total = 0;
	
	while (!f.eof())
	{
		f.read(buf, sizeof(buf));
		rs = f.gcount(); total += rs;
		
		for (auto i=0 ; i < rs ; ++i)
			buf[i] = ~buf[i];
		
		f.seekp(f.tellg() - sizeof(buf));
		f.write(buf, rs);
	}
	
	f.close();
	std::printf("Flipped %llu Bits in %s\n", total*8, argv[1]);
}