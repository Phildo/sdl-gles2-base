uniform mat4 model_mat;
uniform mat4 model_rot_mat;
uniform mat4 view_mat;
uniform mat4 proj_mat;

uniform float time;

attribute vec4 position;
attribute vec4 color;
attribute vec2 texture_uv;

varying vec4 var_color;

void main()
{
  vec4 model_pos = model_mat * model_rot_mat * position;
  model_pos.z = sin((time*10.)+model_pos.y*10.+model_pos.x*8.+texture_uv.x)/4.;
  //fnorm = (model_rot_mat * vec4(vnorm,1.0)).xyz;

  var_color = color;
  gl_Position = proj_mat * view_mat * model_pos;
}

