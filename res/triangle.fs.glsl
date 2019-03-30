#version 110

varying vec3 vColor;// 向片段着色器输出一个颜色
varying vec2 TexCoord;// 向片段着色器输出一个颜色
uniform sampler2D ourTexture;

void main()
{
    vec4 TextureColor=texture2D(ourTexture, TexCoord);
    gl_FragColor = 0.5*(TextureColor+ vec4(vColor, 0));
}