#include "../src/perr.h"

int const colwidth = 20;

int main() {
	std::array< int, 4 >            my_arr  = {{1, 2, 3, 4}};
	std::vector< int >              my_vec  = {1, 2, 3, 4};
	std::list< int >                my_lst  = {1, 2, 3, 4};
	std::set< int >                 my_set  = {1, 2, 3, 4};
	std::multiset< int >            my_mset = {1, 1, 2, 2};
	std::map< char, int >           my_map  = {{'a', 1}, {'c', 2}};
	std::unordered_set< int >       my_uset = {1, 2, 3, 4};
	std::unordered_map< char, int > my_umap = {{'a', 1}, {'c', 2}};

	perr << std::setw(colwidth) << "Array "         << " ┇  " << my_arr;
	perr << std::setw(colwidth) << "Vector "        << " ┇  " << my_vec;
	perr << std::setw(colwidth) << "List "          << " ┇  " << my_lst;
	perr << std::setw(colwidth) << "Set "           << " ┇  " << my_set;
	perr << std::setw(colwidth) << "Multiset "      << " ┇ "  << my_mset;
	perr << std::setw(colwidth) << "Unordered Set " << " ┇  " << my_uset;
	perr << std::setw(colwidth) << "Map "           << " ┇  " << my_map;
	perr << std::setw(colwidth) << "Unordered Map " << " ┇  " << my_umap;
};
