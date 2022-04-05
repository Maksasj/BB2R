#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform vec2 test_light;
uniform vec3 test_light_color;

#define MAX_LIGHT 50

uniform int light_count;
uniform float light_pos_x[MAX_LIGHT];
uniform float light_pos_y[MAX_LIGHT];

uniform float ambient_light;

out vec4 finalColor;

//function to cut values to 0-1 range
float cut(float x) {
    if (x > 1.0) { return 1.0; }
    if (x < 0.0) { return 0.0; }
    return x;
}

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;
    vec2 resolution = vec2(1366, 768);
    vec2 uv = (gl_FragCoord.xy - 0.5 *resolution.xy) / resolution.y;

    vec3 ambient_light_color = vec3(1.0, 1.0, 1.0);
    vec3 amb_light = ambient_light_color * ambient_light;
    

    vec3 lig_light = vec3(0.0, 0.0, 0.0);

    for (int x = 0; x < light_count; x++) {
        vec2 light_pos = vec2(light_pos_x[x], light_pos_y[x]);
        float light_intensity = cut(1 - 10*(length(vec2(uv - light_pos)) - 0.1));
        lig_light += vec3(0.6, 0.6, 0.6) * light_intensity;
    }

    texelColor.rgb *= amb_light + lig_light;

    finalColor = vec4(texelColor.rgb, texelColor.a);
}