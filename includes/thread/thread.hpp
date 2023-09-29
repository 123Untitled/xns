#ifndef XNS_THREAD_HEADER
#define XNS_THREAD_HEADER

// local headers
#include "macros.hpp"
#include "tuple.hpp"
#include "apply.hpp"

#include "is_function.hpp"
#include "integer_sequence.hpp"

// operating system headers
#include <pthread.h>
#include <unistd.h>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {



	// -- T H R E A D  C L A S S ----------------------------------------------

	class thread final {

			// -- private classes ---------------------------------------------

			/* wrapper */
			template <typename F, typename... A>
			class wrapper final {

				public:

					// -- public types ----------------------------------------

					/* prototype */
					using function = F;

					/* arguments type */
					using arguments = xns::tuple<A...>;


					// -- public lifecycle ------------------------------------

					/* members constructor */
					explicit wrapper(F&& function, A&&... arguments) noexcept
					: func{function}, args{xns::forward<A>(arguments)...} {}


					~wrapper(void) noexcept = default;



				//private:

					// -- private members --------------------------------------

					/* function pointer */
					function func;

					/* arguments */
					arguments args;

			};


		public:

			// -- public constructors -----------------------------------------

			/* default constructor */
			inline thread(void) noexcept = default;

			/* function constructor */
			template <typename F, typename... A>
			explicit thread(F&& func, A&&... args) noexcept
			: _thread{}, _joinable{false} {

				using wrapper_t = xns::thread::wrapper<F, A...>;

				wrapper_t* wrapper = new wrapper_t{func, xns::forward<A>(args)...};

				// create thread
				if (::pthread_create(&_thread, nullptr, _function<F, A...>, wrapper) == 0) {
					// set joinable to true
					_joinable = true;
				}

			}

			/* non-copyable class */
			NON_COPYABLE(thread);

			/* move constructor */
			thread(thread&& other) noexcept
			: _thread{other._thread}, _joinable{other._joinable} {
				// invalidate other
				other._joinable = false;
			}

			/* destructor */
			~thread(void) noexcept {
				// detach thread if joinable
				if (_joinable == true) {
					::pthread_detach(_thread);
				}
			}

			// -- public methods ----------------------------------------------

			/* join */
			void join(void) {
				// check if joinable
				if (_joinable == true) {
					// join thread
					::pthread_join(_thread, nullptr);
					std::cout << "joined" << std::endl;
					// set joinable to false
					_joinable = false;
					return;
				}
				std::cout << "not joinable" << std::endl;
			}


			// -- public accessors --------------------------------------------

			/* joinable */
			bool joinable(void) const noexcept {
				return _joinable;
			}



		private:



			// -- private methods ---------------------------------------------



			template <typename F, typename... A>
			static void* _function(void* args) noexcept {

				using wrapper_t = thread::wrapper<F, A...>;

				std::cout << "launching thread" << std::endl;

				// get object
				wrapper_t* tuple = static_cast<wrapper_t*>(args);

				xns::apply(tuple->func, tuple->args);

				// delete object
				delete tuple;


				// call function
				// return
				return nullptr;
			}


			// -- private members ---------------------------------------------

			/* thread */
			::pthread_t _thread;

			/* joinable */
			bool _joinable;

	};

}





#endif // THREAD_HEADER
