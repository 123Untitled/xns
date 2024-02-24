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

#ifndef XNS_MALLOC_HPP
#define XNS_MALLOC_HPP


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	//template <typename T>
	//class ptr final {


	//	private:

	//		// -- private types -----------------------------------------------

	//		/* self type */
	//		using self = xns::ptr<T>;

	//		/* mutable pointer type */
	//		using mut_ptr = T*;

	//		/* size type */
	//		using size_type = decltype(sizeof(0));


	//		// -- private lifecycle -------------------------------------------

	//		/* default constructor */
	//		ptr(mut_ptr ptr, const size_type size) noexcept
	//		: _ptr{ptr} {

	//			// set size
	//			*reinterpret_cast<size_type*>(_ptr) = size;

	//			// activate least significant bit
	//			*reinterpret_cast<size_type*>(_ptr) |= 1;
	//		}

	//	public:

	//		// -- public conversion operators ---------------------------------

	//		/* conversion to mutable pointer */
	//		operator mut_ptr(void) const noexcept {
	//			return reinterpret_cast<size_type*>(_ptr) + 1;
	//		}



	//	private:


	//		// -- private members ---------------------------------------------

	//		/* data pointer */
	//		mut_ptr _ptr;

	//};

	constexpr unsigned int alignment = sizeof(void*);

	inline auto align(const decltype(sizeof(0)) size) noexcept -> decltype(sizeof(0)) {
		return (size + alignment - 1) & ~(alignment - 1);
	}


	// -- M A L L O C ---------------------------------------------------------

	/* malloc */
	template <typename T>
	void* malloc(const decltype(sizeof(0)) size) noexcept {


		class malloc final {

			public:

				malloc(void) noexcept = default;


		}; // class malloc





		malloc m;

		return nullptr;
	}






	/* realloc */
	inline void* realloc(void*, const decltype(sizeof(0))) noexcept {



		return nullptr;
	}

	/* realloc_without_copy */
	void* realloc_without_copy(void*, const decltype(sizeof(0))) noexcept;

} // namespace xns

#endif // XNS_MALLOC_HPP
