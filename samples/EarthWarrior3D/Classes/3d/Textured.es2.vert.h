static const char* baseVertexShader = STRINGIFY(

attribute vec4 Position;
attribute vec3 Normal;
attribute vec2 TextureCoord;

uniform vec3 DiffuseMaterial;
uniform mat3 NormalMatrix;

varying vec4 DestinationColor;
varying vec2 TextureCoordOut;

void main(void)
{
    DestinationColor = vec4(DiffuseMaterial, 1);
    gl_Position = CC_PMatrix * CC_MVMatrix * Position;
    TextureCoordOut = TextureCoord;
}
);


// pure black vert shader
static const char* outLineShader = STRINGIFY(
                                                
attribute vec4 Position;
attribute vec3 Normal;
uniform float OutlineWidth;
uniform mat3 NormalMatrix;
void main(void)
{
    vec4 pos = Position;
    vec3 normal = Normal;
    pos.xyz += Normal * OutlineWidth;
    gl_Position = CC_PMatrix * CC_MVMatrix * pos;
}
);
