#version 110

varying vec4 gl_FragColor;
varying vec3 vColor; // 向片段着色器输出一个颜色

void main()
{
    gl_FragColor = vec4(vColor, 1.0);
}