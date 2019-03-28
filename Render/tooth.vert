#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));    //在世界空间中进行所有的光照计算, 需要一个在世界空间中的顶点位置,顶点位置属性乘以模型矩阵（不是观察和投影矩阵）来把它变换到世界空间坐标
    Normal = mat3(transpose(inverse(model))) * aNormal;    //法线矩阵, 移除对法向量错误缩放的影响

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}