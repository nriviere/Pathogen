#version 330 core
 
in vec2 UV;
 
layout(location = 0) out vec4 color;

uniform sampler2D renderedTexture;
uniform sampler2D blendTexture;

void main(){
	vec4 new = texture(renderedTexture,UV);
	vec4 alr = texture(blendTexture,UV);
	color = vec4(alr.rgb*alr.a,alr.a) + new * (1 - alr.a);


	/*if(alr.a == 1)
	{
		color = vec4(1.,1.,1.,1.);	
	}*/
}
