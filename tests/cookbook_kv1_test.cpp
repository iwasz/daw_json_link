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
#include <string>
#include <unordered_map>

#include <daw/daw_memory_mapped_file.h>

#include "daw/json/daw_json_link.h"

namespace daw::cookbook_kv1 {
	struct MyKeyValue1 {
		std::unordered_map<std::string, int> kv;
	};

#if defined( __cpp_nontype_template_parameter_class )
	auto describe_json_class( MyKeyValue1 const & ) {
		using namespace daw::json;
		return class_description_t<json_key_value<
		  "kv", std::unordered_map<std::string, int>, json_number<no_name, int>>>{};
	}
#else
	namespace symbols_MyKeyValue1 {
		static constexpr char const kv[] = "kv";
	} // namespace symbols_MyKeyValue1
	auto describe_json_class( MyKeyValue1 ) {
		using namespace daw::json;
		return class_description_t<json_key_value<
		  symbols_MyKeyValue1::kv, std::unordered_map<std::string, int>,
		  json_number<no_name, int>>>{};
	}
#endif
	auto to_json_data( MyKeyValue1 const &value ) {
		return std::forward_as_tuple( value.kv );
	}

	bool operator==( MyKeyValue1 const &lhs, MyKeyValue1 const &rhs ) {
		return lhs.kv == rhs.kv;
	}
} // namespace daw::cookbook_kv1

int main( int argc, char **argv ) {
	if( argc <= 1 ) {
		puts( "Must supply path to cookbook_kv1.json file\n" );
		exit( EXIT_FAILURE );
	}
	auto data = daw::filesystem::memory_mapped_file_t<>( argv[1] );

	auto kv = daw::json::from_json<daw::cookbook_kv1::MyKeyValue1>(
	  std::string_view( data.data( ), data.size( ) ) );

	daw::json::json_assert( kv.kv.size( ) == 2, "Expected data to have 2 items" );
	daw::json::json_assert( kv.kv["key0"] == 353434, "Unexpected value" );
	daw::json::json_assert( kv.kv["key1"] == 314159, "Unexpected value" );
	auto const str = daw::json::to_json( kv );
	puts( str.c_str( ) );
	auto const kv2 = daw::json::from_json<daw::cookbook_kv1::MyKeyValue1>(
	  std::string_view( str.data( ), str.size( ) ) );

	daw::json::json_assert( kv == kv2, "Unexpected round trip error" );
}
