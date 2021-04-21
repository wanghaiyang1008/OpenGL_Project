#version 330 core
layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform float xOffset;

uniform mat4 trans;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

   gl_Position =  projection * view * model  * vec4(aPos.xyz, 1.0);
   FragPos = (model   * vec4(aPos.xyz, 1.0)).xyz;
   //��������Ҫ����model����Ҫ���ǵ�ģ�ͽ��зǾ��ȵ����ţ����ϵķ������ͻ�仯
   Normal = mat3(transpose(inverse(model))) * aNormal;

   TexCoord= aTexCoord;

}