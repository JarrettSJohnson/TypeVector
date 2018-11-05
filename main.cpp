#include "vector.hpp"

int main() {
	using myVec = khzmp::vector<int, char, long>;
	static_assert(myVec::size == 3U);
	static_assert(std::is_same_v<myVec::head, int>);
	static_assert(std::is_same_v<myVec::tail, khzmp::vector<char, long>>);
	static_assert(std::is_same_v<myVec::tail::tail, khzmp::vector<long>>);
	static_assert(std::is_same_v<myVec::tail::tail::tail, khzmp::vector<>>);

	using myVec_push_back = khzmp::push_back_t<myVec, short>;
	static_assert(std::is_same_v<
		myVec_push_back,
		khzmp::push_back_t<khzmp::vector<int, char, long>, short>>);
	static_assert(myVec_push_back::size == 4U);
	static_assert(
		std::is_same_v<myVec_push_back, khzmp::vector<int, char, long, short>>);
	static_assert(khzmp::contains_v<myVec_push_back, short>);

	using myVec_pop_front = khzmp::pop_front_t<myVec>;
	static_assert(std::is_same_v<myVec_pop_front, khzmp::vector<char, long>>);

	using myVec_push_front = khzmp::push_front_t<myVec, short>;
	static_assert(myVec_push_front::size == 4U);
	static_assert(
		std::is_same_v<myVec_push_front, khzmp::vector<short, int, char, long>>);
	static_assert(khzmp::contains_v<myVec_push_front, short>);

	using myVec_filter_char = khzmp::filter_not_t<myVec, char>;
	static_assert(myVec_filter_char::size == 2U);
	static_assert(std::is_same_v<myVec_filter_char, khzmp::vector<int, long>>);
}
