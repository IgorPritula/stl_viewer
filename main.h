#ifndef MAIN_H
#define MAIN_H

// include files

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <list>
#include <sstream>
#include <iomanip>
#include <locale>
#include <cstdlib>

#include "vec_struct.h"

#include "read_ascii_stl_file.h"

void createVertexArray(std::vector<triangle> & facet, float* vertices);

std::vector<triangle> facet;        // define a vector object (container) called "facet" of type "triangle"
double x_min, x_max, delta_x;       // geometry extents along X
double y_min, y_max, delta_y;       // geometry extents along Y
double z_min, z_max, delta_z;       // geometry extents along Z

#endif // MAIN_H
