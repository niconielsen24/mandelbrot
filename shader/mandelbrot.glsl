#version 410

uniform vec2 res;

vec4 map_to_color(float t) {
    float r = 0.0f + (t * (31.0f/100.0f))  / 255.0f;
    float g = 0.0f + (t * (81.0f/100.0f))  / 255.0f;
    float b = 0.0f + (t * (255.0f/100.0f)) / 255.0f;

    return vec4(r, g, b, 1.0);
}

void main()
{
    vec2 coord = 4 * (gl_FragCoord.xy - vec2(920,540))/vec2(1920,1080);
    int i = 0;
    int itr = 100;
    float x = 0;
    float y = 0;

    while(i < itr)
    {
        float xTemp = x * x - y * y + coord.x;
        y = 2.0 * x * y + coord.y;
        x = xTemp;

        if ( x * x + y * y > 4)
        {
            break;
        }
        i += 1;
    }
    if( i == itr)
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        gl_FragColor = map_to_color(float(i));
    }
}