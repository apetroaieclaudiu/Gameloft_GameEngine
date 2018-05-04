attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 u_matrix;
uniform mat4 u_world;

varying vec2 v_uv;
varying vec4 v_pos;

void main()
{
gl_Position = u_matrix * vec4(a_posL, 1.0);
v_pos = u_world * vec4(a_posL, 1.0);
v_uv = a_uv;
}
   