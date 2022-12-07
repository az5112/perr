#include "../src/perr.h"

int const colwidth = 22;

int main() {
	std::array< int, 4 >                 my_arr   = {{1, 2, 3, 4}};
	std::vector< int >                   my_vec   = {1, 2, 3, 4};
	std::list< int >                     my_lst   = {1, 2, 3, 4};
	std::set< int >                      my_set   = {1, 2, 3, 4};
	std::multiset< int >                 my_mset  = {1, 1, 2, 2};
	std::map< char, int >                my_map   = {{'a', 1}, {'b', 2}, {'c', 3}};
	std::multimap< char, int >           my_mmap  = {{'a', 1}, {'a', 2}, {'b', 3}};
	std::unordered_set< int >            my_uset  = {1, 2, 3, 4};
	std::unordered_multiset< int >       my_umset = {1, 2, 2, 2};
	std::unordered_map< char, int >      my_umap  = {{'a', 1}, {'c', 2}};
	std::unordered_multimap< char, int > my_ummap = {{'a', 1}, {'a', 2}};

	perr << std::setw(colwidth) << "Array "              << " ┇ " << my_arr;
	perr << std::setw(colwidth) << "Vector "             << " ┇ " << my_vec;
	perr << std::setw(colwidth) << "List "               << " ┇ " << my_lst;
	perr << std::setw(colwidth) << "Set "                << " ┇ " << my_set;
	perr << std::setw(colwidth) << "Multiset "           << " ┇ " << my_mset;
	perr << std::setw(colwidth) << "Map "                << " ┇ " << my_map;
	perr << std::setw(colwidth) << "Multimap "           << " ┇ " << my_mmap;
	perr << std::setw(colwidth) << "Unordered Set "      << " ┇ " << my_uset;
	perr << std::setw(colwidth) << "Unordered Multiset " << " ┇ " << my_umset;
	perr << std::setw(colwidth) << "Unordered Map "      << " ┇ " << my_umap;
	perr << std::setw(colwidth) << "Unordered Multimap " << " ┇ " << my_ummap;
};
