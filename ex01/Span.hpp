#ifndef SPAN_HPP
# define SPAN_HPP

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
};

#endif /* SPAN_HPP */
