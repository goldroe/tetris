#ifndef SML_H
#define SML_H

typedef union {
	struct {
		float x, y;
	};

	struct {
		float width, height;
	};
	
	struct {
		float u, v;
	};

	float elements[2];
} sml_vec2;

typedef union {
	struct {
		float x, y, z;
	};

	struct {
		float u, v, w;
	};

	struct {
		r, g, b;
	};
	
	struct {
		sml_vec2 xy;
		float __unused0;
	};
		struct {
		sml_vec2 yz;
		float __unused1;
	};
	struct {
		sml_vec2 uv;
		float __unused2;
	};
	struct {
		sml_vec2 vw;
		float __unused3;
	};

	float elements[3];
} sml_vec3;

typedef union {
	struct {
		float x, y, z, w;
	};
	struct {
		float r, g, b, a;
	};

	struct {
		sml_vec2 xy;
		float __unused0;
		float __unused1;
	};
	struct {
		sml_vec2 yz;
		float __unused0;
		float __unused1;
	};
	struct {
		sml_vec2 zw;
		float __unused0;
		float __unused1;
	};

	struct {
	    sml_vec3 xyz;
		float __unused0;
	};
	struct {
		sml_vec3 yzw;
		float __unused0;
	};
	
	float elements[4];
} sml_vec4;

typedef union {
	float elements[2][2];
} sml_mat2;

typedef union {
	float elements[3][3];
} sml_mat3;

typedef union {
	float elements[4][4];
} sml_mat4;


static inline sml_vec2 make_vec2(float x, float y) {
	sml_vec2 result;
	result.elements[0] = x;
	result.elements[1] = y;
	return result;
}
static inline sml_vec3 make_vec3(float x, float y, float z) {
	sml_vec3 result;
	result.elements[0] = x;
	result.elements[1] = y;
	result.elements[2] = z;
	return result;
}
static inline sml_vec4 make_vec4(float x, float y, float z, float w) {
	sml_vec4 result;
	result.elements[0] = x;
	result.elements[1] = y;
	result.elements[2] = z;
	result.elements[3] = w;
	return result;
}

static inline sml_mat2 mat2_diagonal(float f) {
	sml_mat2 result = {0};
	result.elements[0][0] = f;
	result.elements[1][1] = f;
	return result;
}
static inline sml_mat3 mat3_diagonal(float f) {
	sml_mat3 result = {0};
	result.elements[0][0] = f;
	result.elements[1][1] = f;
	result.elements[2][2] = f;
	return result;
}
static inline sml_mat4 mat4_diagonal(float f) {
	sml_mat4 result = {0};
	result.elements[0][0] = f;
	result.elements[1][1] = f;
	result.elements[2][2] = f;
	result.elements[3][3] = f;
	return result;
}

static inline sml_mat2 multiply_mat2(sml_mat2 m0, sml_mat2 m1) {
	sml_mat2 result;
	result.elements[0][0] = m0[0][0] * m1[0][0] + m0[0][1] * m1[1][0];
	result.elements[0][1] = m0[0][0] * m1[1][1] + m0[0][1] * m1[1][1];
	result.elements[1][0] = m0[1][0] * m1[0][0] + m0[1][1] * m1[1][0];
	result.elements[1][1] = m0[1][0] * m1[0][1] + m0[1][1] * m1[1][1];
	return result;
}

static inline sml_mat3 multiply_mat3(sml_mat3 m0, sml_mat3 m1) {
	sml_mat3 result;
	result[0][0] = m0[0][0] * m1[0][0] + m0[0][1] * m1[1][0] + m0[0][2] * m1[2][0];
	result[0][1] = m0[0][0] * m1[0][1] + m0[0][1] * m1[1][1] + m0[0][2] * m1[2][1];
	result[0][2] = m0[0][0] * m1[0][2] + m0[0][1] * m1[1][2] + m0[0][2] * m1[2][2];
	result[1][0] = m0[1][0] * m1[0][0] + m0[1][1] * m1[1][0] + m0[1][2] * m1[2][0];
	result[1][1] = m0[1][0] * m1[0][1] + m0[1][1] * m1[1][1] + m0[1][2] * m1[2][1];
	result[1][2] = m0[1][0] * m1[0][2] + m0[1][1] * m1[1][2] + m0[1][2] * m1[2][2];
	result[2][0] = m0[2][0] * m1[0][0] + m0[2][1] * m1[1][0] + m0[2][2] * m1[2][0];
	result[2][1] = m0[2][0] * m1[0][1] + m0[2][1] * m1[1][1] + m0[2][2] * m1[2][1];
	result[2][2] = m0[2][0] * m1[0][2] + m0[2][1] * m1[1][2] + m0[2][2] * m1[2][2];
	return result;
}

