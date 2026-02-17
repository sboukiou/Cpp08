#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Span.hpp"

#define CLR_RED   "\033[31m"
#define CLR_GRN   "\033[32m"
#define CLR_YEL   "\033[33m"
#define CLR_RST   "\033[0m"

static int g_total = 0;
static int g_pass  = 0;

static void title(const std::string& t)
{
	std::cout << "\n" << CLR_YEL << "=== " << t << " ===" << CLR_RST << "\n";
}

static void report(bool ok, const std::string& what)
{
	++g_total;
	if (ok) {
		++g_pass;
		std::cout << CLR_GRN << "[OK] " << CLR_RST << what << "\n";
	} else {
		std::cout << CLR_RED << "[KO] " << CLR_RST << what << "\n";
	}
}

#define EXPECT_TRUE(expr) \
	do { \
		bool _ok = (expr); \
		std::ostringstream _oss; \
		_oss << #expr; \
		report(_ok, _oss.str()); \
	} while (0)

#define EXPECT_EQ(a, b) \
	do { \
		long _av = (a); \
		long _bv = (b); \
		bool _ok = (_av == _bv); \
		std::ostringstream _oss; \
		_oss << #a << " == " << #b << " (got " << _av << ", expected " << _bv << ")"; \
		report(_ok, _oss.str()); \
	} while (0)

#define EXPECT_THROW(stmt) \
	do { \
		bool _thrown = false; \
		try { (void)(stmt); } catch (const std::exception&) { _thrown = true; } \
		std::ostringstream _oss; \
		_oss << "throws: " << #stmt; \
		report(_thrown, _oss.str()); \
	} while (0)

static void test_subject_example()
{
	title("subject example (Span(5))");
	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	EXPECT_EQ(sp.shortestSpan(), 2);  // 9-11 or 6-3? sorted -> [3,6,9,11,17] => min diff = 2
	EXPECT_EQ(sp.longestSpan(), 14);  // 17 - 3
}

static void test_too_small_exceptions()
{
	title("exceptions: span too small");
	Span sp(5);
	EXPECT_THROW(sp.shortestSpan());
	EXPECT_THROW(sp.longestSpan());

	sp.addNumber(42);
	EXPECT_THROW(sp.shortestSpan());
	EXPECT_THROW(sp.longestSpan());
}

static void test_addNumber_overflow()
{
	title("exceptions: addNumber overflow");
	Span sp(2);
	sp.addNumber(1);
	sp.addNumber(2);
	EXPECT_THROW(sp.addNumber(3));
}

static void test_iterator_insert_vector_ok()
{
	title("iterator insert: vector ok");
	Span sp(5);

	std::vector<int> v;
	v.push_back(6);
	v.push_back(3);
	v.push_back(17);
	v.push_back(9);
	v.push_back(11);

	sp.insert(v.begin(), v.end());
	EXPECT_EQ(sp.shortestSpan(), 2);
	EXPECT_EQ(sp.longestSpan(), 14);
}

static void test_iterator_insert_overflow()
{
	title("iterator insert: overflow");
	Span sp(3);

	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	EXPECT_THROW(sp.insert(v.begin(), v.end()));
}

static void test_iterator_insert_list()
{
	title("iterator insert: list");
	Span sp(6);

	std::list<int> l;
	l.push_back(-10);
	l.push_back(-10);
	l.push_back(0);
	l.push_back(5);
	l.push_back(20);
	l.push_back(21);

	sp.insert(l.begin(), l.end());
	EXPECT_EQ(sp.shortestSpan(), 0);  // duplicate -10
	EXPECT_EQ(sp.longestSpan(), 31);  // 21 - (-10)
}

static void test_copy_and_assign()
{
	title("copy ctor and assignment");

	Span a(5);
	a.addNumber(1);
	a.addNumber(10);
	a.addNumber(3);
	a.addNumber(7);
	a.addNumber(9);

	Span b(a);          // copy ctor
	Span c(1);
	c = a;              // operator=

	EXPECT_EQ(b.shortestSpan(), a.shortestSpan());
	EXPECT_EQ(b.longestSpan(), a.longestSpan());
	EXPECT_EQ(c.shortestSpan(), a.shortestSpan());
	EXPECT_EQ(c.longestSpan(), a.longestSpan());
}

static void test_large_sanity()
{
	title("large sanity (random fill)");
	const int N = 10000;
	Span sp(N);

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	for (int i = 0; i < N; ++i)
		sp.addNumber(std::rand());

	// sanity: shortestSpan >= 0 and longestSpan >= 0
	EXPECT_TRUE(sp.shortestSpan() >= 0);
	EXPECT_TRUE(sp.longestSpan() >= 0);
}

int main()
{
	try {
		test_subject_example();
		test_too_small_exceptions();
		test_addNumber_overflow();
		test_iterator_insert_vector_ok();
		test_iterator_insert_overflow();
		test_iterator_insert_list();
		test_copy_and_assign();
		test_large_sanity();
	} catch (const std::exception& e) {
		std::cout << CLR_RED << "\n[KO] Unhandled exception: " << CLR_RST << e.what() << "\n";
		return 1;
	}

	std::cout << "\n" << CLR_YEL << "Summary: " << CLR_RST
	          << g_pass << "/" << g_total << " tests passed\n";

	return (g_pass == g_total) ? 0 : 1;
}
