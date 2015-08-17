attribute vec4 position;
attribute vec2 texture_uv;

varying vec2 var_texture_uv;

void main()
{
  var_texture_uv = texture_uv;
  gl_Position = position;
}

