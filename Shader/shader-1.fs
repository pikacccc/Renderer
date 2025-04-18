#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 world_position;

uniform sampler2D texture_diffuse1;
uniform vec3 light_color;
uniform vec3 light_position;
uniform vec3 view_position;
uniform vec3 camera_look;

void main()
{    
    float ambient_strength = 0.5;
    vec3 ambient = light_color * ambient_strength;

    vec3 normal_nor = normalize(normal);

    vec3 light_direction = normalize(light_position - world_position);
    vec3 diffuse = max(dot(normal_nor , light_direction), 0) * light_color;
    
    float specular_strength = 0.9f;

    vec3 specular = light_color * specular_strength * pow(max(dot(reflect(-light_direction, normal_nor), -camera_look), 0), 64);

    vec4 result =vec4(ambient + diffuse + specular, 1.0) * texture(texture_diffuse1, TexCoords);

    FragColor = result;
}