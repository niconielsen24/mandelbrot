#version 410

uniform vec2 res;


void main()
{
    vec2 coord = 3 * (gl_FragCoord.xy - vec2(920,540))/vec2(1920,1080);
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
    if( i == itr){
        gl_FragColor = vec4(0.0,0.0,0.0,1.0);
    }
    else
    {
        gl_FragColor = vec4(1.0,1.0,1.0,1.0);
    }
}