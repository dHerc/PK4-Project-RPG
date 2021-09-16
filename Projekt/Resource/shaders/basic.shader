#shader vertex
#version 330 core

layout(location=0) in vec4 position;
layout(location=1) in vec2 textcoord;

uniform vec2 u_off;
uniform vec2 u_off_moving;

out vec2 v_textcoord;

void main()
{
	gl_Position = position + vec4(u_off,0.0,0.0) + vec4(u_off_moving,0.0,0.0);
	v_textcoord = textcoord;
};
#shader fragment
#version 330 core

layout(location=0) out vec4 color;

in vec2 v_textcoord;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_textcoord);
	color = texColor;
};