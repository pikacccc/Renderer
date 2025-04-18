#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aUv;

out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{  

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    uv = aUv;
}