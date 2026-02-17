#include <iostream>
#include <sstream>
#include <stack>
#include <list>
#include <vector>
#include "MutantStack.hpp"

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

static long sum_stack(MutantStack<int>& m)
{
	long s = 0;
	for (MutantStack<int>::iterator it = m.begin(); it != m.end(); ++it)
		s += *it;
	return s;
}

static long sum_stack_const(const MutantStack<int>& m)
{
	long s = 0;
	for (MutantStack<int>::const_iterator it = m.begin(); it != m.end(); ++it)
		s += *it;
	return s;
}

static void test_basic_stack_ops()
{
	title("basic stack operations");
	MutantStack<int> m;

	EXPECT_TRUE(m.empty());
	EXPECT_EQ(m.size(), 0);

	m.push(10);
	m.push(20);
	m.push(30);

	EXPECT_TRUE(!m.empty());
	EXPECT_EQ(m.size(), 3);
	EXPECT_EQ(m.top(), 30);

	m.pop();
	EXPECT_EQ(m.size(), 2);
	EXPECT_EQ(m.top(), 20);
}

static void test_iteration_order()
{
	title("iteration order (bottom -> top)");
	MutantStack<int> m;
	m.push(5);
	m.push(17);
	m.push(3);

	// stack top should be 3
	EXPECT_EQ(m.top(), 3);

	MutantStack<int>::iterator it = m.begin();
	EXPECT_TRUE(it != m.end());
	EXPECT_EQ(*it, 5); // bottom

	++it;
	EXPECT_TRUE(it != m.end());
	EXPECT_EQ(*it, 17);

	++it;
	EXPECT_TRUE(it != m.end());
	EXPECT_EQ(*it, 3); // top

	++it;
	EXPECT_TRUE(it == m.end());
}

static void test_const_iteration()
{
	title("const iteration (const_iterator begin/end)");
	MutantStack<int> m;
	m.push(1);
	m.push(2);
	m.push(3);

	const MutantStack<int> cm(m);

	EXPECT_EQ(sum_stack(m), 6);
	EXPECT_EQ(sum_stack_const(cm), 6);

	// ensure begin/end compile and work on const object
	MutantStack<int>::const_iterator it = cm.begin();
	EXPECT_TRUE(it != cm.end());
	EXPECT_EQ(*it, 1);
}

static void test_copy_and_assign()
{
	title("copy ctor and assignment");

	MutantStack<int> a;
	a.push(7);
	a.push(8);
	a.push(9);

	MutantStack<int> b(a); // copy ctor
	EXPECT_EQ(sum_stack(b), 24);
	EXPECT_EQ(b.top(), 9);
	EXPECT_EQ(b.size(), 3);

	MutantStack<int> c;
	c.push(42);
	c = a; // assignment
	EXPECT_EQ(sum_stack(c), 24);
	EXPECT_EQ(c.top(), 9);
	EXPECT_EQ(c.size(), 3);

	// check independence (modify a, b/c should not change)
	a.pop();
	EXPECT_EQ(a.size(), 2);
	EXPECT_EQ(b.size(), 3);
	EXPECT_EQ(c.size(), 3);
}

static void test_compare_with_list_like_subject()
{
	title("compare with std::list (subject-like demo)");

	MutantStack<int> m;
	m.push(5);
	m.push(17);
	EXPECT_EQ(m.top(), 17);
	m.pop();
	EXPECT_EQ(m.size(), 1);
	m.push(3);
	m.push(5);
	m.push(737);
	m.push(0);

	// iterate and compute sum
	long ms = sum_stack(m);

	// equivalent list behavior (iterate same values)
	std::list<int> l;
	l.push_back(5);
	l.push_back(3);
	l.push_back(5);
	l.push_back(737);
	l.push_back(0);

	long ls = 0;
	for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it)
		ls += *it;

	EXPECT_EQ(ms, ls);
}

static void test_iterator_valid_after_push_pop()
{
	title("iterator validity sanity after push/pop");

	MutantStack<int> m;
	m.push(1);
	m.push(2);
	m.push(3);

	// Take begin, then push/pop; for deque this is generally safe-ish,
	// but we don't rely on strict guarantees; we just test we can iterate fresh.
	m.push(4);
	m.pop(); // back to 3 on top

	long s = sum_stack(m);
	EXPECT_EQ(s, 6); // 1+2+3
}

int main()
{
	try {
		test_basic_stack_ops();
		test_iteration_order();
		test_const_iteration();
		test_copy_and_assign();
		test_compare_with_list_like_subject();
		test_iterator_valid_after_push_pop();
	} catch (const std::exception& e) {
		std::cout << CLR_RED << "\n[KO] Unhandled exception: " << CLR_RST << e.what() << "\n";
		return 1;
	}

	std::cout << "\n" << CLR_YEL << "Summary: " << CLR_RST
	          << g_pass << "/" << g_total << " tests passed\n";

	return (g_pass == g_total) ? 0 : 1;
}
