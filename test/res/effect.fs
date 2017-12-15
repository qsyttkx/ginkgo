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
	vec2 offset = vec2(0);
	float x = (TexCoords.x-0.5)*1280;
	float y = (TexCoords.y-0.5)*720;
	float len = sqrt(x*x+y*y);
	offset = normalize(vec2(x,y))*0.002*sin(-tm*3.14*2+len/3.14/5);
	vec4 color = vec4(0);
	// 模糊
	for(int dx=-1;dx<=1;++dx)
	for(int dy=-1;dy<=1;++dy)
		color+=texture(texture_diffuse1, TexCoords+offset+vec2(dx/640.0,dy/360.0));
	FragColor = color/9.0*vec4(0.8,1.0,0.9,1.0)*0.75+0.125;
};