#ifndef SPAN_HPP
# define SPAN_HPP

#include <stdexcept>
class Span {
	private:
		unsigned int	N;
		int				*values;
		int				cursor;
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
		void	insert(T begin, T end) {
			while (begin < end) {
				addNumber(begin);
				begin += 1;
			}
		}
};

#endif /* SPAN_HPP */
