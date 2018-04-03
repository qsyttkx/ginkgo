#version 330 core
out vec4 FragColor;
in  vec2 TexCoords;
uniform float node_opacity;
uniform float tm;
// 接受一个漫反射贴图
uniform sampler2D texture_diffuse1;
void main()
{
    vec4 color = vec4(0);
	// 模糊
	for(int dx=-2;dx<=2;++dx)
	for(int dy=-2;dy<=2;++dy)
		color+=texture(texture_diffuse1, TexCoords+vec2(dx/80.0,dy/45.0)*(0.5*sin(tm*3.14159)+0.5));
	color = color/25.0;
	color.a = color.a * node_opacity;
	FragColor = color;
}