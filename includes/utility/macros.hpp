#ifndef XNS_MACROS_HEADER
#define XNS_MACROS_HEADER

namespace xns {


	#define NON_COPYABLE(obj)					\
		obj(const obj&)				= delete;	\
		obj& operator=(const obj&)	= delete

	#define NON_MOVABLE(obj)					\
		obj(obj&&)					= delete;	\
		obj& operator=(obj&&)		= delete

	#define NON_INSTANCIABLE(obj)				\
		obj(void)					= delete;	\
		~obj(void)					= delete;	\
		NON_COPYABLE(obj);						\
		NON_MOVABLE(obj)

	#define NON_ASSIGNABLE(obj) \
		NON_COPYABLE(obj); \
		NON_MOVABLE(obj)


	#define non_instanciable(obj) NON_INSTANCIABLE(obj)
	#define non_copyable(obj) NON_COPYABLE(obj)
	#define non_movable(obj) NON_MOVABLE(obj)
	#define non_assignable(obj) NON_ASSIGNABLE(obj)

}

#endif
