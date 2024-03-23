#include "xns/3d/camera.hpp"


// -- C A M E R A -------------------------------------------------------------


// -- public constructors -----------------------------------------------------

/* default constructor */
xns::camera::camera(void) noexcept
: _matrix{}, _specs{} {
	// nothing to do...
}

/* copy constructor */
xns::camera::camera(const camera& other) noexcept
: _matrix{other._matrix}, _specs{other._specs} {
	// nothing to do...
}

/* move constructor */
xns::camera::camera(camera&& other) noexcept
: _matrix{xns::move(other._matrix)}, _specs{xns::move(other._specs)} {
	// nothing to do...
}

/* destructor */
xns::camera::~camera(void) noexcept {
	// nothing to do...
}


// -- public accessors --------------------------------------------------------

/* get specs */
const xns::camera::specs& xns::camera::get_specs(void) const noexcept {
	// return const reference to camera specs
	return _specs;
}





// -- S P E C S ---------------------------------------------------------------


// -- public constructors -----------------------------------------------------

/* default constructor */
xns::camera::specs::specs(void) noexcept
: _fov{0.0}, _aspect{0.0}, _near{0.0}, _far{0.0} {
	// nothing to do...
}

/* copy constructor */
xns::camera::specs::specs(const specs& other) noexcept
: _fov{other._fov}, _aspect{other._aspect}, _near{other._near}, _far{other._far} {
	// nothing to do...
}

/* move constructor */
xns::camera::specs::specs(specs&& other) noexcept
: _fov{xns::move(other._fov)}, _aspect{xns::move(other._aspect)}, _near{xns::move(other._near)}, _far{xns::move(other._far)} {
	// nothing to do...
}

/* destructor */
xns::camera::specs::~specs(void) noexcept {
	// nothing to do...
}


// -- public assignment operators ---------------------------------------------

/* copy assignment operator */
xns::camera::specs& xns::camera::specs::operator=(const specs& other) noexcept {
	// assign members
	_fov    = other._fov;
	_aspect = other._aspect;
	_near   = other._near;
	_far    = other._far;
	// return self reference
	return *this;
}

/* move assignment operator */
xns::camera::specs& xns::camera::specs::operator=(specs&& other) noexcept {
	// move members
	_fov    = xns::move(other._fov);
	_aspect = xns::move(other._aspect);
	_near   = xns::move(other._near);
	_far    = xns::move(other._far);
	// return self reference
	return *this;
}


// -- public accessors --------------------------------------------------------

/* get fov */
double xns::camera::specs::fov(void) const noexcept {
	// return fov
	return _fov;
}

/* get aspect */
double xns::camera::specs::aspect(void) const noexcept {
	// return aspect
	return _aspect;
}

/* get near */
double xns::camera::specs::near(void) const noexcept {
	// return near
	return _near;
}

/* get far */
double xns::camera::specs::far(void) const noexcept {
	// return far
	return _far;
}

