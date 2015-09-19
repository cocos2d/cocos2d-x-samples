static const char* baseTexturedFrag = STRINGIFY(

#ifdef GL_ES
varying lowp vec4 DestinationColor;
varying mediump vec2 TextureCoordOut;
#else
varying vec4 DestinationColor;
varying vec2 TextureCoordOut;
#endif

uniform sampler2D Sampler;

void main(void)
{
    gl_FragColor = texture2D(Sampler, TextureCoordOut) * DestinationColor;
}
);