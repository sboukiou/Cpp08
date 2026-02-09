#include "./Span.hpp"
#include <climits>
#include <iostream>

Span::Span(void) {
	N = 0;
	cursor = 0;
	values = NULL;
}

Span::Span(int param) {
	if (param < 0)
		throw(std::out_of_range("Given size is negative!"));
	N = param;
	cursor = 0;
	values = new int [N];
	if (values == NULL)
		throw(std::runtime_error("Failed to allocate memory"));
	for (unsigned int i = 0; i < N; i += 1)
		values[i] = 0;
}

Span::Span(const Span &other) {
	if (other.values == NULL || other.N == 0)
		throw(std::runtime_error("Given copy is empty"));
	N = other.N;
	cursor = other.cursor;
	values = new int [N];
	if (values == NULL)
		throw(std::runtime_error("Failed to allocate memory"));
	for (unsigned int i = 0; i < N; i += 1)
		values[i] = other.values[i];
}

Span::~Span(void) {
	if (values != NULL)
		delete [] values;
}

Span	&Span::operator=(const Span &other) {
	if (other.values == NULL || other.N == 0)
		throw(std::runtime_error("Given copy is empty"));
	N = other.N;
	cursor = other.cursor;
	if (values != NULL)
		delete [] values;
	values = new int [N];
	if (values == NULL)
		throw(std::runtime_error("Failed to allocate memory"));
	for (unsigned int i = 0; i < N; i += 1)
		values[i] = other.values[i];
	return (*this);
}

void Span::addNumber(int param) {
	if (static_cast<unsigned int>(cursor) < N) {
		values[cursor] = param;
		cursor += 1;
	}
	else
		throw(std::out_of_range("Span already filled!"));
}

int Span::shortestSpan(void) {
	int result = INT_MAX;
	int temp;
	if (N < 2)
		throw(std::runtime_error("Span is too small!"));
	for (unsigned int i = 0; i < N; i += 1)
		for (unsigned int j = 0; j < N - 1; j += 1) {
			if (values[j] > values[j + 1]) {
				temp = values[j];
				values[j] = values[j + 1];
				values[j + 1] = temp;
			}
		}
	for (unsigned int i = 0; i < N - 1; i += 1) {
		if (values[i + 1] - values[i] < result)
			result = values[i + 1] - values[i];
	}
	return (result);
}

int Span::longestSpan(void) {
	int max = INT_MIN;
	int min = INT_MAX;
	int result;

	if (N < 2)
		throw(std::runtime_error("Span is too small!"));
	for (unsigned int i = 0; i < N; i += 1)
		if (values[i] > max)
			max = values[i];
	for (unsigned int i = 0; i < N; i += 1)
		if (values[i] < min)
			min = values[i];
	result = max - min;
	return (result);
}
