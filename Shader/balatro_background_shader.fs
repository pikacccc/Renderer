#version 330 core
in vec2 uv;

out vec4 FragColor;

uniform float time;
uniform vec2 resolution;

#define SPIN_ROTATION-2.
#define SPIN_SPEED 7.
#define OFFSET vec2(0.)
#define COLOUR_1 vec4(.871,.267,.231,1.)
#define COLOUR_2 vec4(0.,.42,.706,1.)
#define COLOUR_3 vec4(.086,.137,.145,1.)
#define CONTRAST 3.5
#define LIGTHING.4
#define SPIN_AMOUNT.25
#define PIXEL_FILTER 365.
#define SPIN_EASE 1.
#define PI 3.14159265359
#define IS_ROTATE false

vec4 effect(vec2 screenSize,vec2 screen_coords){
    float pixel_size=length(screenSize.xy)/PIXEL_FILTER;
    vec2 uv=(floor(screen_coords.xy*(1./pixel_size))*pixel_size-.5*screenSize.xy)/length(screenSize.xy)-OFFSET;
    float uv_len=length(uv);
    
    float speed=(SPIN_ROTATION*SPIN_EASE*.2);
    if(IS_ROTATE){
        speed=time*speed;
    }
    speed+=302.2;
    float new_pixel_angle=atan(uv.y,uv.x)+speed-SPIN_EASE*20.*(1.*SPIN_AMOUNT*uv_len+(1.-1.*SPIN_AMOUNT));
    vec2 mid=(screenSize.xy/length(screenSize.xy))/2.;
    uv=(vec2((uv_len*cos(new_pixel_angle)+mid.x),(uv_len*sin(new_pixel_angle)+mid.y))-mid);
    
    uv*=30.;
    speed=time*(SPIN_SPEED);
    vec2 uv2=vec2(uv.x+uv.y);
    
    for(int i=0;i<5;i++){
        uv2+=sin(max(uv.x,uv.y))+uv;
        uv+=.5*vec2(cos(5.1123314+.353*uv2.y+speed*.131121),sin(uv2.x-.113*speed));
        uv-=1.*cos(uv.x+uv.y)-1.*sin(uv.x*.711-uv.y);
    }
    
    float contrast_mod=(.25*CONTRAST+.5*SPIN_AMOUNT+1.2);
    float paint_res=min(2.,max(0.,length(uv)*(.035)*contrast_mod));
    float c1p=max(0.,1.-contrast_mod*abs(1.-paint_res));
    float c2p=max(0.,1.-contrast_mod*abs(paint_res));
    float c3p=1.-min(1.,c1p+c2p);
    float light=(LIGTHING-.2)*max(c1p*5.-4.,0.)+LIGTHING*max(c2p*5.-4.,0.);
    return(.3/CONTRAST)*COLOUR_1+(1.-.3/CONTRAST)*(COLOUR_1*c1p+COLOUR_2*c2p+vec4(c3p*COLOUR_3.rgb,c3p*COLOUR_1.a))+light;
}

void main()
{
    FragColor=effect(vec2(1,1),uv);
}