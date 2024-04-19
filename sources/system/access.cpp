#include "xns/system/access.hpp"
#include "xns/system/environment.hpp"
#include "xns/string/string.hpp"
#include <unistd.h>



/* x ok */
auto xns::access::x_ok(const xns::string& path) noexcept -> bool {
	return ::access(path.data(), X_OK) == 0;
}

/* r ok */
auto xns::access::r_ok(const xns::string& path) noexcept -> bool {
	return ::access(path.data(), R_OK) == 0;
}

/* w ok */
auto xns::access::w_ok(const xns::string& path) noexcept -> bool {
	return ::access(path.data(), W_OK) == 0;
}

/* f ok */
auto xns::access::f_ok(const xns::string& path) noexcept -> bool {
	return ::access(path.data(), F_OK) == 0;
}


/* sys x ok */
auto xns::access::sys_x_ok(xns::string& exec) -> bool {

	auto paths{xns::env::paths()};

	xns::string buffer{};

	for (xns::size_t x = 0; x < paths.size(); ++x) {

		buffer.reserve(paths[x].size()
					   + 1
					   + exec.size());

		buffer.append(paths[x]);
		buffer.append('/');
		buffer.append(exec);

		if (::access(buffer.data(), X_OK) == 0) {
			exec = xns::move(buffer);
			return true;
		}

		buffer.clear();


	}
	return false;
}
