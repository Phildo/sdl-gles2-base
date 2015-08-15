attribute vec4 position;
attribute vec4 color;

uniform float time;

varying vec4 var_color;

void main()
{
  gl_Position = position;
  gl_Position.x += sin(time+(gl_Position.x*10.));

  var_color = color;
}

