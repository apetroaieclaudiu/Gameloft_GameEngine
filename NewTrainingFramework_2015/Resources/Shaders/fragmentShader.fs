precision mediump float;

varying vec2 v_uv;
varying vec4 v_pos;

uniform sampler2D u_texture0;
uniform vec3 u_color;
uniform	float u_r;
uniform float u_R;
uniform vec3 u_cam;

void main()
{
	vec4 culoare = texture2D(u_texture0, v_uv);
	if (culoare.a < 0.1)
		discard;
		
	vec4 ps = vec4(v_pos.xyz, 1.0);
	float d = distance(vec4(u_cam, 1.0), ps);
	float x;
	x = (d - u_r) / (u_R - u_r);
	x = clamp(x, 0.0 , 1.0);
	vec4 cfog = culoare * x + vec4(60.0 / 255.0, 64.0/ 255.0, 85.0/255.0, 1.0) * (1.0 - x);
	cfog.a = 1.0;
	d = d /100.0;
	gl_FragColor = cfog;
}
