#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
uniform vec4 shaderColor; //è una gloabal variabile.
void main()
{
    //" FragColor = shaderColor;"
    FragColor = vec4(vertexColor, 1.0);
}
    