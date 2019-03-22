#version 110

in vec2 position;
in vec3 color;

varying vec3 vColor; // 向片段着色器输出一个颜色


void main()
{
    gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    vColor = color; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
}

