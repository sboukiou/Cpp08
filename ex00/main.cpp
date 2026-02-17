#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include "easyfind.hpp"

#define CLR_RED   "\033[31m"
#define CLR_GRN   "\033[32m"
#define CLR_YEL   "\033[33m"
#define CLR_RST   "\033[0m"

static int g_total = 0;
static int g_pass  = 0;

static void printTitle(const std::string& t)
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
		bool _ok = ((a) == (b)); \
		std::ostringstream _oss; \
		_oss << #a << " == " << #b << " (got " << (a) << ", expected " << (b) << ")"; \
		report(_ok, _oss.str()); \
	} while (0)

#define EXPECT_THROW(stmt) \
	do { \
		bool _thrown = false; \
		try { stmt; } catch (const std::exception&) { _thrown = true; } \
		std::ostringstream _oss; \
		_oss << "throws: " << #stmt; \
		report(_thrown, _oss.str()); \
	} while (0)

template <typename C>
static void pushRange(C& c, int from, int toInclusive)
{
	for (int i = from; i <= toInclusive; ++i)
		c.push_back(i);
}

static void test_vector_found_and_not_found()
{
	printTitle("std::vector<int> | found / not found");
	std::vector<int> v;
	pushRange(v, 0, 9);

	EXPECT_EQ(easyfind(v, 0), 0);
	EXPECT_EQ(easyfind(v, 5), 5);
	EXPECT_EQ(easyfind(v, 9), 9);
	EXPECT_THROW(easyfind(v, 42));
}

static void test_list_negative_values()
{
	printTitle("std::list<int> | negative values");
	std::list<int> l;
	pushRange(l, -5, 5);

	EXPECT_EQ(easyfind(l, -5), -5);
	EXPECT_EQ(easyfind(l, 0), 0);
	EXPECT_EQ(easyfind(l, 5), 5);
	EXPECT_THROW(easyfind(l, 6));
}

static void test_deque_const_container()
{
	printTitle("const std::deque<int> | const_iterator");
	std::deque<int> d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);

	const std::deque<int> cd(d);
	EXPECT_EQ(easyfind(cd, 20), 20);
	EXPECT_THROW(easyfind(cd, -1));
}

static void test_duplicates()
{
	printTitle("duplicates | value exists multiple times");
	std::vector<int> v;
	v.push_back(1);
	v.push_back(7);
	v.push_back(7);
	v.push_back(2);

	EXPECT_EQ(easyfind(v, 7), 7);
}

static void test_empty()
{
	printTitle("empty container");
	std::vector<int> v;
	EXPECT_THROW(easyfind(v, 0));
}

int main()
{
	test_vector_found_and_not_found();
	test_list_negative_values();
	test_deque_const_container();
	test_duplicates();
	test_empty();

	std::cout << "\n"
	          << CLR_YEL << "Summary: " << CLR_RST
	          << g_pass << "/" << g_total << " tests passed\n";

	return (g_pass == g_total) ? 0 : 1;
}
