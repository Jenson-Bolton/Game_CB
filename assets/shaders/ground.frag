#version 330 core

in vec3 worldPosition;

out vec4 fragmentColour;

float gridLine(vec2 worldCoordinate, float spacing)
{
    vec2 coordinate = worldCoordinate / spacing;
    vec2 derivativeWidth = max(fwidth(coordinate), vec2(0.0001));
    vec2 distanceToLine = abs(fract(coordinate - 0.5) - 0.5) / derivativeWidth;
    return 1.0 - min(min(distanceToLine.x, distanceToLine.y), 1.0);
}

void main()
{
    vec2 groundCoordinate = worldPosition.xz;
    float minorGrid = gridLine(groundCoordinate, 1.0);
    float majorGrid = gridLine(groundCoordinate, 10.0);

    vec3 ground = vec3(0.16, 0.20, 0.17);
    vec3 minorColour = vec3(0.25, 0.31, 0.27);
    vec3 majorColour = vec3(0.42, 0.49, 0.44);

    vec3 colour = mix(ground, minorColour, minorGrid * 0.65);
    colour = mix(colour, majorColour, majorGrid * 0.9);

    float xAxisWidth = max(fwidth(worldPosition.z) * 1.5, 0.015);
    float zAxisWidth = max(fwidth(worldPosition.x) * 1.5, 0.015);
    float xAxis = 1.0 - smoothstep(0.0, xAxisWidth, abs(worldPosition.z));
    float zAxis = 1.0 - smoothstep(0.0, zAxisWidth, abs(worldPosition.x));

    colour = mix(colour, vec3(0.85, 0.18, 0.16), xAxis);
    colour = mix(colour, vec3(0.18, 0.38, 0.92), zAxis);

    fragmentColour = vec4(colour, 1.0);
}
