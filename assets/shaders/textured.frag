#version 330 core

in vec2 textureCoordinate;

out vec4 fragmentColour;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    fragmentColour = mix(
        texture(texture1, textureCoordinate),
        texture(texture2, textureCoordinate),
        0.25
    );
}
