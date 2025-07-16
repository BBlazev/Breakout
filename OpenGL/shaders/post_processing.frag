#version 330 core
in  vec2 TexCoords;
out vec4 color;

uniform sampler2D scene;
uniform vec2      offsets[9];
uniform int       edge_kernel[9];
uniform float     blur_kernel[9];

uniform bool chaos;
uniform bool confuse;
uniform bool shake;

vec2 BarrelUV(vec2 uv)
{
    vec2  xy  = uv * 2.0 - 1.0;
    float r2  = dot(xy, xy);

    const float k1 = 0.20;
    const float k2 = 0.10;

    xy *= (1.0 + k1 * r2 + k2 * r2 * r2);
    return xy * 0.5 + 0.5;
}

vec3 SampleOrBlack(sampler2D tex, vec2 uv)
{
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
        return vec3(0.0);
    return texture(tex, uv).rgb;
}

float Hash21(vec2 p)
{
    p = fract(p * vec2(123.34, 456.21));
    p += dot(p, p + 45.32);
    return fract(p.x * p.y);
}

vec3 RGB2HSV(vec3 c)
{
    vec4 K = vec4(0.0, -1.0/3.0, 2.0/3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)),
                d / (q.x + e),
                q.x);
}

vec3 HSV2RGB(vec3 c)
{
    vec3 p = abs(fract(c.xxx + vec3(0.0, 2.0/3.0, 1.0/3.0)) * 6.0 - 3.0);
    return c.z * mix(vec3(1.0), clamp(p - 1.0, 0.0, 1.0), c.y);
}

void main()
{
    vec2 cuv = BarrelUV(TexCoords);

    float waveShift = 0.0;
    if (chaos)
    {
        const float WAVE_FREQ = 140.0;
        const float WAVE_AMP  = 0.002;
        waveShift = sin(TexCoords.y * WAVE_FREQ) * WAVE_AMP;
    }

    vec3 resultColor = vec3(0.0);
    vec3 sample[9];

    bool useKernel = chaos || shake;
    if (useKernel)
        for (int i = 0; i < 9; ++i)
            sample[i] = SampleOrBlack(scene, cuv + offsets[i] + vec2(waveShift, 0.0));

    if (chaos)                              // edge + wave
    {
        for (int i = 0; i < 9; ++i)
            resultColor += sample[i] * float(edge_kernel[i]);
    }
    else if (confuse)                       // invert + hue whirl + static flecks
    {
        vec3 inv = 1.0 - SampleOrBlack(scene, cuv);

        vec2  centered = cuv - 0.5;
        float angle    = atan(centered.y, centered.x);       // -π … π
        float hueShift = fract(angle / (2.0 * 3.14159265));  // 0 … 1

        vec3 hsv = RGB2HSV(inv);
        hsv.x = fract(hsv.x + hueShift);                     
        resultColor = HSV2RGB(hsv);

        const float NOISE_AMP = 0.15;
        float fleck = Hash21(gl_FragCoord.xy) * 2.0 - 1.0;   // -1 … 1
        resultColor += fleck * NOISE_AMP;
    }
    else if (shake)                         // blur
    {
        for (int i = 0; i < 9; ++i)
            resultColor += sample[i] * blur_kernel[i];
    }
    else                                    // passthrough
    {
        resultColor = SampleOrBlack(scene, cuv);
    }

    const float SCAN_FREQ = 800.0;
    const float SCAN_AMP  = 0.08;
    resultColor -= sin(TexCoords.y * SCAN_FREQ) * SCAN_AMP;      // scan lines

    float vignette = smoothstep(0.80, 0.40, length(TexCoords - 0.5));
    resultColor  *= vignette;

    resultColor   = pow(resultColor, vec3(1.25));                // gamma

    color = vec4(clamp(resultColor, 0.0, 1.0), 1.0);
}
