#version 130
#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D _maskText;
uniform sampler2D _mainText;
void main()
{

vec2 coord=gl_TexCoord[0].xy;
//coord.y=1.0-coord.y;


vec4 color=gl_FragColor;
color.a=1.0;
vec4 mask=texture2D(_maskText, coord);
vec4 main=texture2D(_mainText, coord);
color=mask*main;
gl_FragColor=color;
}