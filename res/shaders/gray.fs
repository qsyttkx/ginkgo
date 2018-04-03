#version 330 core
out vec4 FragColor;
in  vec2 TexCoords;
uniform float node_opacity;
uniform float tm;
// 接受一个漫反射贴图
uniform sampler2D texture_diffuse1;
void main()
{
	vec4 color = texture(texture_diffuse1, TexCoords)*vec4(1,1,1,node_opacity);
    float gray = (color.r+color.g+color.b)/3.0;
    FragColor = vec4(gray,gray,gray,color.a);
}