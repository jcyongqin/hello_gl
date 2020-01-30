#version 330 core

uniform sampler2D ourTexture;

in vec3 vColor;// 向片段着色器输出一个颜色
in vec2 vTexCoord;// 向片段着色器输出一个颜色

out vec4 FragColor;

void main()
{
    //    vec4 TextureColor = texture2D(ourTexture, TexCoord);
    FragColor = vec4(vColor, 1.0);
    //    vFragColor = 0.5 * (TextureColor + vec4(vColor, 0));
}