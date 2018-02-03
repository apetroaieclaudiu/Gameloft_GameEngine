precision mediump float;

varying vec2 v_uv;

uniform sampler2D u_texture0;

void main()
{
	vec4 culoare = texture2D(u_texture0, v_uv);
	if (culoare.a < 0.1)
		discard;
	gl_FragColor = culoare;
}
