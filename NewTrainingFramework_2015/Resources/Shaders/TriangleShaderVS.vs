attribute vec3 a_posL;
attribute vec3 a_color;

uniform mat4 u_matrix;

varying vec3 v_color;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
posL = posL * u_matrix;
v_color	= a_color;
gl_Position = posL;
}
   