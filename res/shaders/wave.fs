#version 330 core
out vec4 FragColor;
in  vec2 TexCoords;
uniform float node_opacity;
uniform float tm;
// 接受一个漫反射贴图
uniform sampler2D texture_diffuse1;
void main()
{
	// 波纹
    vec2 offset = vec2(sin(tm*3.1415926 - TexCoords.y * 3.1415926*8)/30.0,0);
	vec4 color = texture(texture_diffuse1, TexCoords+offset);
	color.a = color.a * node_opacity;
	FragColor = color;
}