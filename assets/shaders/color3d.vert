uniform mat4 model_mat;
uniform mat4 model_rot_mat;
uniform mat4 view_mat;
uniform mat4 proj_mat;

attribute vec4 position;
attribute vec4 color;

varying vec4 var_color;

void main()
{
  vec4 fpos = model_mat * model_rot_mat * position;
  //fnorm = (model_rot_mat * vec4(vnorm,1.0)).xyz;

  var_color = color;
  gl_Position = proj_mat * view_mat * fpos;
}

