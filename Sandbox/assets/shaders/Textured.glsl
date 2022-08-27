// Flat Color Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 l_Position;
layout(location = 1) in vec2 l_Texcoord;

out vec2 b_Texcoord;

uniform mat4 u_ViewProjMat;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjMat * u_Transform * vec4(l_Position, 1.0);
    b_Texcoord = l_Texcoord;
}

#type fragment
#version 330 core

in vec2 b_Texcoord;

layout(location = 0) out vec4 o_Color;

uniform sampler2D u_Textures[32];

void main()
{



    o_Color = texture(u_Textures[0], b_Texcoord);
    //o_Color = vec4(b_Texcoord, 0.0f, 1.0f);
}
