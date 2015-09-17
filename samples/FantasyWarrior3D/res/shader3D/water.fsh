
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D u_wave1;
uniform sampler2D u_wave2;
uniform float u_interpolate;
uniform float saturateValue;
uniform float verticalSpeed;
uniform float horizontalSpeed;
void main() {
    vec2 textCoord1 = v_texCoord;
    textCoord1.x += horizontalSpeed * CC_Time.x;
    textCoord1.x = fract(textCoord1.x);
    textCoord1.y += verticalSpeed * CC_Time.x;
    textCoord1.y = fract(textCoord1.y);
    vec3 color = texture2D(u_wave1, textCoord1).xyz;
    color += texture2D(u_wave2, v_texCoord).xyz;
    if(color.x > saturateValue)
        color = vec3(1.0);
    else
        color = texture2D(CC_Texture0, v_texCoord).xyz;
    gl_FragColor = vec4(color, 1.0);
}

