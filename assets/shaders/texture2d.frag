uniform sampler2D texture;
varying vec2 var_texture_uv;

void main()
{
  gl_FragColor = texture2D(texture,var_texture_uv);
}

