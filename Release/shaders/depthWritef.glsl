#version 330 core
const uint MAX_LIGHT_COUNT = 100u;

varying vec4 V; 
varying vec3 N;

//in vec2 UV;
//uniform sampler2D envmap;

uniform vec4 lights_ambient[MAX_LIGHT_COUNT];
uniform vec4 lights_diffuse[MAX_LIGHT_COUNT];
uniform vec4 lights_specular[MAX_LIGHT_COUNT];
uniform vec4 lights_position[MAX_LIGHT_COUNT];
uniform vec4 lights_misc[MAX_LIGHT_COUNT];
uniform uint lights_count;

uniform vec4 material_ambient;
uniform vec4 material_diffuse;
uniform vec4 material_specular;
uniform float material_shininess;

uniform float width;
uniform float height;

out vec4 color;
uniform sampler2D depthTex;

void main(){
	vec3 E = normalize(-V).xyz;
	vec3 R;
	vec3 L;
	vec3 vTol;
	float vtollength;
	float range;
	float attenuation;
	float attenuationFactor;
	color = vec4(0.,0.,0.,0.);
	vec4 ambient = vec4(0.,0.,0.,0.);
	vec4 diffuse = vec4(0.,0.,0.,0.);
	vec4 specular = vec4(0.,0.,0.,0.);
	 
	for(uint i = 0u; i < lights_count;i++)
	{
		vTol = (lights_position[i] - V).xyz;
		vtollength = length(vTol);
		range = lights_misc[i].x;
		if(range == 0. || vtollength < range)
		{
			attenuation = lights_misc[i].y;
			attenuationFactor = 1.;
			if(attenuation < 1. && range != 0.)
			{
				attenuationFactor = ((range - vtollength) / ((1-attenuation) * range));
			}
			clamp(attenuationFactor,0.0,1.0);
			L = normalize(vTol).xyz;
			R = normalize(-reflect(L.xyz,N));
			ambient += material_ambient * lights_ambient[i] * attenuationFactor;
			diffuse += dot(L,N) * material_diffuse * lights_diffuse[i] * attenuationFactor;
			diffuse = clamp(diffuse,0.0,1.0);
			specular += pow(max(0.0,dot(R,E)),0.3*material_shininess) * material_specular*lights_specular[i]*attenuationFactor;
			specular += clamp(specular,0.0,1.0);
		}
	}


	float textureZ = texture(depthTex,vec2(clamp(gl_FragCoord.x / width,0.0,1.0),clamp(gl_FragCoord.y / height,0.0,1.0))).x;
	
	if(textureZ < gl_FragCoord.z) 
	{
		color = vec4((diffuse + ambient + specular).xyz,material_diffuse.a);
	}else
	{
		discard;
	}
}
	
