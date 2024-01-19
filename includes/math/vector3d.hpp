#ifndef XNS_VECTOR3D_HPP
#define XNS_VECTOR3D_HPP

#include "math.hpp"
#include <iostream>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- V E C T O R  3 D ----------------------------------------------------

	template <typename T>
	class vector3D final {

		// -- assertions ------------------------------------------------------

		/* require floating point type */
		static_assert(xns::is_floating<T>, "): VECTOR3D: T must be a floating point type :(");


		public:

			// -- public types ------------------------------------------------

			/* self type */
			using self = xns::vector3D<T>;

			/* value type */
			using value_type = T;

			/* mutable reference type */
			using mut_ref = value_type&;

			/* const reference type */
			using const_ref = const value_type&;


			// -- public lifecycle --------------------------------------------

			/* default constructor */
			inline constexpr vector3D(void) noexcept
			: _x{0}, _y{0}, _z{0} {}

			/* value constructor */
			inline constexpr vector3D(const value_type x, const value_type y, const value_type z) noexcept
			: _x{x}, _y{y}, _z{z} {}

			/* copy constructor */
			inline constexpr vector3D(const self& other) noexcept
			: _x{other._x}, _y{other._y}, _z{other._z} {}

			/* move constructor */
			inline constexpr vector3D(self&& other) noexcept
			: self{other} {} // copy

			/* destructor */
			inline ~vector3D(void) noexcept = default;


			// -- public assignment operators ---------------------------------

			/* copy assignment operator */
			inline constexpr auto operator=(const self& other) noexcept -> self& {
				_x = other._x;
				_y = other._y;
				_z = other._z;
				return *this;
			}

			/* move assignment operator */
			inline constexpr auto operator=(self&& other) noexcept -> self& {
				return self::operator=(other); // copy
			}


			// -- public accessors --------------------------------------------

			/* x coordinate */
			inline constexpr auto x(void) const noexcept -> const_ref {
				return _x;
			}

			/* y coordinate */
			inline constexpr auto y(void) const noexcept -> const_ref {
				return _y;
			}

			/* z coordinate */
			inline constexpr auto z(void) const noexcept -> const_ref {
				return _z;
			}


			// -- public characteristics --------------------------------------

			/* length */
			inline constexpr auto length(void) const noexcept -> value_type {
				return xns::sqrt((_x * _x) + (_y * _y) + (_z * _z));
			}

			/* length squared */
			inline constexpr auto length_squared(void) const noexcept -> value_type {
				return (_x * _x) + (_y * _y) + (_z * _z);
			}

			/* is normalized */
			inline constexpr auto is_normalized(void) const noexcept -> bool {
				// not implemented
				return false;
			}

			/* is zero */
			inline constexpr auto is_zero(void) const noexcept -> bool {
				return (_x == 0) && (_y == 0) && (_z == 0);
			}


			// -- public modifiers --------------------------------------------

			/* set x coordinate */
			inline constexpr auto x(const value_type x) noexcept -> void {
				_x = x;
			}

			/* set y coordinate */
			inline constexpr auto y(const value_type y) noexcept -> void {
				_y = y;
			}

			/* set z coordinate */
			inline constexpr auto z(const value_type z) noexcept -> void {
				_z = z;
			}

			/* normalize */
			inline constexpr auto normalize(void) noexcept -> void {
				const auto length = self::length();
				_x /= length;
				_y /= length;
				_z /= length;
			}

			/* scale */
			inline constexpr auto scale(const value_type scalar) noexcept -> void {
				_x *= scalar;
				_y *= scalar;
				_z *= scalar;
			}

			/* reset to zero */
			inline constexpr auto reset(void) noexcept -> void {
				_x = 0;
				_y = 0;
				_z = 0;
			}









			// -- public comparison operators ---------------------------------

			/* equality operator */
			inline constexpr auto operator==(const self& other) const noexcept -> bool {
				return (_x == other._x) && (_y == other._y) && (_z == other._z);
			}

			/* inequality operator */
			inline constexpr auto operator!=(const self& other) const noexcept -> bool {
				return (_x != other._x) || (_y != other._y) || (_z != other._z);
			}


			// -- public arithmetic operators ---------------------------------

			/* addition operator */
			inline constexpr auto operator+=(const self& other) noexcept -> void {
				_x += other._x;
				_y += other._y;
				_z += other._z;
			}

			/* subtraction operator */
			inline constexpr auto operator-=(const self& other) noexcept -> void {
				_x -= other._x;
				_y -= other._y;
				_z -= other._z;
			}

			/* multiplication operator */
			inline constexpr auto operator*=(const value_type scalar) noexcept -> void {
				_x *= scalar;
				_y *= scalar;
				_z *= scalar;
			}

			/* multiplication operator */
			inline constexpr auto operator*=(const self& other) noexcept -> void {
				_x *= other._x;
				_y *= other._y;
				_z *= other._z;
			}

			/* division operator */
			inline constexpr auto operator/=(const value_type scalar) noexcept -> void {
				_x /= scalar;
				_y /= scalar;
				_z /= scalar;
			}

			/* unary minus operator */
			inline constexpr auto operator-(void) const noexcept -> self {
				return self{-_x, -_y, -_z};
			}




			inline auto print(void) const noexcept -> void {
				std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
			}

		private:

			// -- private members ---------------------------------------------

			/* x coordinate */
			value_type _x;

			/* y coordinate */
			value_type _y;

			/* z coordinate */
			value_type _z;


		// -- friends ---------------------------------------------------------

		/* normalize as friend */
		template <typename U>
		friend constexpr auto normalize(const xns::vector3D<U>&) noexcept -> xns::vector3D<U>;

		/* dot product as friend */
		template <typename U>
		friend constexpr auto dot(const xns::vector3D<U>&, const xns::vector3D<U>&) noexcept -> xns::vector3D<U>::value_type;

		/* cross product as friend */
		template <typename U>
		friend constexpr auto cross(const xns::vector3D<U>&, const xns::vector3D<U>&) noexcept -> xns::vector3D<U>;

		/* project as friend */
		template <typename U>
		friend constexpr auto project(const xns::vector3D<U>&, const xns::vector3D<U>&) noexcept -> xns::vector3D<U>;

		/* reflect as friend */
		template <typename U>
		friend constexpr auto reflect(const xns::vector3D<U>&, const xns::vector3D<U>&) noexcept -> xns::vector3D<U>;

	};


	/* normalize */
	template <typename T>
	inline constexpr auto normalize(const xns::vector3D<T>& v) noexcept -> xns::vector3D<T> {
		const auto length = v.length();
		return xns::vector3D<T>{v._x / length,
								v._y / length,
								v._z / length};
	}

	/* dot product */
	template <typename T>
	inline constexpr auto dot(const xns::vector3D<T>& v1, const xns::vector3D<T>& v2) noexcept -> xns::vector3D<T>::value_type {
		return (v1._x * v2._x) + (v1._y * v2._y) + (v1._z * v2._z);
	}

	/* cross product */
	template <typename T>
	inline constexpr auto cross(const xns::vector3D<T>& v1, const xns::vector3D<T>& v2) noexcept -> xns::vector3D<T> {
		return xns::vector3D<T>{(v1._y * v2._z) - (v1._z * v2._y),
								(v1._z * v2._x) - (v1._x * v2._z),
								(v1._x * v2._y) - (v1._y * v2._x)};
	}

	/* project */
	template <typename T>
	inline constexpr auto project(const xns::vector3D<T>& v1, const xns::vector3D<T>& v2) noexcept -> xns::vector3D<T> {
		const auto dot = xns::dot(v1, v2);
		const auto mag = xns::dot(v2, v2);
		const auto val = dot / mag;
		return xns::vector3D<T>{val * v2._x,
								val * v2._y,
								val * v2._z};
	}

	/* reflect */
	template <typename T>
	inline constexpr auto reflect(const xns::vector3D<T>& v1, const xns::vector3D<T>& v2) noexcept -> xns::vector3D<T> {
		const auto dot = xns::dot(v1, v2);
		const auto val = 2 * dot;
		return xns::vector3D<T>{v1._x - (val * v2._x),
								v1._y - (val * v2._y),
								v1._z - (val * v2._z)};
	}
}

#endif // XNS_VECTOR3D_HPP
