#ifndef SPAN_HPP
# define SPAN_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>
class Span {
	private:
		unsigned int	N;
		std::vector<int>		values;
	public:
		Span(void);
		Span(int param);
		Span(const Span &other);
		~Span(void);
		Span&	operator=(const Span &other);
		void	addNumber(int number);
		int		shortestSpan(void);
		int		longestSpan(void);
		template <typename It>
		void insert(It begin, It end) {
			const size_t	count = std::distance(begin, end);
			if (values.size() + count > N)
				throw(std::out_of_range("Range is out of bounds!"));
			values.insert(values.end(), begin, end);
		}
};

#endif /* SPAN_HPP */
