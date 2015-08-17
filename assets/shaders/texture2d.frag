uniform sampler2D tex;
varying vec2 var_tex_coord;

void main()
{
  gl_FragColor = texture2D(tex,var_tex_coord);
}

