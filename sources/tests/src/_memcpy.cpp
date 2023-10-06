#include "unit_tests.hpp"
#include "memcpy.hpp"
#include "benchmark.hpp"
#include "system.hpp"

#include <vector>
#include <fcntl.h>


static xns::size_t NSIZE = 0;

/* unit test */
template <>
int UT::unit_tests<"memcpy">(void) {

	xns::size_t N = NSIZE * NSIZE * NSIZE;

	std::vector<xns::ubyte> src{};
	std::vector<xns::ubyte> dst{};

	src.resize(N);
	dst.resize(N);

	{
		auto fd = ::open("/dev/urandom", O_RDONLY);
		if (fd == -1) {
			xns::println("error: failed to open /dev/urandom");
			xns::out::render();
			return false;
		}
		::read(fd, src.data(), N);
		::close(fd);
	}

	xns::benchmark<5> bench;

	bench.run("xns::memcpy", xns::memcpy<xns::ubyte, xns::ubyte>, dst.data(), src.data(), N);
	bench.run("std::memcpy", std::memcpy, dst.data(), src.data(), N);

	bench.result("memcpy");
	std::cout << "done" << std::endl;


	return 0;


	// Taille de la ligne de cache en octets (ex. 128 octets)
    size_t cacheLineSize = xns::system::cache_line();

	std::cout << "Taille de la ligne de cache : " << cacheLineSize << " octets" << std::endl;

    // Adresse mémoire à aligner
    uintptr_t address = reinterpret_cast<uintptr_t>(malloc(64)); // Exemple d'allocation de mémoire
	++address;

    // Calcul du masque d'alignement
    uintptr_t alignmentMask = cacheLineSize - 1;

    // Alignement de l'adresse mémoire
    uintptr_t alignedAddress = (address + alignmentMask) & ~alignmentMask;

    std::cout << "Adresse d'origine : " << std::hex << address << std::endl;
    std::cout << "Adresse alignée   : " << std::hex << alignedAddress << std::endl;

    free(reinterpret_cast<void*>(--address));

}




#if defined(XNS_TEST_MEMCPY)
int main(void) {
	return UT::unit_tests<"memcpy">();
}
#endif

