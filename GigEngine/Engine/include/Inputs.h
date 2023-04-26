#pragma once
#include<string>
#include<vector>

namespace GigInput
{
	enum class MouseButton
	{
		LEFT = 0,
		RIGHT = 1,
		MIDDLE = 2
	};

	enum class MouseState
	{
		RELEASE = 0,
		PRESS = 1
	};

	enum class Keys
	{
		ESCAPE = 256,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		SPACE = 32,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		LEFT = 263,
		RIGHT = 262,
		DOWN = 264,
		UP = 265,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		LAST = 348,
		TAB = 258,
	};

	struct Mouse
	{
		double x;
		double y;

		double lastX;
		double lastY;

		double mouseOffsetX;
		double mouseOffsetY;

		double wheelOffsetY;

		bool rightClick;
		bool leftClick;

		bool wheelClick;
	};

	class Inputs
	{
	public:
		Inputs() = delete;

		static bool GetKey(Keys pKey);

		static Mouse GetMouse();

		static void UpdateKey(int key, int action);

		static void UpdateMousePosition();

		static void UpdateMouseButton(int button, int action);
		static void UpdateMouseWheelOffset(double offset);

	private:
		inline static Mouse mouse;
		inline static std::vector<bool> inputs = std::vector<bool>((int)Keys::LAST + 1, false);
	};
}
