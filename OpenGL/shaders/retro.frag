#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D scene;
uniform vec2 resolution;
uniform float distortion;
uniform float saturation;
uniform float gamma;

uniform float borderThickness;   
uniform float lineSpacing;       
uniform float lineThickness;     
uniform vec3  borderColor;       
uniform vec3  bgColor;           
uniform vec3  lineColor;         

uniform float pixelSize;         
uniform float scanlineIntensity; 
uniform int   scanlineCount;     
uniform float chromaOffset;      
uniform float noiseIntensity;    

float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    vec2 uv = TexCoords * 2.0 - 1.0;
    float r2 = dot(uv,uv);
    uv *= (1.0 + distortion * r2);
    vec2 d = uv * 0.5 + 0.5;
  
    if (d.x < 0.0 || d.x > 1.0 || d.y < 0.0 || d.y > 1.0)
    {
        bool left   = (d.x < 0.0);
        bool right  = (d.x > 1.0);
        bool top    = (d.y > 1.0);
        bool bottom = (d.y < 0.0);

        vec3 col = bgColor;
        // border line
        if (TexCoords.x < borderThickness ||
            TexCoords.x > 1.0 - borderThickness ||
            TexCoords.y < borderThickness ||
            TexCoords.y > 1.0 - borderThickness)
        {
            col = borderColor;
        }

        // scan‐lines on bezel
        float tU = lineThickness / resolution.y;
        float sU = lineSpacing   / resolution.y;
        if (left || right) {
            if (fract(TexCoords.y / sU) < tU) col = lineColor;
        }
        else if (top || bottom) {
            float sU_x = lineSpacing / resolution.x;
            float tU_x = lineThickness / resolution.x;
            if (fract(TexCoords.x / sU_x) < tU_x) col = lineColor;
        }

        FragColor = vec4(col,1.0);
        return;
    }


    vec2 pixelUV = floor(d * resolution / pixelSize) * pixelSize / resolution;

    float co = chromaOffset / resolution.x;
    vec3 col;
    col.r = texture(scene, pixelUV + vec2( co, 0)).r;
    col.g = texture(scene, pixelUV           ).g;
    col.b = texture(scene, pixelUV - vec2( co, 0)).b;

    float gray = dot(col, vec3(0.299,0.587,0.114));
    col = mix(vec3(gray), col, saturation);
    col = pow(col, vec3(1.0/gamma));

    float scanY = fract((TexCoords.y * float(scanlineCount)));
    float scanMod = smoothstep(0.5 - scanlineIntensity*0.5,
                               0.5 + scanlineIntensity*0.5,
                               scanY);
    col *= mix(1.0, 1.0 - scanlineIntensity, scanMod);

    float n = rand(gl_FragCoord.xy) * noiseIntensity;
    col += n;

    FragColor = vec4(col,1.0);
}
