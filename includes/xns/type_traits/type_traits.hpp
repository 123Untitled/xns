/*****************************************************************************/
/*                       :::    ::: ::::    :::  ::::::::                    */
/*                      :+:    :+: :+:+:   :+: :+:    :+:                    */
/*                      +:+  +:+  :+:+:+  +:+ +:+                            */
/*                      +#++:+   +#+ +:+ +#+ +#++:++#++                      */
/*                    +#+  +#+  +#+  +#+#+#        +#+                       */
/*                  #+#    #+# #+#   #+#+# #+#    #+#                        */
/*                 ###    ### ###    ####  ########                          */
/*****************************************************************************/

#pragma once

#ifndef XNS_TYPE_TRAITS_HEADER
#define XNS_TYPE_TRAITS_HEADER


// -- T Y P E  T R A I T S ----------------------------------------------------


#endif // XNS_TYPE_TRAITS_HPP


// -- C L A N G / G C C  B U I L T I N S --------------------------------------

// __is_trivial (C++, GNU, Microsoft, Embarcadero)
// __is_trivially_assignable (C++, GNU, Microsoft)
// __is_trivially_constructible (C++, GNU, Microsoft)
// __is_trivially_copyable (C++, GNU, Microsoft)
// __is_trivially_destructible (C++, MSVC 2013)
// __is_trivially_relocatable (Clang): Returns true if moving an object of the given type, and then destroying the source object, is known to be functionally equivalent to copying the underlying bytes and then dropping the source object on the floor. This is true of trivial types and types which were made trivially relocatable via the clang::trivial_abi attribute.
// __is_trivially_equality_comparable (Clang): Returns true if comparing two objects of the provided type is known to be equivalent to comparing their value representations.

// __is_nothrow_assignable (C++, MSVC 2013)
// __is_nothrow_constructible (C++, MSVC 2013)
// __is_nothrow_destructible (C++, MSVC 2013)

// __array_rank(type) (Embarcadero):
// Returns the number of levels of array in the type type: 0 if type is not an array type, and __array_rank(element) + 1 if type is an array of element.

// __array_extent(type, dim) (Embarcadero): The dim’th array bound in the type type, or 0 if dim >= __array_rank(type).
// __can_pass_in_regs (C++) Returns whether a class can be passed in registers under the current ABI. This type can only be applied to unqualified class types. This is not a portable type trait.


// __has_unique_object_representations (C++, GNU)
// __has_virtual_destructor (C++, GNU, Microsoft, Embarcadero)
// __is_abstract (C++, GNU, Microsoft, Embarcadero)
// __is_aggregate (C++, GNU, Microsoft)
// __is_arithmetic (C++, Embarcadero)
// __is_array (C++, Embarcadero)
// __is_assignable (C++, MSVC 2015)
// __is_base_of (C++, GNU, Microsoft, Embarcadero)
// __is_bounded_array (C++, GNU, Microsoft, Embarcadero)
// __is_class (C++, GNU, Microsoft, Embarcadero)
// __is_complete_type(type) (Embarcadero): Return true if type is a complete type. Warning: this trait is dangerous because it can return different values at different points in the same program.
// __is_compound (C++, Embarcadero)
// __is_const (C++, Embarcadero)
// __is_constructible (C++, MSVC 2013)
// __is_convertible (C++, Embarcadero)
// __is_convertible_to (Microsoft): Synonym for __is_convertible.
// __is_destructible (C++, MSVC 2013)
// __is_empty (C++, GNU, Microsoft, Embarcadero)
// __is_enum (C++, GNU, Microsoft, Embarcadero)
// __is_final (C++, GNU, Microsoft)
// __is_floating_point (C++, Embarcadero)
// __is_function (C++, Embarcadero)
// __is_fundamental (C++, Embarcadero)
// __is_integral (C++, Embarcadero)
// __is_interface_class (Microsoft): Returns false, even for types defined with __interface.
// __is_literal (Clang): Synonym for __is_literal_type.
// __is_literal_type (C++, GNU, Microsoft): Note, the corresponding standard trait was deprecated in C++17 and removed in C++20.
// __is_lvalue_reference (C++, Embarcadero)
// __is_member_object_pointer (C++, Embarcadero)
// __is_member_function_pointer (C++, Embarcadero)
// __is_member_pointer (C++, Embarcadero)
// __is_nullptr (C++, GNU, Microsoft, Embarcadero): Returns true for std::nullptr_t and false for everything else. The corresponding standard library feature is std::is_null_pointer, but __is_null_pointer is already in use by some implementations.
// __is_object (C++, Embarcadero)
// __is_pod (C++, GNU, Microsoft, Embarcadero): Note, the corresponding standard trait was deprecated in C++20.
// __is_pointer (C++, Embarcadero)
// __is_polymorphic (C++, GNU, Microsoft, Embarcadero)
// __is_reference (C++, Embarcadero)
// __is_referenceable (C++, GNU, Microsoft, Embarcadero): Returns true if a type is referenceable, and false otherwise. A referenceable type is a type that’s either an object type, a reference type, or an unqualified function type.
// __is_rvalue_reference (C++, Embarcadero)
// __is_same (C++, Embarcadero)
// __is_same_as (GCC): Synonym for __is_same.
// __is_scalar (C++, Embarcadero)
// __is_scoped_enum (C++, GNU, Microsoft, Embarcadero)
// __is_sealed (Microsoft): Synonym for __is_final.
// __is_signed (C++, Embarcadero): Returns false for enumeration types, and returns true for floating-point types. Note, before Clang 10, returned true for enumeration types if the underlying type was signed, and returned false for floating-point types.
// __is_standard_layout (C++, GNU, Microsoft, Embarcadero)
// __is_unbounded_array (C++, GNU, Microsoft, Embarcadero)
// __is_union (C++, GNU, Microsoft, Embarcadero)
// __is_unsigned (C++, Embarcadero): Returns false for enumeration types. Note, before Clang 13, returned true for enumeration types if the underlying type was unsigned.
// __is_void (C++, Embarcadero)
// __is_volatile (C++, Embarcadero)
// __reference_binds_to_temporary(T, U) (Clang): Determines whether a reference of type T bound to an expression of type U would bind to a materialized temporary object. If T is not a reference type the result is false. Note this trait will also return false when the initialization of T from U is ill-formed. Deprecated, use __reference_constructs_from_temporary.
// __reference_constructs_from_temporary(T, U) (C++) Returns true if a reference T can be constructed from a temporary of type a non-cv-qualified U.
// __underlying_type (C++, GNU, Microsoft)
// __is_lvalue_expr(e) (Embarcadero): Returns true if e is an lvalue expression. Deprecated, use __is_lvalue_reference(decltype((e))) instead.
// __is_rvalue_expr(e) (Embarcadero): Returns true if e is a prvalue expression. Deprecated, use !__is_reference(decltype((e))) instead.

