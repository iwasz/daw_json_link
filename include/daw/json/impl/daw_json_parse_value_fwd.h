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

#pragma once

#include "daw_iterator_range.h"
#include "daw_json_parse_common.h"

namespace daw::json::impl {
	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Real>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Signed>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Unsigned>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Null>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Bool>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::String>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Date>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Custom>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Class>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::Array>,
	             IteratorRange<First, Last, TrustedInput> & );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::KeyValue>,
	             IteratorRange<First, Last, TrustedInput> &rng );

	template<typename JsonMember, typename First, typename Last,
	         bool TrustedInput>
	[[nodiscard]] static constexpr json_result<JsonMember>
	parse_value( ParseTag<JsonParseTypes::KeyValueArray>,
	             IteratorRange<First, Last, TrustedInput> &rng );
} // namespace daw::json::impl
