#ifndef _PERR_H_
#define _PERR_H_

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <format>

#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#define perr PrettyStream(std::cerr, __PRETTY_FUNCTION__, __FILE__, __LINE__).stream()

struct ESCAPE {
#ifdef NOCOLOR
	inline static std::string_view const red     = "";
	inline static std::string_view const green   = "";
	inline static std::string_view const yellow  = "";
	inline static std::string_view const blue    = "";
	inline static std::string_view const magenta = "";
	inline static std::string_view const cyan    = "";
	inline static std::string_view const nocolor = "";
#else
	inline static std::string_view const red     = "\E[00;31m";
	inline static std::string_view const green   = "\E[00;32m";
	inline static std::string_view const yellow  = "\E[00;33m";
	inline static std::string_view const blue    = "\E[00;34m";
	inline static std::string_view const magenta = "\E[00;35m";
	inline static std::string_view const cyan    = "\E[00;36m";
	inline static std::string_view const nocolor = "\E[0m";
#endif
};

struct Config {
	inline static const int line_number_width = 5;
	inline static const std::string_view source_point_separator = " : ";
	inline static const std::string_view source_point_color = ESCAPE::blue;
	inline static const std::string_view non_value_color = ESCAPE::cyan;
	inline static const std::string_view no_color = ESCAPE::nocolor;
};

using VALUES_T = char;
using KEY_VALUES_T = int;

struct ArrayWriter {
	inline static std::string_view tag = "A";
	inline static std::string_view open_mark = "[";
	inline static std::string_view close_mark = "]";
	inline static std::string_view elem_separator = ", ";
	using vkv = VALUES_T;
};

struct VectorWriter {
	inline static std::string_view tag = "V";
	inline static std::string_view open_mark = "[";
	inline static std::string_view close_mark = "]";
	inline static std::string_view elem_separator = ", ";
	using vkv = VALUES_T;
};

struct ListWriter {
	inline static std::string_view tag = "L";
	inline static std::string_view open_mark = "(";
	inline static std::string_view close_mark = ")";
	inline static std::string_view elem_separator = " -> ";
	using vkv = VALUES_T;
};

struct SetWriter {
	inline static std::string_view tag = "S";
	inline static std::string_view open_mark = "<";
	inline static std::string_view close_mark = ">";
	inline static std::string_view elem_separator = ", ";
	using vkv = VALUES_T;
};

struct MapWriter {
	inline static std::string_view tag = "M";
	inline static std::string_view open_mark = "<";
	inline static std::string_view close_mark = ">";
	inline static std::string_view elem_separator = ", ";
	inline static std::string_view key_value_separator = " : ";
	using vkv = KEY_VALUES_T;
};

struct UnorderedSetWriter {
	inline static std::string_view tag = "s";
	inline static std::string_view open_mark = "{";
	inline static std::string_view close_mark = "}";
	inline static std::string_view elem_separator = ", ";
	using vkv = VALUES_T;
};

struct UnorderedMapWriter {
	inline static std::string_view tag = "m";
	inline static std::string_view open_mark = "{";
	inline static std::string_view close_mark = "}";
	inline static std::string_view elem_separator = ", ";
	inline static std::string_view key_value_separator = " : ";
	using vkv = KEY_VALUES_T;
};



/* count (recursively) the total length of multiple std::string_views */
template< typename SV >
size_t sv_length(SV const& sv) {
	return sv.size();
}

template< typename SV, typename ...Args >
size_t sv_length(SV const& sv, Args const& ... args) {
	return sv.size() + sv_length(args...);
}

/* write out (recursively) multiple std::string_view's */
template< typename SV >
std::ostream& write_many(std::ostream& os, SV const& sv) {
	os << sv;
	return os;
}

template< typename SV, typename ...Args >
std::ostream& write_many(std::ostream& os, SV const& sv, Args const& ... args) {
	write_many(os, sv);
	write_many(os, args...);
	return os;
}

/* write std::string_views wrapped up in a color escape sequence */
template < typename... T >
std::ostream& write_color(std::ostream& os, std::string_view const& color, T const& ...sv) {
	int total_length = sv_length(sv...);

	if (total_length == 0) {
		// nothing to do
	}
	else if (color.size() == 0) {
		write_many(os, sv...);
	}
	else {
		os << color;
		write_many(os, sv...);
		os << ESCAPE::nocolor;
	}

	return os;
};

class PrettyStream {
	std::ostream& os;
	std::string const& pretty_func;
	std::string const& file_name;
	int line_number;
public:
	PrettyStream(
		std::ostream& os,
		std::string const& pretty_func,
		std::string const& file_name,
		int line_number
	):
		os(os),
		pretty_func(pretty_func),
		file_name(file_name),
		line_number(line_number)
	{};

	~PrettyStream() {
		os << std::endl;
	}