static inline sml_mat4 multiply_mat4(sml_mat4 m0, sml_mat4 m1) {
	sml_mat4 result;
	result.elements[0][0] = m0[0][0] * m1[0][0] + m0[0][1] * m1[1][0] + m0[0][2] * m1[2][0] + m0[0][3] * m1[3][0];
	result.elements[0][1] = m0[0][0] * m1[0][1] + m0[0][1] * m1[1][1] + m0[0][2] * m1[2][1] + m0[0][3] * m1[3][1];
	result.elements[0][2] = m0[0][0] * m1[0][2] + m0[0][1] * m1[1][2] + m0[0][2] * m1[2][2] + m0[0][3] * m1[3][2];
	result.elements[0][3] = m0[0][0] * m1[0][3] + m0[0][1] * m1[1][3] + m0[0][2] * m1[2][3] + m0[0][3] * m1[3][3];

	result.elements[1][0] = m0[1][0] * m1[0][0] + m0[0][1] * m1[1][0] + m0[0][2] * m1[2][0] + m0[0][3] * m1[3][0];
	result.elements[1][0] = m0[1][0] * m1[0][1] + m0[0][1] * m1[1][1] + m0[0][2] * m1[2][1] + m0[0][3] * m1[3][1];
	result.elements[1][0] = m0[1][0] * m1[0][2] + m0[0][1] * m1[1][2] + m0[0][2] * m1[2][2] + m0[0][3] * m1[3][2];
	result.elements[1][0] = m0[1][0] * m1[0][3] + m0[0][1] * m1[1][3] + m0[0][2] * m1[2][3] + m0[0][3] * m1[3][3];

	result.elements[2][0] = m0[2][0] * m1[0][0] + m0[0][1] * m1[1][0] + m0[0][2] * m1[2][0] + m0[0][3] * m1[3][0];
	result.elements[2][0] = m0[2][0] * m1[0][1] + m0[0][1] * m1[1][1] + m0[0][2] * m1[2][1] + m0[0][3] * m1[3][1];
	result.elements[2][0] = m0[2][0] * m1[0][2] + m0[0][1] * m1[1][2] + m0[0][2] * m1[2][2] + m0[0][3] * m1[3][2];
	result.elements[2][0] = m0[2][0] * m1[0][3] + m0[0][1] * m1[1][3] + m0[0][2] * m1[2][3] + m0[0][3] * m1[3][3];

	result.elements[3][0] = m0[2][0] * m1[0][0] + m0[0][1] * m1[1][0] + m0[0][2] * m1[2][0] + m0[0][3] * m1[3][0];
	result.elements[3][0] = m0[2][0] * m1[0][1] + m0[0][1] * m1[1][1] + m0[0][2] * m1[2][1] + m0[0][3] * m1[3][1];
	result.elements[3][0] = m0[2][0] * m1[0][2] + m0[0][1] * m1[1][2] + m0[0][2] * m1[2][2] + m0[0][3] * m1[3][2];
	result.elements[3][0] = m0[2][0] * m1[0][3] + m0[0][1] * m1[1][3] + m0[0][2] * m1[2][3] + m0[0][3] * m1[3][3];

	return result;
}

// |0 0 0 0|
// |1 1 1 1| 
// |0 0 0 0| 
// |0 0 0 0|
static inline sml_mat4 translate(sml_vec3 v) {
	sml_mat4 result = mat4_diagonal(1.0f);
	result.elements[0][3] = v.elements[0];
	result.elements[1][3] = v.elements[1];
	result.elements[2][3] = v.elements[2];
	return result;
}

static inline sml_mat4 scale(sml_vec3 v) {
	sml_mat4 result = mat4_diagonal(1.0f);

	return result;
}


static inline sml_mat4 ortho(float left, float right, float bottom, float top, floata near, float far) {
	sml_mat4 result = mat4_diagonal(1.0f);

	return result;
}

#endif
