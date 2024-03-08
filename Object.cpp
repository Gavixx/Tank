#include "Object.h"
#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

//�������
int Createwindow_();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void Paint();


// ���������
const unsigned int SCR_WIDTH = 1440;
const unsigned int SCR_HEIGHT = 1024;



const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";



int Object::BackGround()
{
	Createwindow_();
	Paint();


	
	return 0;

}

// glfw: ������ ���, ����� ���������� ������� ���� (������������� ��� ������������ ��������), ���������� ������ callback-�������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// ����������, ��� ���� ��������� ������������� ����� �������� ����. 
	// �������� ��������, ������ ���� �� Retina-�������� ����� ����������� ������, ��� ������� � ���������
	glViewport(0, 0, width, height);
}
// ��������� ���� ������� �����: ������ GLFW � �������/���������� ������ �� ���������� � ������ ����� � ��������������� ��������� ������ �������
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int Createwindow_()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// glfw: �������� ����
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "My first game <3  ", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	
	GLFWimage images[1];
	images[0].pixels = stbi_load("image.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	
	

	if (images[0].pixels == nullptr)
	{
		// Handle error
		printf("Error loading image: %s\n", stbi_failure_reason());
	}
	else
	{
		glfwSetWindowIcon(window, 1, images);
		stbi_image_free(images[0].pixels);
	}

	// glad: �������� ���� ���������� �� OpenGL-�������
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	//////
	//////     Shaiders
	//////
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// �������� �� ������� ������ �������������� ���������� �������
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ����������� ������
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// �������� �� ������� ������ �������������� ������������ �������
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	// ���������� ��������
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// ���������� ������ (� �������) � ��������� ��������� ���������
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // ����� �������
		 0.5f, -0.5f, 0.0f, // ������ �������
		 0.0f,  0.5f, 0.5f,
		 // ������� �������   
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	// ������� ��������� ������ ���������� �������, ����� ��������� � ������������� ��������� �����(�), � ����� ������������� ��������� �������(�)
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// �������� ��������, ��� ������ �������� ���������, ����� glVertexAttribPointer() ��������������� VBO ��� ����������� ��������� �������� ������ ��� ���������� ��������, ��� ��� ����� ����� �� ����� �������� ��������� �������
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//////
	//////
	//////



	



	// ���� ����������
	while (!glfwWindowShouldClose(window))
	{
		// ��������� �����
		processInput(window);

		// ���������� ����������
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO); // ��������� � ��� ���� ������ ���� VAO, �� ��� ������������� ��������� ��� ������ ��� (�� �� ������� ���, ����� �� ���� ������� ��������������)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: ����� ���������� front- � back-�������. ������������ ������� �����/������ (���� �� ������/�������� ������, ��������� ������ ���� � �.�.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: ����������, ������������ ���� ����� ��������������� GLFW-��������
	glfwTerminate();
	return 0;



}

void Paint()
{
	
}
