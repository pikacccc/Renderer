#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform float time;
uniform vec2 resolution;

#define PIXEL_FILTER 72

float opSmoothUnion(float d1,float d2,float k)
{
    float h=clamp(.5+.5*(d2-d1)/k,0.,1.);
    return mix(d2,d1,h)-k*h*(1.-h);
}

float sdSphere(vec3 p,float s)
{
    return length(p)-s;
}

float map(vec3 p)
{
    float d=2.;
    for(int i=0;i<16;i++){
        float fi=float(i);
        float fina_time=time*(fract(fi*412.531+.513)-.5)*2.;
        d=opSmoothUnion(
            sdSphere(p+sin(fina_time+fi*vec3(52.5126,64.62744,632.25))*vec3(2.,2.,.8),mix(.5,1.,fract(fi*412.531+.5124))),
            d,
            .4
        );
    }
    return d;
}

vec3 calcNormal(in vec3 p)
{
    const float h=1e-5;// or some other value
    const vec2 k=vec2(1,-1);
    return normalize(k.xyy*map(p+k.xyy*h)+
    k.yyx*map(p+k.yyx*h)+
    k.yxy*map(p+k.yxy*h)+
    k.xxx*map(p+k.xxx*h));
}

void main()
{
    vec2 Uv = floor(uv*PIXEL_FILTER)/PIXEL_FILTER;
    
    // screen size is 6m x 6m
    vec3 rayOri=vec3((Uv-.5)*6.,3.);
    vec3 rayDir=vec3(0.,0.,-1.);
    
    float depth=0.;
    vec3 p;
    
    for(int i=0;i<64;i++){
        p=rayOri+rayDir*depth;
        float dist=map(p);
        depth+=dist;
        if(dist<1e-6){
            break;
        }
    }
    
    depth=min(6.,depth);
    vec3 n=calcNormal(p);
    float b=max(0.,dot(n,vec3(.577)));
    vec3 col=(.5+.5*cos((b+time*3.)+Uv.xyx*2.+vec3(0,2,4)))*(.85+b*.35);
    col*=exp(-depth*.15);
    
    FragColor=vec4(col,1.-(depth-.5)/2.);
}