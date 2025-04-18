#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform float time;
uniform vec2 resolution;

#define PIXEL_FILTER 72

float plot(vec2 st,float map_y){
    return smoothstep(.02,0.,abs(st.y-map_y));
}

float circle(in vec2 _st,in float _radius){
    vec2 l=_st-vec2(.5);
    return 1.-smoothstep(_radius-(_radius*.01),
    _radius+(_radius*.01),
    dot(l,l)*4.);
}

void main()
{
    vec2 Uv=floor((uv-.5)*PIXEL_FILTER)/PIXEL_FILTER;
    
    float t=time*3.;
    vec2 gv=Uv*25;
    gv=fract(gv)-.5;
    
    float s=(.4*sin(t-length(Uv*25.))+.5)*.6;
    float m=smoothstep(s,s-.05,length(gv));
    m+=s*2.;
    
    vec3 col=vec3(s,0.,.5)*m;
    FragColor=vec4(col,1.);
}