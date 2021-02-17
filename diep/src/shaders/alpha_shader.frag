uniform sampler2D texture;
uniform float alpha;
uniform float time;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy * time, vec2(12.9898, 78.233))) * 43758.5453);
}

void main()
{
    vec4 pixel_color = texture2D(texture, gl_TexCoord[0].xy);
    if (pixel_color.a != 0)
    {
        pixel_color.a = alpha * rand(gl_TexCoord[0].xy);
        pixel_color.xyz *= alpha;
    }
    gl_FragColor = pixel_color;
}
