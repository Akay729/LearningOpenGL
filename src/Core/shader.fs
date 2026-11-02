#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec3 newPos;
uniform vec4 shaderColor; //è una gloabal variabile.
void main()
{

    //" FragColor = shaderColor;"
    FragColor = vec4(newPos, 0.0);
}
    