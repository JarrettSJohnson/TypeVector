#pragma once

#include <tuple>
#include <type_traits>

namespace khzmp {

	//////////////////////////////////////
	//								    //
	//			   VECTOR 				//
	//									//
	//////////////////////////////////////
	struct empty_vector {};

	template <class... T>
	struct vector;

	template <>
	struct vector<> {
		using head = empty_vector;
		using tail = empty_vector;
		using tuple_t = std::tuple<>;
		static constexpr std::size_t size = 0;
	};

	template <class H, class... T>
	struct vector<H, T...> : vector<T...> {
		using head = H;
		using tail = vector<T...>;
		using tuple_t = std::tuple<H, T...>;
		static constexpr std::size_t size = 1 + sizeof...(T);
	};

	//////////////////////////////////////
	//								    //
	//			   PUSH_BACK			//
	//									//
	//////////////////////////////////////

	template <class Container, class T>
	struct push_back;

	template <template <class...> class Container, class T, class... Ts>
	struct push_back<Container<Ts...>, T> {
		using type = Container<Ts..., T>;
	};

	template <class Container, class T>
	using push_back_t = typename push_back<Container, T>::type;

	//////////////////////////////////////
	//								    //
	//			   PUSH_FRONT			//
	//									//
	//////////////////////////////////////

	template <class Container, class T>
	struct push_front;

	template <template <class...> class Container, class... ContainerTs, class NewT>
	struct push_front<Container<ContainerTs...>, NewT> {
		using type = Container<NewT, ContainerTs...>;
	};

	template <class Container, class T>
	using push_front_t = typename push_front<Container, T>::type;

	//////////////////////////////////////
	//								    //
	//			   POP_BACK				//
	//			Under Construction   	//
	//									//
	//////////////////////////////////////

	// template<class Container, class T>
	// struct pop_back;
	//
	// template <template <class...> class Container, class... ContainerTs>
	// struct pop_back<Container<ContainerTs...>> {
	//  using type = Container<std::index_sequence<sizeof...(ContainerTs) - 1>>;
	//};

	//////////////////////////////////////
	//								    //
	//			   POP_FRONT			//
	//									//
	//////////////////////////////////////

	template <class Container, class... Ts>
	struct pop_front;

	template <template <class...> class Container, class ContainerH,
		class... ContainerTs>
		struct pop_front<Container<ContainerH, ContainerTs...>> {
		using type = Container<ContainerTs...>;
	};

	template <class Container, class... Ts>
	using pop_front_t = typename pop_front<Container, Ts...>::type;

	//////////////////////////////////////
	//								    //
	//			   FILTER_NOT			//
	//									//
	//////////////////////////////////////

	template <class Container, class... Ts>
	struct _filter_not_impl;

	template <template <class...> class Container, class TargetT,
		class... SelectedTs>
		struct _filter_not_impl<Container<>, TargetT, Container<SelectedTs...>> {
		using type = Container<SelectedTs...>;
	};

	template <template <class...> class Container, class TargetT, class ContainerH,
		class... ContainerTs, class... SelectedTs>
		struct _filter_not_impl<Container<ContainerH, ContainerTs...>, TargetT,
		Container<SelectedTs...>>
		: _filter_not_impl<
		Container<ContainerTs...>, TargetT,
		std::conditional_t<std::is_same_v<ContainerH, TargetT>,
		Container<SelectedTs...>,
		Container<SelectedTs..., ContainerH>>> {};

	template <class Container, class TargetT>
	struct filter_not;

	template <template <class...> class Container, class... Ts, class TargetT>
	struct filter_not<Container<Ts...>, TargetT> {
		using type =
			typename _filter_not_impl<Container<Ts...>, TargetT, Container<>>::type;
	};

	template <class Container, class TargetT>
	using filter_not_t = typename filter_not<Container, TargetT>::type;

	//////////////////////////////////////
	//								    //
	//			FILTER_IF_NOT   		//
	//		  Under Construction     	//
	//									//
	//////////////////////////////////////

	// template <bool Pred, class...> struct filterIfNotImpl;
	//
	// template <bool Pred, template <class...> class Container, class... SelectedT>
	// struct filterIfNotImpl<Pred, Container<>, Container<SelectedTs...>> {
	//	using type = Container<SelectedTs...>;
	//};
	//
	// template <bool Pred, template <class...> class Container, class ContainerH,
	// class... ContainerTs, class... SelectedTs> struct filterIfNotImpl<Pred,
	// Container<ContainerH, ContainerTs...>, Container<SelectedTs...>, Pred> :
	//	filterIfNotImpl <
	//	Container<ContainerTs...>,
	//	std::conditional_t<
	//	Pred<T>,
	//	Container<SelectedTs...>,
	//	Container<SelectedTs..., ContainerH>
	//	>,
	//	TargetT
	//	> {};
	//
	// template<class...> struct filterIfNot;
	//
	// template <template <class...> class Container, class...Ts, class TargetT>
	// struct filterIfNot<Container<Ts...>, TargetT> {
	//	using type = typename filterIfNot<Container<Ts...>, Container<>,
	// TargetT>::type;
	//};

	//////////////////////////////////////
	//								    //
	//			   CONTAINS				//
	//									//
	//////////////////////////////////////

	template <class...>
	struct contains;

	template <template <class...> class Container, class H, class... ContainerTs,
		class TargetType>
		struct contains<Container<H, ContainerTs...>, TargetType>
		: std::conditional_t<std::is_same_v<H, TargetType>, std::true_type,
		contains<Container<ContainerTs...>, TargetType>> {};

	template <class... T>
	inline constexpr bool contains_v = contains<T...>::value;

}  // namespace khzmp