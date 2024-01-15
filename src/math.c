
#include "math.h"
void create_transformation_matrix(mat4 matrix, vec2 translation, vec2 scale) {
	glm_mat4_identity(matrix);
	vec3 d3 = { translation[0], translation[1], 0 };
	glm_translate(matrix, d3);
	vec3 s3 = { scale[0], scale[1], 1 };
	glm_scale(matrix, s3);

}