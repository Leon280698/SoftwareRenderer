#include "mesh.h"

void Mesh::Draw(RenderContext& target, const Matrix& viewProjection, const LightInfo* lightInfo) const{
	Matrix transform = Matrix().Translation(position) * Matrix().Rotation(rotation);
	Matrix mvp = viewProjection * transform;

	for(int i = 0; i < triangles.size(); i += 3)
		target.DrawTriangle(vertices[triangles[i]].Transform(mvp, transform),
							vertices[triangles[i + 1]].Transform(mvp, transform),
							vertices[triangles[i + 2]].Transform(mvp, transform),
							shaderType, lightInfo, texture);
}

bool Mesh::LoadMeshPLY(const std::string& fileName){
	std::ifstream read(fileName);

	if(!read.is_open())
		return false;

	std::string current;
	bool hasUVs = false, hasVertexColors = false;
	int numVertices, numFaces;

	do{
		read >> current;

		if(current == "vertex")
			read >> numVertices;
		else if(current == "s")
			hasUVs = true;
		else if(current == "red")
			hasVertexColors = true;
		else if(current == "face")
			read >> numFaces;
	}while(current != "end_header");

	vertices.resize(numVertices);

	for(int i = 0; i < numVertices; i++){
		Vec4 temp;

		read >> temp.X;
		read >> temp.Y;
		read >> temp.Z;
		vertices[i].setPosition(temp);

		read >> temp.X;
		read >> temp.Y;
		read >> temp.Z;
		temp.W = 0.0f;
		vertices[i].setNormal(Vec3(temp.X, temp.Y, temp.Z).Normalize());

		if(hasUVs){
			read >> temp.X;
			read >> temp.Y;
			vertices[i].setTextureCoordinates(Vec2(temp.X, 1 - temp.Y));
		}

		if(hasVertexColors){
			read >> temp.X;
			read >> temp.Y;
			read >> temp.Z;
			vertices[i].setColor(Color(temp.X / 255.0f, temp.Y / 255.0f, temp.Z / 255.0f));
		}
	}

	for(int i = 0; i < numFaces; i++){
		int v1, v2, v3, v4;

		read >> v1;

		if(v1 == 3){
			read >> v1;
			read >> v2;
			read >> v3;

			triangles.push_back(v1);
			triangles.push_back(v2);
			triangles.push_back(v3);
		}else{
			read >> v1;
			read >> v2;
			read >> v3;
			read >> v4;

			triangles.push_back(v1);
			triangles.push_back(v2);
			triangles.push_back(v3);

			triangles.push_back(v3);
			triangles.push_back(v4);
			triangles.push_back(v1);
		}
	}

	return true;
}

Vec4 Mesh::getPosition() const{
	return position;
}

void Mesh::setPosition(const Vec4& v){
	position = v;
}

Rotator Mesh::getRotation() const{
	return rotation;
}

void Mesh::setRotation(const Rotator& r){
	rotation = r;
}