// dummy shader;

//
#type vertex
#version 330 core

layout(location = 0) in vec3 i_Position;
layout(location = 1) in vec4 i_Color;
layout(location = 2) in vec2 i_Texcoord;
layout(location = 3) in float i_Texid;
layout(location = 4) in float i_TilingFactor;

uniform mat4 u_ViewProjMat;

out vec4 ex_Color;
out vec2 ex_Texcoord;
out float ex_Texid;
out float ex_TilingFactor;

void main() 
{
    ex_Color = i_Color;
    ex_Texcoord = i_Texcoord;
    ex_Texid = i_Texid;
    ex_TilingFactor = 1.0f;
    gl_Position = u_ViewProjMat * vec4(i_Position, 1.0f);
}

//
#type fragment
#version 330 core

layout(location = 0) out vec4 o_Color;

in vec4 ex_Color;
in vec2 ex_Texcoord;
in float ex_Texid;
in float ex_TilingFactor;

uniform sampler2D u_Textures[32];

void main()
{
    if (ex_Texid >= 0.0f && ex_Texid < 32.0f)
    {
        o_Color = ex_Color * texture(u_Textures[int(ex_Texid)], ex_Texcoord * ex_TilingFactor);
    }
    else
    {
        o_Color = ex_Color;
    }
    //o_Color = ex_Color;
}
