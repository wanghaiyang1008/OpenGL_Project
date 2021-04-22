#define GLEW_STATIC
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include"Camera.h"
#include"Shader.h"
#include "Material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"

float offset = 1.0f;
float mixValue = 0.2f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


		
#pragma region Model Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

Camera camera(cameraPos, glm::radians(15.0f), glm::radians(180.0f), cameraUp);

LightDirectional light = LightDirectional(glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(glm::radians(90.0f), 0, 0),
	glm::vec3(1.0f, 1.0f,1.0f));

LightPoint lightP0 = LightPoint(glm::vec3(1.0f, .0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 0.0f, 0.0f));

LightPoint lightP1 = LightPoint(glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0f, 1.0f, 0.0f));

LightPoint lightP2 = LightPoint(glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0.0f, 0.0f, 1.0f));

LightPoint lightP3 = LightPoint(glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightSpot lightS = LightSpot(glm::vec3(0.5f, 3.0f, -1.0f),
	glm::vec3(glm::radians(90.0f), 0, 0),
	glm::vec3(1.0f, 1.0f, 1.0f));

#pragma region Input Declare
float lastX = 400, lastY = 300;
bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) // 这个bool变量初始时是设定为true的
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

//键盘响应
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}



	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.speedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -1.0f;
	}
	else {
		camera.speedX = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.speedY = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.speedY = 1.0f;
	}
	else {
		camera.speedY = 0;
	}
	camera.updateCameraPosition();
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
#pragma endregion

//绑定纹理
unsigned int LoadImageToGPU(const char* filename,GLint internalFormat,GLint format,int texturSlot) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0+ texturSlot); // 在绑定纹理之前先激活纹理单元
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);//图片正向
	unsigned char *data1 = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);
	return texture;
}

int main() {

#pragma region Open a Window
	glfwInit(); 
	//OpenGL主版本号(Major)和次版本号(Minor)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	//	Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//	Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to Init GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

#pragma endregion

#pragma region Init Sharder Program

	Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");

#pragma endregion
	
#pragma region Init Sharder Program

	Material* myMaterial = new Material(myShader,
		LoadImageToGPU("container2.png",GL_RGBA,GL_RGBA,Shader::DIFFUSE),
		LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
		glm::vec3(1.0f, 1.0f, 1.0f),
		64.0f
		);

#pragma endregion

#pragma region Init and Load Model to VAO,VBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

#pragma endregion

#pragma region Init and Load Texture
	/*unsigned int texture1;
	texture1 = LoadImageToGPU("container.jpg",GL_RGB,GL_RGB,0);

	unsigned int texture2;
	texture2 = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 1);*/

	//LoadImageToGPU
#pragma endregion
	

	//	 渲染循环Render Loop
	while (!glfwWindowShouldClose(window)) {
		
		//Camera camera(cameraPos, cameraPos + cameraFront, cameraUp);
		//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0 , 0), glm::vec3(0, 1.0f, 0));
		//Camera camera(cameraPos, glm::radians(15.0f), glm::radians(180.0f), cameraUp);
		
		glm::mat4 trans;

		glm::mat4 model;
		//返回照相机的位置
		glm::mat4 view;

		glm::mat4 projection;
		
		
		// 输入
		processInput(window);

		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);


		//清屏
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (unsigned int i = 0; i < 10; i++)
		{
			
			
			//Set Model matrix
			model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			//model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
			
			//Set View and Projection Matrices here if you want


			//Set Material -> Shader Oregram
			myShader->setFloat("xOffset", offset);
			myShader->setFloat("mixValue", mixValue);
			myShader->use();


			//Set Material -> Texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0 + 1);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);


			//Set Material -> Uniforms
			//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0); // 手动设置
			//myShader->setInt("ourFace", 1); // 或者使用着色器类设置
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "trans"), 1, GL_FALSE, glm::value_ptr(trans));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glUniform3f(glGetUniformLocation(myShader->ID, "objectColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
			glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.pos"), light.positon.x, light.positon.y, light.positon.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), light.color.x, light.color.y, light.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), light.direction.x, light.direction.y, light.direction.z);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.positon.x, lightP0.positon.y, lightP0.positon.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.positon.x, lightP1.positon.y, lightP1.positon.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.positon.x, lightP2.positon.y, lightP2.positon.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.positon.x, lightP3.positon.y, lightP3.positon.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);

			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.positon.x, lightS.positon.y, lightS.positon.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);
			glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
			glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);


			

			

			//Set Model
			glBindVertexArray(VAO);

			//Drawcall
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}




		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();

		
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();

	return 0;
}


