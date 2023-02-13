#ifndef MACRO_HEADER
#define MACRO_HEADER

#define LOOP(x,limit) for(UInt64 x = 0; x < UInt64(limit); ++x)

#define Loop(ite) for (uint x = 0; x < (ite); ++x)

#define iloop(start, end) for (uint i = (start); i < (end); ++i)
#define xloop(start, end) for (uint x = (start); x < (end); ++x)
#define yloop(start, end) for (uint y = (start); y < (end); ++y)
#define zloop(start, end) for (uint z = (start); z < (end); ++z)

#define irevloop(start, end) for (uint i = (start); i < (end); ++i)
#define xrevloop(start, end) for (uint x = (start); x < (end); ++x)
#define yrevloop(start, end) for (uint y = (start); y < (end); ++y)
#define zrevloop(start, end) for (uint z = (start); z < (end); ++z)

#define memfree(ptr) (ptr) ? delete	: (void)0
#define memfree2(ptr) (ptr) ? delete[] : (void)0

#define NON_INSTANCIABLE(Obj)				\
	Obj(void)					= delete;	\
	~Obj(void)					= delete;	\
	Obj(Obj&&)					= delete;	\
	Obj(const Obj&)				= delete;	\
	Obj& operator=(Obj&&)		= delete;	\
	Obj& operator=(const Obj&)	= delete;

#define NON_COPYABLE(Obj)					\
	Obj(const Obj&)				= delete;	\
	Obj& operator=(const Obj&)	= delete;

#define NON_MOVABLE(Obj)					\
	Obj(Obj&&)					= delete;	\
	Obj& operator=(Obj&&)		= delete;

#define NON_ASSIGNABLE(Obj)					\
	NON_COPYABLE(Obj)						\
	NON_MOVABLE(Obj)

#define NO_OPERATOR(OBJ, OP) \
	OBJ& operator OP (const OBJ&) = delete; \
	OBJ& operator OP (OBJ&&) = delete



#define IDX(type) static_cast<int>((type))

#define CAST(type, var) static_cast<type>((var))

#define HINT(mess) std::cerr << YELLOW << (mess) << RESET << std::endl

#define YELLOW "\x1b[33m"

#define RESET "\x1b[0m"

#define newline std::cout.write("\n", 1);


#endif
