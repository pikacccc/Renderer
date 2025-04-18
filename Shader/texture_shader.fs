#version 330 core
in vec2 uv;

out vec4 FragColor;

uniform float time;
uniform vec2 resolution;

float plot(vec2 st,float map_y){
    return smoothstep(.02,0.,abs(st.y-map_y));
}

float circle(vec2 center,vec2 uv,float r){
    vec2 dir=uv-center;
    float dis=length(dir);
    // return 1-step(r,dis);
    return 1.-smoothstep(r-(r*.01),r+(r*.01),dis);
}

float box(in vec2 _st, in vec2 _size){
    _size = vec2(0.5) - _size*0.5;
    vec2 uv = smoothstep(_size,
                        _size+vec2(0.001),
                        _st);
    uv *= smoothstep(_size,
                    _size+vec2(0.001),
                    vec2(1.0)-_st);
    return uv.x*uv.y;
}

float cross(in vec2 _st, float _size){
    return  box(_st, vec2(_size,_size/4.)) +
            box(_st, vec2(_size/4.,_size));
}

void main()
{
    vec2 Uv=uv;
    
    vec2 translate=vec2(cos(time),sin(time));
    Uv+=translate*0.35;
    
    vec3 col=vec3(Uv.x,Uv.y,0.)+ vec3(cross(Uv,0.25));
    gl_FragColor=vec4(col,1.);
}