	std::ostream& stream()
	{	
		// std::format not yet available.
		std::stringstream sstr;
		sstr
			<< std::setw(Config::line_number_width)
			<< std::left
			<< line_number;

		// sstr.view() not yet available.
		write_color(os, Config::source_point_color, file_name, Config::source_point_separator, sstr.str());
		return os;
	}
};

template< typename VALUE_T >
struct QUOTE {
	inline static std::string_view CHAR = "";
};

template< > inline std::string_view QUOTE< std::string_view >::CHAR = "\"";
template< > inline std::string_view QUOTE< std::string      >::CHAR = "\"";
template< > inline std::string_view QUOTE< const char*      >::CHAR = "\"";
template< > inline std::string_view QUOTE< char             >::CHAR = "\'"; // single quote

template< typename CONTAINER, typename CNFO >
struct Writer;

template< typename value_type, size_t N >
std::ostream& operator<<(std::ostream& os, std::array< value_type, N > a) {
	return Writer<
		std::array< value_type, N >, ArrayWriter
	> {}.write(os, a);
}

template< typename value_type, typename allocator_type >
std::ostream& operator<<(std::ostream& os, std::vector< value_type, allocator_type > v) {
	return Writer<
		std::vector< value_type, allocator_type >, VectorWriter
	> {}.write(os, v);
}

template< typename value_type, typename allocator_type >
std::ostream& operator<<(std::ostream& os, std::list< value_type, allocator_type > l) {
	return Writer<
		std::list< value_type, allocator_type >, ListWriter
	> {}.write(os, l);
}

template< typename key_type, typename compare_type, typename allocator_type >
std::ostream& operator<<(std::ostream& os, std::set< key_type, compare_type, allocator_type > s) {
	return Writer<
		std::set< key_type, compare_type, allocator_type >, SetWriter
	> {}.write(os, s);
}

template< typename key_type, typename mapped_type, typename key_compare, typename allocator_type >
std::ostream& operator<<(std::ostream& os, std::map< key_type, mapped_type, key_compare, allocator_type > m) {
	return Writer<
		std::map< key_type, mapped_type, key_compare, allocator_type >, MapWriter
	> {}.write(os, m);
}

template< typename key_type, typename hasher, typename key_equal, typename allocator_type >
std::ostream& operator<<(std::ostream& os, std::unordered_set< key_type, hasher, key_equal, allocator_type > s) {
	return Writer<
		std::unordered_set< key_type, hasher, key_equal, allocator_type >, UnorderedSetWriter
	> {}.write(os, s);
}

template< typename key_type, typename mapped_type, typename hasher, typename key_equal, typename allocator_type >
std::ostream& operator<<(std::ostream& os, std::unordered_map< key_type, mapped_type, hasher, key_equal, allocator_type > m) {
	return Writer<
		std::unordered_map< key_type, mapped_type, hasher, key_equal, allocator_type >, UnorderedMapWriter
	> {}.write(os, m);
}

template< typename CONTAINER, typename CNFO >
struct Writer {
	std::ostream& write(std::ostream& os, CONTAINER cont) {
		return _write< typename CNFO::vkv >(os, cont);
	};
private:
	std::ostream& _write_container_start(std::ostream& os) const {
		return write_color(os, Config::non_value_color, CNFO::tag, CNFO::open_mark);
	}

	std::ostream& _write_container_end(std::ostream& os) const {
		return write_color(os, Config::non_value_color, CNFO::close_mark);
	}

	template< typename VKV >
	std::ostream& _write(std::ostream& os, CONTAINER cont);

	template< >
	std::ostream& _write< VALUES_T  >(std::ostream& os, CONTAINER cont) {
		std::string_view const quote = QUOTE< typename CONTAINER::value_type >::CHAR;
		int const sz = cont.size();
		int cnt = 0;

		_write_container_start(os);

		for (auto el: cont) {
			++cnt;
			write_color(os, Config::non_value_color, quote);
			os << el;
			write_color(os, Config::non_value_color, quote, (cnt == sz) ? "" : CNFO::elem_separator);
		}

		_write_container_end(os);
		return os;
	}

	template< >
	std::ostream& _write< KEY_VALUES_T >(std::ostream& os, CONTAINER cont) {
		std::string_view const quote = QUOTE< typename CONTAINER::key_type >::CHAR;

		int const sz = cont.size();
		int cnt = 0;

		_write_container_start(os);
		for (auto el: cont) {
			++cnt;
			write_color(os, Config::non_value_color, quote);
			os << el.first;
			write_color(os, Config::non_value_color, quote, CNFO::key_value_separator, quote);
			os << el.second;
			write_color(os, Config::non_value_color, quote, (cnt == sz) ? "" : CNFO::elem_separator);
		}

		_write_container_end(os);
		return os;
	}
};

#endif
