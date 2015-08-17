attribute vec4 position;
attribute vec2 tex_coord;

varying vec2 var_tex_coord;

void main()
{
  var_tex_coord = tex_coord;
  gl_Position = position;
}

