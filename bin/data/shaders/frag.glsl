#version 120
#extension GL_ARB_texture_rectangle : enable
//A simple fragment shader

uniform sampler2DRect tex;

void main()
{
  vec2 st = gl_TexCoord[0].st;
  vec4 color = texture2DRect(tex, st);
  gl_FragColor = color;
}   
