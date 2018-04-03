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
    float treshold = 0.4*sin(tm*3.14159)+0.5;
    float v = gray>treshold?1.0:0.0;
    FragColor = vec4(0.8*v,0.2*v,0,color.a);
}