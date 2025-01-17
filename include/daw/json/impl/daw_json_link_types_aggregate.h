// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#pragma once

#include "version.h"

#include "daw_json_enums.h"
#include <daw/daw_tuple_forward.h>

#include <daw/daw_attributes.h>
#include <daw/daw_traits.h>

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace daw::json {
	inline namespace DAW_JSON_VER {
		namespace json_details {
			// A type that can be implicitly converted to *anything*
			struct Anything {
				template<typename T>
				operator T( ) const; // We don't need to define this function
			};

			template<typename T, typename Is, typename = void>
			inline constexpr bool is_aggregate_constructible_from_n_impl_v = false;

			template<typename T, std::size_t... Is>
			inline constexpr bool is_aggregate_constructible_from_n_impl_v<
			  T, std::index_sequence<Is...>,
			  std::void_t<decltype( T{ ( void( Is ), Anything{ } )... } )>> = true;

			template<typename T, std::size_t N>
			inline constexpr bool is_aggregate_constructible_from_n_v =
			  is_aggregate_constructible_from_n_impl_v<T,
			                                           std::make_index_sequence<N>>;

			template<typename... Ts>
			void tp_from_struct_binding( std::tuple<Ts...> );

			template<typename T>
			constexpr auto tp_from_struct_binding( T &&value ) {
				using type = daw::remove_cvref_t<T>;
				static_assert( std::is_class_v<type> and std::is_aggregate_v<type> );
				if constexpr( is_aggregate_constructible_from_n_v<type, 16> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13,
					        x14, x15] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ), DAW_FWD( x10 ), DAW_FWD( x11 ),
					  DAW_FWD( x12 ), DAW_FWD( x13 ), DAW_FWD( x14 ), DAW_FWD( x15 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 15> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13,
					        x14] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ), DAW_FWD( x10 ), DAW_FWD( x11 ),
					  DAW_FWD( x12 ), DAW_FWD( x13 ), DAW_FWD( x14 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 14> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13] =
					  DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ), DAW_FWD( x10 ), DAW_FWD( x11 ),
					  DAW_FWD( x12 ), DAW_FWD( x13 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 13> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12] =
					  DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ), DAW_FWD( x10 ), DAW_FWD( x11 ),
					  DAW_FWD( x12 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 12> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11] =
					  DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ), DAW_FWD( x10 ), DAW_FWD( x11 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 11> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10] =
					  DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ), DAW_FWD( x10 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 10> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8, x9] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ), DAW_FWD( x9 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 9> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7, x8] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ),
					  DAW_FWD( x8 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 8> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6, x7] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ), DAW_FWD( x7 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 7> ) {
					auto &&[x0, x1, x2, x3, x4, x5, x6] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ), DAW_FWD( x6 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 6> ) {
					auto &&[x0, x1, x2, x3, x4, x5] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ),
					  DAW_FWD( x4 ), DAW_FWD( x5 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 5> ) {
					auto &&[x0, x1, x2, x3, x4] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple( DAW_FWD( x0 ), DAW_FWD( x1 ),
					                                        DAW_FWD( x2 ), DAW_FWD( x3 ),
					                                        DAW_FWD( x4 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 4> ) {
					auto &&[x0, x1, x2, x3] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple(
					  DAW_FWD( x0 ), DAW_FWD( x1 ), DAW_FWD( x2 ), DAW_FWD( x3 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 3> ) {
					auto &&[x0, x1, x2] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple( DAW_FWD( x0 ), DAW_FWD( x1 ),
					                                        DAW_FWD( x2 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 2> ) {
					auto &&[x0, x1] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple( DAW_FWD( x0 ),
					                                        DAW_FWD( x1 ) );
				} else if constexpr( is_aggregate_constructible_from_n_v<type, 1> ) {
					auto &&[x0] = DAW_FWD( value );
					return daw::forward_nonrvalue_as_tuple( DAW_FWD( x0 ) );
				}
			}

			template<typename T>
			inline constexpr bool can_convert_to_tuple_v =
			  not std::is_same_v<void, decltype( tp_from_struct_binding(
			                             std::declval<T>( ) ) )>;

			template<typename T>
			using tp_from_struct_binding_result_t =
			  daw::remove_cvref_t<decltype( tp_from_struct_binding(
			    std::declval<T>( ) ) )>;
		} // namespace json_details
	}   // namespace DAW_JSON_VER
} // namespace daw::json
