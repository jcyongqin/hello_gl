#version 110

in vec3 position;
in vec3 color;
in vec2 uv;

uniform mat4 MVP;

varying vec3 vColor; // 向片段着色器输出一个颜色
out vec2 TexCoord;

void main()
{
    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(position,1);
    vColor = color; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
    TexCoord = uv;
}

