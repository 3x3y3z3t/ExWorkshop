// Flat Color Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 l_Position;
layout(location = 1) in vec4 l_Color;

layout(location = 0) out vec4 b_Color;

uniform mat4 u_ViewProjMat;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjMat * u_Transform * vec4(l_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) in vec4 b_Color;

layout(location = 0) out vec4 o_Color;

void main()
{
    //o_color = i_Color;
    o_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
