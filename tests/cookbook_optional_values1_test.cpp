// The MIT License (MIT)
//
// Copyright (c) 2019 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>

#include <daw/daw_benchmark.h>
#include <daw/daw_memory_mapped_file.h>

#include "daw/json/daw_json_link.h"

namespace daw::cookbook_optional_values1 {
	struct MyOptionalStuff1 {
		std::optional<int> member0;
		std::string member1;
		std::unique_ptr<bool> member2;
	};

#if defined( __cpp_nontype_template_parameter_class )
	auto describe_json_class( MyOptionalStuff1 const & ) {
		using namespace daw::json;
		return class_description_t<
		  json_nullable<json_number<"member0", int>>, json_string<"member1">,
		  json_nullable<json_bool<"member2", bool, LiteralAsStringOpt::never,
		                          UniquePtrConstructor<bool>>>>{};
	}
#else
	namespace symbols_MyOptionalStuff1 {
		static constexpr char const member0[] = "member0";
		static constexpr char const member1[] = "member1";
		static constexpr char const member2[] = "member2";
	} // namespace symbols_MyOptionalStuff1
	auto describe_json_class( MyOptionalStuff1 const & ) {
		using namespace daw::json;
		return class_description_t<
		  json_nullable<json_number<symbols_MyOptionalStuff1::member0, int>>,
		  json_string<symbols_MyOptionalStuff1::member1>,
		  json_nullable<
		    json_bool<symbols_MyOptionalStuff1::member2, bool,
		              LiteralAsStringOpt::never, UniquePtrConstructor<bool>>>>{};
	}
#endif
	auto to_json_data( MyOptionalStuff1 const &value ) {
		return std::forward_as_tuple( value.member0, value.member1, value.member2 );
	}

	bool operator==( MyOptionalStuff1 const &lhs, MyOptionalStuff1 const &rhs ) {
		return to_json_data( lhs ) == to_json_data( rhs );
	}
} // namespace daw::cookbook_optional_values1

int main( int argc, char **argv ) {
	if( argc <= 1 ) {
		puts( "Must supply path to cookbook_optional_values1.json file\n" );
		exit( EXIT_FAILURE );
	}
	auto data = daw::filesystem::memory_mapped_file_t<>( argv[1] );

	auto stuff = daw::json::from_json_array<
	  daw::cookbook_optional_values1::MyOptionalStuff1>(
	  {data.data( ), data.size( )} );

	auto const str = daw::json::to_json_array( stuff );
	puts( str.c_str( ) );
	auto stuff2 = daw::json::from_json_array<
	  daw::cookbook_optional_values1::MyOptionalStuff1>(
	  {str.data( ), str.size( )} );
	daw::do_not_optimize( stuff );
	daw::do_not_optimize( stuff2 );
	 bool are_equal = stuff == stuff2;
	daw_json_assert( are_equal, "Unexpected round trip error" );

	return 0;
}
