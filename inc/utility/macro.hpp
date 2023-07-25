#ifndef MACRO_HEADER
#define MACRO_HEADER

namespace xns {

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
	Obj& operator=(const Obj&)	= delete

#define NON_COPYABLE(Obj)					\
	Obj(const Obj&)				= delete;	\
	Obj& operator=(const Obj&)	= delete

#define NON_MOVABLE(Obj)					\
	Obj(Obj&&)					= delete;	\
	Obj& operator=(Obj&&)		= delete

#define NON_ASSIGNABLE(Obj) NON_COPYABLE(Obj); NON_MOVABLE(Obj)

#define NO_OPERATOR(OBJ, OP) \
	OBJ& operator OP (const OBJ&) = delete; \
	OBJ& operator OP (OBJ&&) = delete


#ifndef _MIN
#define _MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef _MAX
#define _MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#define IDX(type) static_cast<int>((type))

#define CAST(type, var) static_cast<type>((var))

#define HINT(mess) std::cerr << YELLOW << (mess) << RESET << std::endl

#define YELLOW "\x1b[33m"

#define RESET "\x1b[0m"

//#define newline std::cout.write("\n", 1);

#define _DBG(msg) std::cout << YELLOW << msg << RESET << " : " << __PRETTY_FUNCTION__ << std::endl;


// -- C L A S S  D E B U G  M A C R O -----------------------------------------

/* constructor */
#define _CTOR(obj) \
	Xf::Debug::print("ctor: %s\n", #obj)

/* destructor */
#define _DTOR(obj) \
	Xf::Debug::print("dtor: %s\n", #obj)

/* copy constructor */
#define _COPY(obj) \
	Xf::Debug::print("copy: %s\n", #obj)

/* move constructor */
#define _MOVE(obj) \
	Xf::Debug::print("move: %s\n", #obj)

/* copy assignment */
#define _COPY_ASSIGN(obj) \
	Xf::Debug::print("copy assign: %s\n", #obj)

/* move assignment */
#define _MOVE_ASSIGN(obj) \
	Xf::Debug::print("move assign: %s\n", #obj)



}

#endif
