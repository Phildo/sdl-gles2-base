varying vec4 var_color;

uniform float time;

void main()
{
  gl_FragColor = var_color;
  gl_FragColor.x = 0.;
  gl_FragColor.y = sin(time);
}

