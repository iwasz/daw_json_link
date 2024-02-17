// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#pragma once

#include <daw/json/impl/version.h>

#include "daw_writable_output_fwd.h"
#include <daw/json/impl/daw_json_assert.h>

#include <daw/daw_algorithm.h>
#include <daw/daw_character_traits.h>
#include <daw/daw_string_view.h>

#include <cstdio>
// #include <iostream>
#include <string>

namespace daw::json {
	inline namespace DAW_JSON_VER {
		namespace concepts {
			namespace writeable_output_details {
				template<typename T>
				constexpr T *copy_to_buffer( T *buff, daw::string_view source ) {
#if defined( DAW_IS_CONSTANT_EVALUATED )
					if( DAW_IS_CONSTANT_EVALUATED( ) ) {
#endif
						daw::algorithm::transform_n( source.data( ), buff, source.size( ),
						                             []( auto c ) {
							                             return static_cast<T>( c );
						                             } );
#if defined( DAW_IS_CONSTANT_EVALUATED )
					} else {
						memcpy( buff, source.data( ), source.size( ) );
					}
#endif
					return buff + source.size( );
				}

				template<typename T>
				inline constexpr bool is_byte_type_v =
				  std::is_same_v<T, std::byte> or std::is_same_v<T, unsigned char>;

				template<typename T>
				using is_char_sized = std::bool_constant<sizeof( T ) == 1>;

				template<typename T>
				inline constexpr bool is_char_sized_character_v = false;

				template<>
				inline constexpr bool is_char_sized_character_v<char> = true;

#if defined( __cpp_lib_char8_t )
#if __cpp_lib_char8_t >= 201907L
				template<>
				inline constexpr bool is_char_sized_character_v<char8_t> = true;
#endif
#endif
			} // namespace writeable_output_details

			/// @brief Specialization for character pointer
			template<typename T>
			struct writable_output_trait<
			  T *, std::enable_if_t<(
			         writeable_output_details::is_char_sized_character_v<T> or
			         writeable_output_details::is_byte_type_v<T> )>>
			  : std::true_type {

				template<typename... StringViews>
				static constexpr void write( T *&ptr, StringViews const &...svs ) {
					static_assert( sizeof...( StringViews ) > 0 );
					daw_json_ensure( ptr, daw::json::ErrorReason::OutputError );
					constexpr auto writer = []( T *&p, auto sv ) {
						if( sv.empty( ) ) {
							return 0;
						}
						p = writeable_output_details::copy_to_buffer( p, sv );
						return 0;
					};
					(void)( writer( ptr, svs ) | ... );
				}

				static constexpr void put( T *&ptr, char c ) {
					daw_json_ensure( ptr, daw::json::ErrorReason::OutputError );
					*ptr = static_cast<T>( c );
					++ptr;
				}
			};

			/// @brief Specialization for ostream &
			template<typename T>
			struct writable_output_trait<
			  T, std::enable_if_t<std::is_base_of_v<std::ostream, T>>>
			  : std::true_type {

				template<typename... StringViews>
				static inline void write( std::ostream &os,
				                          StringViews const &...svs ) {
					static_assert( sizeof...( StringViews ) > 0 );
					constexpr auto writer = []( std::ostream &o, auto sv ) {
						if( sv.empty( ) ) {
							return 0;
						}
						o.write( sv.data( ), static_cast<std::streamsize>( sv.size( ) ) );
						daw_json_ensure( static_cast<bool>( o ),
						                 daw::json::ErrorReason::OutputError );
						return 0;
					};
					(void)( writer( os, svs ) | ... );
				}

				static inline void put( std::ostream &os, char c ) {
					os.put( c );
					daw_json_ensure( static_cast<bool>( os ),
					                 daw::json::ErrorReason::OutputError );
				}
			};

			/// @brief Specialization for FILE * streams
			template<>
			struct writable_output_trait<std::FILE *> : std::true_type {

				template<typename... StringViews>
				static inline void write( std::FILE *fp, StringViews const &...svs ) {
					static_assert( sizeof...( StringViews ) > 0 );
					constexpr auto writer = []( std::FILE *f, auto sv ) {
						if( sv.empty( ) ) {
							return 0;
						}
						auto ret = std::fwrite( sv.data( ), 1, sv.size( ), f );
						daw_json_ensure( ret == sv.size( ),
						                 daw::json::ErrorReason::OutputError );
						return 0;
					};
					(void)( writer( fp, svs ) | ... );
				}

				static inline void put( std::FILE *f, char c ) {
					auto ret = std::fputc( c, f );
					daw_json_ensure( ret == c, daw::json::ErrorReason::OutputError );
				}
			};

			namespace writeable_output_details {
				template<typename T, typename CharT>
				using span_like_range_test =
				  decltype( (void)( std::declval<T &>( ).subspan( 1 ) ),
				            (void)( std::declval<std::size_t &>( ) =
				                      std::declval<T &>( ).size( ) ),
				            (void)( std::declval<bool &>( ) =
				                      std::declval<T &>( ).empty( ) ),
				            (void)( *std::declval<T &>( ).data( ) =
				                      std::declval<CharT>( ) ) );
				template<typename T, typename CharT>
				inline constexpr bool is_span_like_range_v =
				  daw::is_detected_v<span_like_range_test, T, CharT> and
				  ( writeable_output_details::is_char_sized_character_v<CharT> or
				    writeable_output_details::is_byte_type_v<CharT> );
			} // namespace writeable_output_details

			/// @brief Specialization for a span to a buffer with a fixed size
			template<typename T>
			struct writable_output_trait<
			  T, std::enable_if_t<writeable_output_details::is_span_like_range_v<
			       T, typename T::value_type>>> : std::true_type {
				using CharT = typename T::value_type;

				template<typename... StringViews>
				static constexpr void write( T &out, StringViews const &...svs ) {
					static_assert( sizeof...( StringViews ) > 0 );
					daw_json_ensure( out.size( ) >= ( std::size( svs ) + ... ),
					                 daw::json::ErrorReason::OutputError );
					constexpr auto writer = []( T &s, auto sv ) {
						if( sv.empty( ) ) {
							return 0;
						}
						(void)writeable_output_details::copy_to_buffer( s.data( ), sv );
						s = s.subspan( sv.size( ) );
						return 0;
					};
					(void)( writer( out, svs ) | ... );
				}

				static constexpr void put( T &out, char c ) {
					daw_json_ensure( not out.empty( ),
					                 daw::json::ErrorReason::OutputError );
					*out.data( ) = static_cast<CharT>( c );
					out.remove_prefix( 1 );
				}
			};

			namespace writeable_output_details {
				template<typename T, typename CharT>
				using resizable_contiguous_range_test =
				  decltype( (void)( std::declval<T &>( ).resize( std::size_t{ 0 } ) ),
				            (void)( std::declval<T &>( ).size( ) ),
				            (void)( *std::declval<T &>( ).data( ) ),
				            (void)( *std::declval<T &>( ).data( ) =
				                      std::declval<CharT>( ) ),
				            (void)( std::declval<T &>( ).push_back(
				              std::declval<CharT>( ) ) ),
				            (void)( static_cast<CharT>( 'a' ) ) );

				template<typename Container, typename CharT>
				inline constexpr bool is_resizable_contiguous_range_v =
				  daw::is_detected_v<resizable_contiguous_range_test, Container, CharT>;

				template<typename Container, typename CharT>
				inline constexpr bool is_string_like_writable_output_v =
				  (writeable_output_details::is_char_sized_character_v<CharT> or
				   writeable_output_details::is_byte_type_v<
				     CharT>)and writeable_output_details::
				    is_resizable_contiguous_range_v<Container, CharT>;
			} // namespace writeable_output_details

			/// @brief Specialization for a resizable continain like vector/string
			template<typename Container>
			struct writable_output_trait<
			  Container, std::enable_if_t<
			               writeable_output_details::is_string_like_writable_output_v<
			                 Container, typename Container::value_type>>>
			  : std::true_type {
				using CharT = typename Container::value_type;

				template<typename... StringViews>
				static inline void write( Container &out, StringViews const &...svs ) {
					static_assert( sizeof...( StringViews ) > 0 );
					auto const start_pos = out.size( );
					auto const total_size = ( std::size( svs ) + ... );
					out.resize( start_pos + total_size );

					constexpr auto writer = []( CharT *&p, auto sv ) {
						if( sv.empty( ) ) {
							return 0;
						}
						p = writeable_output_details::copy_to_buffer( p, sv );
						return 0;
					};
					auto *ptr = out.data( ) + start_pos;
					(void)( writer( ptr, svs ) | ... );
				}

				static inline void put( Container &out, char c ) {
					out.push_back( static_cast<CharT>( c ) );
				}
			};

			namespace writeable_output_details {
				template<typename T>
				using is_writable_output_iterator_test =
				  decltype( *std::declval<T &>( ) = 'c', ++std::declval<T &>( ) );

				template<typename T>
				inline constexpr bool is_writable_output_iterator_v =
				  not std::is_pointer_v<T> and
				  daw::is_detected_v<is_writable_output_iterator_test, T>;
			} // namespace writeable_output_details

			/// @brief Specialization for output iterators
			template<typename T>
			struct writable_output_trait<
			  T, std::enable_if_t<
			       writeable_output_details::is_writable_output_iterator_v<T>>>
			  : std::true_type {

				template<typename... StringViews>
				static constexpr void write( T &it, StringViews const &...svs ) {
					static_assert( sizeof...( StringViews ) > 0 );

					constexpr auto writer = []( T &i, auto sv ) {
						for( char c : daw::string_view( sv ) ) {
							*i = c;
							++i;
						}
						return 0;
					};
					(void)( writer( it, svs ) | ... );
				}

				static constexpr void put( T &it, char c ) {
					*it = c;
					++it;
				}
			};
		} // namespace concepts
	}   // namespace DAW_JSON_VER
} // namespace daw::json
