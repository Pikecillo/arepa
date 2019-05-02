#pragma once

#include <assert.h>
#include <math.h>
#include <time.h>

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/glut.h>

// This specifies linker options in visual c++
#pragma comment(lib, "glew32.lib")

#define AREPA_ASSERT(x) assert(x);
