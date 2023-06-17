#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math/matrix.hpp"
#include <cmath>


// -- X N S  N A M E S P A C E ------------------------------------------------

namespace xns {


	// -- C A M E R A ---------------------------------------------------------

	class camera final {


		public:

			// -- S P E C S ---------------------------------------------------

			class specs final {


				// -- friend --------------------------------------------------

				/* camera as friend */
				friend class camera;


				public:

					// -- public constructors ---------------------------------

					/* copy constructor */
					specs(const specs&) noexcept;

					/* move constructor */
					specs(specs&&) noexcept;

					/* destructor */
					~specs(void) noexcept;


					// -- public assignment operators -------------------------

					/* copy assignment operator */
					specs& operator=(const specs&) noexcept;

					/* move assignment operator */
					specs& operator=(specs&&) noexcept;


					// -- public accessors ------------------------------------

					/* get fov */
					double fov(void) const noexcept;

					/* get aspect */
					double aspect(void) const noexcept;

					/* get near */
					double near(void) const noexcept;

					/* get far */
					double far(void) const noexcept;


				private:

					// -- private constructors --------------------------------

					/* default constructor */
					specs(void) noexcept;

					/* members constructor */
					specs(const double fov, const double aspect, const double near, const double far)
					: _fov{fov}, _aspect{aspect}, _near{near}, _far{far} {
						// nothing to do...
					}


					// -- private members -------------------------------------

					/* specs */
					double _fov, _aspect, _near, _far;

			};



			// -- public types ------------------------------------------------

			using view_matrix = matrix<double, 4, 4>;


			// -- public constructors -----------------------------------------

			/* default constructor */
			camera(void) noexcept;

			/* copy constructor */
			camera(const camera&) noexcept;

			/* move constructor */
			camera(camera&&) noexcept;

			/* destructor */
			~camera(void) noexcept;


			// -- public accessors --------------------------------------------

			/* get specs */
			const specs& get_specs(void) const noexcept;


		private:

			// -- private members ---------------------------------------------

			/* view matrix */
			view_matrix _matrix;

			/* specs */
			specs _specs;

	};




	// -- P R O J E C T I O N -------------------------------------------------

	class projection final {


		public:

			// -- public types ------------------------------------------------

			using projection_matrix = matrix<double, 4, 4>;


			// -- public update methods ---------------------------------------

			/* update projection matrix */
			void update(const xns::camera::specs& specs) {

				// compute yscale
				const double ys = 1         /  std::tan(((specs.fov() / 180.0) * 3.14159265358979323846) * 0.5);

				// compute xscale
				const double xs = ys        /  specs.aspect();

				// compute zscale
				const double zs = specs.far() / (specs.near() - specs.far());

				// compute ztranslate
				const double zt = zs        *  specs.near();


				// assign new matrix
				_matrix = projection_matrix{
					xs, 0.0, 0.0, 0.0,
				   0.0,  ys, 0.0, 0.0,
				   0.0, 0.0, -zs, 1.0,
				   0.0, 0.0,  zt, 0.0
				};

			}


			// -- public accessors --------------------------------------------

			/* get projection matrix */
			const projection_matrix& matrix(void) const {
				return _matrix;
			}


		private:

			// -- private members ---------------------------------------------

			projection_matrix _matrix;


	};

}

#endif
