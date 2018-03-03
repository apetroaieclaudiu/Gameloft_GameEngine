precision mediump float;

varying vec2 v_uv;
varying vec2 v_uv_blend;
varying vec4 v_pos;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform vec3 u_color;
uniform	float u_r;
uniform float u_R;
uniform vec3 u_cam;

void main()
{
	vec4 vgreen =  texture2D(u_texture0, v_uv);
	vec4 vblue =   texture2D(u_texture1, v_uv);
	vec4 vrosu =   texture2D(u_texture2, v_uv);
	vec4 vblend =  texture2D(u_texture3, v_uv_blend);
	vec4 vfinal =  vblend.r * vrosu + vblend.g * vgreen + vblend.b * vblue;
	vfinal.a = 1.0;
	
	float d = distance(vec4(u_cam, 1.0), v_pos);
	float x;
	x = (d - u_r) / (u_R - u_r);
	x = clamp(x, 0.0 , 1.0);
	vec4 cfog = vfinal * x + vec4(60.0 / 255.0, 64.0/ 255.0, 85.0/255.0, 1.0) * (1.0 - x);
	cfog.a = 1.0;
	gl_FragColor = cfog;
	
}
