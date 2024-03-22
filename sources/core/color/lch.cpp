#include "color/color.hpp"

#include <cmath>

auto xns::lch_to_rgb(const double lightness,
					 const double chroma,
					 const double hue) -> xns::rgb {

	#define LUM(l) (l) < 0 ? 0 : (l) > 100 ? 100 : (l)
	#define HUE(h) (h) < 0 ? 0 : (h) > 360 ? 360 : (h)
	#define CHR(c) (c) < 0 ? 0 : (c) > 100 ? 100 : (c)

								// PI / 180
	const double radian = hue * (0.017453292519943295);

	// convert lab to d50-adapted xyz
	constexpr double k = 24389.0 / 27.0;
	constexpr double e = 216.0 / 24389.0;


	// compute xyz, starting with the luminance-related term
	double y = (lightness + 16) / 116;
	double x =  y + (chroma * std::cos(radian) / 500);
	double z =  y - (chroma * std::sin(radian) / 200);

	// compute x
	x = (std::pow(x, 3) > e ? std::pow(x, 3) : ((116 * x) - 16) / k) * 0.9642956764295677;
	// compute y
	y = (lightness > (k * e) ? std::pow((lightness + 16) / 116, 3) : lightness / k) * 1.00000;
	// compute z
	z = (std::pow(z, 3) > e  ? std::pow(z, 3) : ((116 * z) - 16) / k) * 0.8251046025104602;

	constexpr double d65[3][3] = {
		{  0.9554734527042182,   -0.023098536874261423,  0.0632593086610217   },
		{ -0.028369706963208136,  1.0099954580058226,    0.021041398966943008 },
		{  0.012314001688319899, -0.020507696433477912,  1.3303659366080753   }
	};

	// convert d50-adapted xyz to d65-adapted xyz
	const double d65x = d65[0][0] * x + d65[0][1] * y + d65[0][2] * z;
	const double d65y = d65[1][0] * x + d65[1][1] * y + d65[1][2] * z;
	const double d65z = d65[2][0] * x + d65[2][1] * y + d65[2][2] * z;

	constexpr double mat[3][3] = {
		{  +12831.0 /   +3959.0,     -329.0 /    +214.0,  -1974.0 /   +3959.0 },
		{ -851781.0 / +878810.0, +1648619.0 / +878810.0, +36519.0 / +878810.0 },
		{    +705.0 /  +12673.0,    -2585.0 /  +12673.0,   +705.0 /    +667.0 },
	};

	// convert an array of linear-light srgb values in the range 0.0-1.0
	double r = (mat[0][0] * d65x) + (mat[0][1] * d65y) + (mat[0][2] * d65z);
	double g = (mat[1][0] * d65x) + (mat[1][1] * d65y) + (mat[1][2] * d65z);
	double b = (mat[2][0] * d65x) + (mat[2][1] * d65y) + (mat[2][2] * d65z);

	double abs = 0;

	abs = std::abs(r);
	r = (abs > 0.0031308) ? (r < 0 ? -1 : +1)
		* (1.055 * std::pow(abs, 0.4166666666666667) - 0.055)
		: 12.92 * r;

	abs = std::abs(g);
	g = (abs > 0.0031308) ? (g < 0 ? -1 : +1)
		* (1.055 * std::pow(abs, 0.4166666666666667) - 0.055)
		: 12.92 * g;

	abs = std::abs(b);
	b = (abs > 0.0031308) ? (b < 0 ? -1 : +1)
		* (1.055 * std::pow(abs, 0.4166666666666667) - 0.055)
		: 12.92 * b;

	#define clamp(c) static_cast<unsigned char>(((c) < 0) ? 0 : ((c) > 255) ? 255 : (c))
	return xns::rgb{clamp(r * 255), clamp(g * 255), clamp(b * 255)};
	#undef clamp
}


