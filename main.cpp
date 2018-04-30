//----------------------------------------------------------------------
// FluidSolver Project
// by Bhavathi Reddy
//----------------------------------------------------------------------

#include <string>
#include <chrono>
#include <iostream>
#include "FluidSolver3d.h"
#include "FluidRenderer3d.h"
#include "SimUtil.h"

//----------------------------------------------------------------------
// Simulation Attributes
//----------------------------------------------------------------------
using namespace std;
// grid cell width (in meters)
const float GRID_CELL_WIDTH = 0.005f;
// simulation time step (in seconds)
const float TIME_STEP = 0.01f;

//----------------------------------------------------------------------
// Input
//----------------------------------------------------------------------

// file format for initial geometry
const std::string INITIAL_GEOMETRY_FILE_IN = "geo_small.txt";

//----------------------------------------------------------------------
// Main Function
//----------------------------------------------------------------------

int main(int argc, char** argv) {
	cout<<"T0"<<endl;
	FluidSolver3D solver(INITIAL_GEOMETRY_FILE_IN, GRID_CELL_WIDTH, TIME_STEP);
	cout<<"T00"<<endl;
	solver.init(INITIAL_GEOMETRY_FILE_IN);
	cout<<"T1"<<endl;
	int w, h, d, b;
	solver.getDim(w, h, d, b);
	cout<<"T2"<<endl;
	FluidRenderer3D render( solver.getGeometry(), w, h, d, b );
	cout<<"T3"<<endl;
	solver.step();
	cout<<"T4"<<endl;
	SimUtil::Mesh3D data = solver.meshData();
	cout<<"T5"<<endl;
	auto start = std::chrono::system_clock::now();
	cout<<"T6"<<endl;
	bool newFrame = true;
	int i=1;
	while (!render.isClosed()) {
		auto pdata=solver.particleData();
		render.draw(pdata, data.vertices, data.normals, data.indices);

		if (!render.isPaused() && newFrame) {
			start = std::chrono::system_clock::now();
			if (render.gManipulationActive()) {
				solver.updateOrientation(render.currentOrientation());
			}
			solver.step();
			data = solver.meshData();
			newFrame = false;
		}
		if (render.isPaused() && render.forwardPressed()) {
			if (render.gManipulationActive()) {
				solver.updateOrientation(render.currentOrientation());
			}
			solver.step();
			data = solver.meshData();
		}
		//Check if it's time for a new frame
		if (!render.isPaused() && !newFrame) {
			auto now = std::chrono::system_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
			if (elapsed.count() > 1000 * TIME_STEP) {
				newFrame = true;
			}
		}
	}

	return 0;
}