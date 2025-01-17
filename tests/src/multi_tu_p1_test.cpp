// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link.h
//

#include <daw/json/daw_from_json.h>
#include <daw/json/daw_from_json_fwd.h>
#include <daw/json/daw_json_data_contract.h>
#include <daw/json/daw_json_default_constuctor_fwd.h>
#include <daw/json/daw_json_event_parser.h>
#include <daw/json/daw_json_exception.h>
#include <daw/json/daw_json_find_path.h>
#include <daw/json/daw_json_iostream.h>
#include <daw/json/daw_json_iterator.h>
#include <daw/json/daw_json_lines_iterator.h>
#include <daw/json/daw_json_link.h>
#include <daw/json/daw_json_link_types.h>
#include <daw/json/daw_json_parse_options.h>
#include <daw/json/daw_json_schema.h>
#include <daw/json/daw_json_serialize_options.h>
#include <daw/json/daw_json_switches.h>
#include <daw/json/daw_json_value_state.h>
#include <daw/json/daw_to_json.h>
#include <daw/json/daw_to_json_fwd.h>

#include <string>
#include <tuple>

struct Z {
	int y;
};

namespace daw::json {
	template<>
	struct json_data_contract<Z> {
		static constexpr char const y[] = "y";
		using type = json_member_list<json_number<y, int>>;

		[[nodiscard]] static constexpr auto to_json_data( Z const &x ) {
			return std::forward_as_tuple( x.y );
		}
	};
} // namespace daw::json

Z parse_Z( daw::string_view json ) {
	return daw::json::from_json<Z>( json );
}

std::string from_Z( Z const &x ) {
	return daw::json::to_json( x );
}
