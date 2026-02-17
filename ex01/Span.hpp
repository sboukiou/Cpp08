#ifndef SPAN_HPP
# define SPAN_HPP

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
		template <typename T>
		void	insert(int begin, int end) {
			while (begin < end) {
				addNumber(begin);
				begin += 1;
			}
		}
};

#endif /* SPAN_HPP */
