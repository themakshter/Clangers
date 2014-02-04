#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

bool loadOBJ(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
);

GLuint loadBMP_custom(const char * imagepath);


#endif // UTIL_H_INCLUDED
