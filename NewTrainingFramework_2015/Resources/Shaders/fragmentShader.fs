precision mediump float;

varying vec2 v_uv;
varying vec4 v_pos;
varying vec4 N;

uniform sampler2D u_texture0;
uniform vec3 u_color;
uniform	float u_r;
uniform float u_R;
uniform vec3 u_cam;
uniform vec3 c_amb;
uniform vec3 c_luminaDiff;
uniform vec3 c_luminaSpec;
uniform float SpecPower;
uniform vec3 L;
uniform float ratio;
uniform vec3 u_spot_pos;
uniform float u_spot_opening;
uniform vec3 u_lights_type;
uniform float u_spot_attenuation;

void main()
{
	vec4 culoare = texture2D(u_texture0, v_uv);
	if (culoare.a < 0.1)
		discard;
	vec4 E = normalize(vec4(u_cam, 1.0) - v_pos);
	vec4 Le = normalize(vec4(L, 0.0));
	vec4 Ne = normalize(N);
	vec4 R = reflect(Le, Ne);
	//culoare = ratio * vec4(c_amb / 255.0, 1.0) + (1.0 - ratio) * vec4(vec3(culoare.xyz * c_luminaDiff * max(dot(Ne, -Le), 0.0) / 255.0) + vec3(c_luminaSpec/255.0 * pow(max(dot(R,Ne), 0.0), SpecPower)), culoare.a);
	
	//culoare = ratio * vec4(c_amb / 255.0, 1.0) + (1.0 - ratio) * vec4(vec3(c_luminaSpec/255.0 * pow(max(dot(R,Ne), 0.0), SpecPower)), culoare.a);
	//culoare =vec4(vec3(c_luminaSpec/255.0 * pow(max(dot(R,Ne), 0.0), SpecPower)), culoare.a);
	
	float alpha = u_spot_opening;
	vec4 dist = v_pos - vec4(u_spot_pos, 1.0);
	float beta = dot(Le, normalize(dist));
	float unghi_beta = acos(beta);
	culoare = ratio * vec4(c_amb / 255.0, 1.0) + u_lights_type.z * ((1.0 - ratio) * vec4(vec3(culoare.xyz * c_luminaDiff * max(dot(Ne, -Le), 0.0) / 255.0) + vec3(c_luminaSpec/255.0 * pow(max(dot(R,Ne), 0.0), SpecPower)), culoare.a)) * cos( clamp(unghi_beta, 0.0, alpha) * 3.14 / (2.0 * alpha)) * u_spot_attenuation;
	
	
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
