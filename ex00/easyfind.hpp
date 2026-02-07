#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <stdexcept>
template <typename T>

int	easyfind(T Param, int Num) {

	for (size_t i = 0; i < Param.size(); i += 1)
		if (Param[i] == Num)
			return (i);
	throw (std::out_of_range("No occurence was found"));
}

#endif /* EASYFIND_HPP */
