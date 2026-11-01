#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 AColoror;
out vec3 vertexColor;

uniform vec3 offSet;

vec4 currenPos;

void main()
{
    //vec3 newPos = offSet * aPos;
    vec3 newPos = offSet + aPos;

    gl_Position = vec4(newPos, 1.0);
    vertexColor = AColoror;
};