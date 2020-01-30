#version 330 core

uniform mat4 MVP;

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 vColor;// 向片段着色器输出一个颜色
out vec2 vTexCoord;

void main()
{
    // Output position of the vertex, in clip space : MVP * position
    //    gl_Position =  MVP * vec4(position, 1);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vColor = aColor;// 将ourColor设置为我们从顶点数据那里得到的输入颜色
    vColor = vec3(0.0, 0.0, 0.0);// 把输出变量设置为暗红色
    vTexCoord = aTexCoord;
}

