#version 330 core
in vec3 in_position;
in vec3 in_normal;
in vec2 in_texcoord;

varying vec3 N;

varying vec4 V; 

//out vec2 UV;
//inout vec4 C;

uniform mat4 MV;
uniform mat4 P;

uniform uint lights_count;

uniform float t;

void main(void)
{
	vec4 position = vec4(in_position.x  ,in_position.y,in_position.z,1.0);
	mat3 NM = mat3(transpose(inverse(MV)));
	V = MV * position ;
	uint i;

	N = normalize(NM * in_normal);
	gl_Position =  P * MV *  position;
}


