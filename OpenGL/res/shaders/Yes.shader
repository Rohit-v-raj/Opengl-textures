#vertex shader
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main()
{
    gl_Position = position;
    v_TexCoord = texCoord;
};

#fragment shader
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_color;
uniform sampler2D u_Texture;

void main()
{
    //color = vec4(1.0, 1.0, 0.0, 1.0);
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
};