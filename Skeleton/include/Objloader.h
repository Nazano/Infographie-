#ifndef OBJLOADER_INC
#define OBJLOADER_INC


//GML libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream> 
#include <algorithm>

#include "Shape.h"
#include "logger.h"

class Objloader
{
public:
	Objloader(char*);
	Shape getShape() { return shape; }
	
private:
	Shape shape;
};


#endif // !OBJLOADER_INC
