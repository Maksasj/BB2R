#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord).rgba;

    float gamma = 1.5;
    texelColor.r = pow(texelColor.r, gamma);
    texelColor.g = pow(texelColor.g, gamma);
    texelColor.b = pow(texelColor.b, gamma);

    vec3 col1 = vec3(0.612, 0.725, 0.086);
    vec3 col2 = vec3(0.549, 0.667, 0.078);
    vec3 col3 = vec3(0.188, 0.392, 0.188);
    vec3 col4 = vec3(0.063, 0.247, 0.063);

    float dist1 = length(texelColor - col1);
    float dist2 = length(texelColor - col2);
    float dist3 = length(texelColor - col3);
    float dist4 = length(texelColor - col4);

    float d = min(dist1, dist2);
    d = min(d, dist3);
    d = min(d, dist4);

    if (d == dist1) {
    texelColor.rgb = col1;
    }    
    else if (d == dist2) {
    texelColor.rgb = col2;
    }    
    else if (d == dist3) {
    texelColor.rgb = col3;
    }    
    else {
    texelColor.rgb = col4;
    } 

    finalColor = texelColor;
}