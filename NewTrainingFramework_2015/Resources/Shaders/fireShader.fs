precision mediump float;

varying vec2 v_uv;
varying vec4 v_pos;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

uniform vec3 u_color;
uniform	float u_r;
uniform float u_R;
uniform vec3 u_cam;
uniform	float u_time;
uniform float u_dispMax;

void main()
{
	vec2 disp = texture2D(u_texture2, vec2(v_uv.x, v_uv.y + u_time)).rg;
	
	vec2 offset = disp * 2.0 * u_dispMax - u_dispMax;
	
	vec2 v_uv_disp = v_uv + offset;
	
	vec4 c_fire = texture2D(u_texture0, v_uv_disp);
	vec4 c_alpha = texture2D(u_texture1, v_uv);
	
	c_fire.a = c_fire.a * c_alpha.r;
	gl_FragColor = c_fire;	
//	gl_FragColor = vec4(v_uv_disp.x, v_uv_disp.y, 0.0, 1.0);
}
