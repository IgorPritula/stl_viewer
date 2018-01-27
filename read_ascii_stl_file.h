#ifndef READ_ASCII_STL_FILE_H
#define READ_ASCII_STL_FILE_H

// include files

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

#include "vec_struct.h"

extern int read_ascii_STL_file (std::string STL_filename,std::vector<triangle> & facet,
                                 double & x_min, double & x_max, double & y_min, double & y_max, double & z_min, double & z_max);

#endif // READ_ASCII_STL_FILE_H
