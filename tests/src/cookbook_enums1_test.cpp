// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//
// See cookbook/enums.md for the 1st example
//

#include "defines.h"

#include "daw/json/daw_json_link.h"

#include <daw/daw_read_file.h>
#include <daw/daw_utility.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

namespace daw::cookbook_enums1 {
	enum class Colours : uint8_t { red, green, blue, black };

	DAW_CONSTEXPR std::string_view to_string( Colours c ) {
		switch( c ) {
		case Colours::red:
			return "red";
		case Colours::green:
			return "green";
		case Colours::blue:
			return "blue";
		case Colours::black:
			return "black";
		}
		std::terminate( );
	}

	DAW_CONSTEXPR Colours from_string( daw::tag_t<Colours>,
	                                   std::string_view sv ) {
		if( sv == "red" ) {
			return Colours::red;
		}
		if( sv == "green" ) {
			return Colours::green;
		}
		if( sv == "blue" ) {
			return Colours::blue;
		}
		if( sv == "black" ) {
			return Colours::black;
		}
		std::terminate( );
	}

	struct MyClass1 {
		std::vector<Colours> member0;
	};

	bool operator==( MyClass1 const &lhs, MyClass1 const &rhs ) {
		return lhs.member0 == rhs.member0;
	}
} // namespace daw::cookbook_enums1

namespace daw::json {
	template<>
	struct json_data_contract<daw::cookbook_enums1::MyClass1> {
#ifdef DAW_JSON_CNTTP_JSON_NAME
		using type = json_member_list<json_array<
		  "member0", json_custom_no_name<daw::cookbook_enums1::Colours>>>;
#else
		constexpr inline static char const member0[] = "member0";
		using type = json_member_list<
		  json_array<member0, json_custom_no_name<daw::cookbook_enums1::Colours>>>;
#endif
		static inline auto
		to_json_data( daw::cookbook_enums1::MyClass1 const &value ) {
			return std::forward_as_tuple( value.member0 );
		}
	};
} // namespace daw::json

int main( int argc, char **argv )
#ifdef DAW_USE_EXCEPTIONS
  try
#endif
{
	if( argc <= 1 ) {
		puts( "Must supply path to cookbook_enums1.json file\n" );
		exit( EXIT_FAILURE );
	}
	auto data = *daw::read_file( argv[1] );

	auto const cls = daw::json::from_json<daw::cookbook_enums1::MyClass1>(
	  std::string_view( data.data( ), data.size( ) ) );

	test_assert( cls.member0[0] == daw::cookbook_enums1::Colours::red,
	             "Unexpected value" );
	test_assert( cls.member0[1] == daw::cookbook_enums1::Colours::green,
	             "Unexpected value" );
	test_assert( cls.member0[2] == daw::cookbook_enums1::Colours::blue,
	             "Unexpected value" );
	test_assert( cls.member0[3] == daw::cookbook_enums1::Colours::black,
	             "Unexpected value" );
	auto const str = daw::json::to_json( cls );
	puts( str.c_str( ) );

	auto const cls2 = daw::json::from_json<daw::cookbook_enums1::MyClass1>(
	  std::string_view( str.data( ), str.size( ) ) );

	test_assert( cls == cls2, "Unexpected round trip error" );
}
#ifdef DAW_USE_EXCEPTIONS
catch( daw::json::json_exception const &jex ) {
	std::cerr << "Exception thrown by parser: " << jex.reason( ) << '\n';
	exit( 1 );
} catch( std::exception const &ex ) {
	std::cerr << "Unknown exception thrown during testing: " << ex.what( )
	          << '\n';
	exit( 1 );
} catch( ... ) {
	std::cerr << "Unknown exception thrown during testing\n";
	throw;
}
#endif