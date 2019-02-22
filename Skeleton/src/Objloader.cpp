/*
Permet de charger un fichier .obj et le stocker dans une instance de Shape pour être manipulé après. 
*/

#include "Objloader.h"

//Découpe un string en fonction d'un délimiteur
std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

Objloader::Objloader(char* path) {
	std::vector<glm::vec3> vertices_tmp, vertices, normals_tmp, normals;
	std::vector<glm::vec2> uvs_tmp, uvs;
	std::vector<int> vertexIndicies, uvIndicies, normalIndicies;
	std::string header, line;
	float x, y, z;
	INFO("%s", path);
	std::ifstream objFile(path);
	if (!objFile) ERROR("Impossible d'ouvrir le fichier %s", path);
	
	while (std::getline(objFile, line)) {
		//v est un sommet, vt texture et vn normale et f face
		
		header = line.substr(0, 2);
		if (header == "v ") {
			std::stringstream ss(line);
			ss >> header >> x >> y >> z;
			vertices_tmp.push_back(glm::vec3(x, y, z));
		}
		else if (header == "vt") {
			std::stringstream ss(line);
			ss >> header >> x >> y;
			uvs_tmp.push_back(glm::vec2(x,y));
		}
		else if (header == "vn") {
			std::stringstream ss(line);
			ss >> header >> x >> y >> z;
			normals_tmp.push_back(glm::vec3(x, y, z));
		}
		else if (header == "f ") {
			std::stringstream ss(line);
			std::string f, s, t, token;
			ss >> header >> f >> s >> t;

			vertexIndicies.push_back(stoi(split(f, '/').at(0)));
			uvIndicies.push_back(stoi(split(f, '/').at(1)));
			normalIndicies.push_back(stoi(split(f, '/').at(2)));

			vertexIndicies.push_back(stoi(split(s, '/').at(0)));
			uvIndicies.push_back(stoi(split(s, '/').at(1)));
			normalIndicies.push_back(stoi(split(s, '/').at(2)));

			vertexIndicies.push_back(stoi(split(t, '/').at(0)));
			uvIndicies.push_back(stoi(split(t, '/').at(1)));
			normalIndicies.push_back(stoi(split(t, '/').at(2)));

		}
		
	}
	//Mise en ordre

	for (auto n : vertexIndicies)
		vertices.push_back(vertices_tmp[n - 1]);

	for (auto n : normalIndicies)
		normals.push_back(normals_tmp[n - 1]);

	for (auto n : uvIndicies)
		uvs.push_back(uvs_tmp[n - 1]);

	shape = Shape(vertices, normals, uvs);
}
