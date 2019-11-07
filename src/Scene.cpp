#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderEyelightTextured.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include "PrimTriangleSmooth.h"
#include "PrimTriangleSmoothTextured.h"

#include <fstream> 


void CScene::ParseOBJ(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.is_open()) {
		std::cout << "Parsing OBJFile : " << fileName << std::endl;

		//std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 0.5f, 0));
		// For 4.4
		//std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(1, 0.5f, 0), "../../../../data/barney.bmp");
		// For 4.5
		std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelightTextured>(RGB(1, 1, 1), "../../../../data/cb.bmp");
		std::vector<Vec3f> vVertices;
		std::vector<Vec3f> vNormals; 
		std::vector<Vec2f> vTextures;
		
		std::string line;
		for (;;) {
			if (!getline(file, line)) break;
			std::stringstream ss(line);
			getline(ss, line, ' ');
			if (line == "v") {
				Vec3f v;
				for (int i = 0; i < 3; i++) ss >> v.val[i];
				// std::cout << "Vertex: " << v << std::endl;
				vVertices.emplace_back(v);
			}
			else if (line == "f") {
				std::string aV, aN, aT, bV, bN, bT, cV, cN, cT;
				getline(ss, aV, '/');
				getline(ss, aT, '/');
				getline(ss, aN, ' ');

				getline(ss, bV, '/');
				getline(ss, bT, '/');
				getline(ss, bN, ' ');

				getline(ss, cV, '/');
				getline(ss, cT, '/');
				getline(ss, cN, ' ');

				// std::cout << "Face: " << f << std::endl;
				// For 4.1
				/*Add(std::make_shared<CPrimTriangleSmooth>(vVertices[stoi(aV) - 1], vVertices[stoi(bV) - 1], vVertices[stoi(cV) - 1], 
					vNormals[stoi(aN) - 1], vNormals[stoi(bN) - 1], vNormals[stoi(cN)-1],pShader));*/

				// For 4.3
				Add(std::make_shared<CPrimTriangleSmoothTextured>(vVertices[stoi(aV) - 1], vVertices[stoi(bV) - 1], vVertices[stoi(cV) - 1],
					vNormals[stoi(aN) - 1], vNormals[stoi(bN) - 1], vNormals[stoi(cN) - 1],
					vTextures[stoi(aT)-1], vTextures[stoi(bT)-1], vTextures[stoi(cT)-1], pShader));
			}
			else if (line == "vn") {
				Vec3f vertexNormal;
				for (int i = 0; i < 3; i++) ss >> vertexNormal.val[i];
				vNormals.emplace_back(vertexNormal);
			}
			else if (line == "vt") {
				Vec2f vt;
				for (int i = 0; i < 2; i++) ss >> vt.val[i];
				vTextures.emplace_back(vt);
			}
			else if (line == "#") {
				std::string comment;
				getline(ss, comment);
			}
			else {
				std::cout << "Unknown key [" << line << "] met in the OBJ file" << std::endl;
			}
		}

		file.close();
		std::cout << "Finished Parsing" << std::endl;
	} else
		std::cout << "ERROR: Can't open OBJFile" << std::endl;
}
