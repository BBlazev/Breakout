#version 330 core
in vec2 TexCoords;
in vec4 ParticleColor;
out vec4 color;

uniform sampler2D sprite;

// RETRO CONTROLS:
uniform vec2  spriteResolution;  
uniform float pixelSize;         
uniform int   colorLevels;       
uniform float noiseIntensity;    

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec2 uv = TexCoords;
    vec2 gridUV = floor(uv * spriteResolution / pixelSize) * pixelSize / spriteResolution;

    vec4 col = texture(sprite, gridUV) * ParticleColor;

    float levels = float(colorLevels);
    col.rgb = floor(col.rgb * levels) / levels;

    float n = rand(gl_FragCoord.xy) * noiseIntensity;
    col.rgb += n;

    color = col;
}
