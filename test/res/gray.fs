#version 330 core
out vec4 FragColor;
in  vec2 TexCoords;
uniform float node_opacity;
// 接受一个漫反射贴图
uniform sampler2D texture_diffuse1;
void main()
{
	vec4 color = texture(texture_diffuse1, TexCoords);
	float value = dot(color.rgb,vec3(1.0/3.0));
	// 提高对比度
	value = value - 0.5;
	value = value * 50;
	value = value + 0.5;
	float alpha = color.a;
	FragColor = vec4(0.7,0.1,0,(1-value)*alpha*node_opacity);
};