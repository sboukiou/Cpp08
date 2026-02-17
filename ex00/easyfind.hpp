#ifndef EASYFIND_HPP
# define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>
template <typename T>
int	easyfind(const T &Param, int Num) {

	typename T::const_iterator num = std::find(Param.begin(), Param.end(), Num);
	if (num == Param.end())
		throw (std::out_of_range("No occurrence was found"));
	return (*num);
}

#endif /* EASYFIND_HPP */
