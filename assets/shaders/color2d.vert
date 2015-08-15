attribute vec4 position;
attribute vec4 color;

varying vec4 var_color;

void main()
{
  var_color = color;
  gl_Position = position;
}

