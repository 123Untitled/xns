/*****************************************************************************/
/*                                                                           */
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*                                                                           */
/*****************************************************************************/

#pragma once

#ifndef XNS_ENVIRONMENT_HEADER
#define XNS_ENVIRONMENT_HEADER

#include "string/string.hpp"
#include "memory/unique_ptr.hpp"
#include "memory/weak_ptr.hpp"
#include "containers/pair.hpp"
#include "containers/vector.hpp"
#include "terminal/output.hpp"


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



			// -- public static methods ---------------------------------------

			/* get environment variable */
			static auto get(const xns::string&) noexcept -> const weak_string;

			/* get paths */
			static auto paths(void) -> xns::vector<xns::string>;

			/* print environment */
			static auto print(void) -> void;


		private:

			// -- private lifecycle -------------------------------------------

			/* default constructor */
			env(void);

			/* non-assignable class */
			NON_ASSIGNABLE(env);

			/* destructor */
			~env(void) noexcept = default;


			// -- private modifiers -------------------------------------------

			/* initialize environment */
			auto init(char**) -> void;


			// -- private static accessors ------------------------------------

			/* get instance */
			inline static auto shared(void) -> env& {
				static env instance{};
				return instance;
			}


			// -- private members ---------------------------------------------

			/* environment variables */
			vector_type _env;


	};


}


#endif
