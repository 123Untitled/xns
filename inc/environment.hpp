#ifndef ENV_HEADER
#define ENV_HEADER

#include "string.hpp"
#include "unique_pointer.hpp"
#include "weak_pointer.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include "output.hpp"


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- E N V I R O N M E N T -----------------------------------------------

	class env {

		public:

			// -- public types ------------------------------------------------

			/* vector type */
			using vector_type = xns::vector<xns::pair<xns::string, xns::string>>;

			/* size type */
			using size_type   = typename vector_type::size_type;

			/* weak string type */
			using weak_string = xns::weak_ptr<const xns::string>;


			// -- public constructors -----------------------------------------

			/* non-instanciable class */
			NON_INSTANCIABLE(env);


			// -- public static methods ---------------------------------------

			/* initialize environment */
			static void init(const char** envp);

			/* get environment variable */
			static const weak_string get(const xns::string&);

			/* print environment */
			static void print(void);


		private:

			// -- private static members --------------------------------------

			/* environment variables */
			static vector_type _env;


	};


}


#endif
