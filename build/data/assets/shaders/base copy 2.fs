#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

struct Spot {
    vec2 pos; 
    float inner;
    float radius;
};

#define MAX_SPOTS 50

uniform int light_count;
uniform Spot spots[MAX_SPOTS];
uniform float ambient_light;

float cut(float x) {
    if (x > 1.0) { return 1.0; }
    if (x < 0.0) { return 0.0; }
    return x;
}

void main()
{
    float alpha = 1.0*(1 - ambient_light);
    vec2 resolution = vec2(1366, 768);
    vec2 uv = (gl_FragCoord.xy - 0.5 *resolution.xy) / resolution.y;

    float light_intensity = 0.0;
    
    for (int x = 0; x < light_count; x++) {
        if (light_intensity >= 1.0) { break; }
        light_intensity += cut(1 - 10*(length(vec2(uv - spots[x].pos)) - 0.1));
    }

    alpha -= light_intensity;

    finalColor = vec4(0.0, 0.0, 0.0, alpha);
}