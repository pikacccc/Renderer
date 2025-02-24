#pragma once

namespace camera_data_define {
	enum camera_movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;
	const float ZOOMMAX = 60.0f;
	const float ZOOMMIN = 20.0f;
}