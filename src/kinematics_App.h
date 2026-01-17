#pragma once
#include "kinematics/include/kinematics.h"
#include <memory>

class App
{
  public:
	App(const float width, const float height, const size_t initialNumBodies);

	void Update();

        /// Draw simulation (does NOT call BeginDrawing/EndDrawing)
        void Draw() const;

        /// Top level draw function for the entire scene.
        /// Includes: Background, FPS counter, statistics and `Simulation` contents.
        /// Calls BeginDrawing/EndDrawing internally.
        void DrawFrame() const;

  private:
	bool _renderBodies = true, _renderStats = false;
	bool _updateBodies = true;
	std::unique_ptr<kinematics::Simulation> _simulation;

	float _frameTimeSeconds;
	long _updateMicroseconds;

  private:
	/// Update the simulation according to user input.
	/// Includes: Toggle for rendering bodies, toggle for updating bodies, setting number of bodies
	void HandleInput();
};
