#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//// Other Libs
//#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
bool anim;//puerta der Buro
bool anim2;//puerta izq Buro
bool anim3;//puerta Casa
bool anim4;//prender lampara
bool anim5;//puerta estufa
bool anim6;//prender arribarefri
bool anim7;//puerta abajo  refri
float rot = 0.0f;//puerta der Buro
float rot2 = 0.0f;//puerta izq Buro
float rot3 = 0.0f;//puerta
float rot4 = 0.0f;//colaPajaro
float rot5 = 0.0f;//puertaEstufa
float rot6 = 0.0f;//puerta arriba refri
float rot7 = 0.0f;//puerta abajo refri
glm::vec3 PosIni(-5.67f, 1.8f, -4.0f); //posicion inicial animacion buro2
glm::vec3 PosIni2(5.0f, 16.5f, -6.4f); //posicion inicial animacion pajaro
glm::vec3 PosIni3(15.0f, 0.0f, 12.0f); //posicion inicial pollo


//Animación del buro
float movKitX = 0.0;
float movKitZ = 0.0;
bool recorrido = false;
bool recorrido1 = true;
bool recorrido2 = false;

//Animación del pajaro
float movKitX2 = 0.0;
float movKitY2 = 0.0;
float movKitZ2 = 0.0;
float rotKit2 = 0.0;
bool recorrido3 = false;
bool recorrido4 = true;
bool recorrido5 = false;
bool recorrido6 = false;
bool recorrido7 = false;
bool recorrido8 = false;

//Animación del pollo
float rotKit3 = 0.0;
float movKitX3 = 0.0;
float movKitY3 = 0.0;
float movKitZ3 = 0.0;
bool recorrido9 = false;
bool recorrido10 = true;
bool recorrido11 = false;
bool recorrido12 = false;
bool recorrido13 = false;
bool recorrido14 = false;
bool recorrido15 = false;
bool recorrido16 = false;
bool recorrido17 = false;
bool recorrido18 = false;


// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);


// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,8.0f, 0.0f)/*,
	glm::vec3(0.0f,9.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(10.0f,0.0f, 0.0f)*/
};
glm::vec3 LightP1;
//glm::vec3 Light1 = glm::vec3(0);
//glm::vec3 Light2 = glm::vec3(0);
//glm::vec3 Light3 = glm::vec3(0);
//glm::vec3 Light4 = glm::vec3(0);

glm::vec3 spotLightPositions[] = { //colocacion del cubo
	glm::vec3(0.4f,7.0f, -6.3f),
};
glm::vec3 spotLightDir[] = {
	glm::vec3(0.0f, 0.0f, 0.0f), //a donde apunta la luz de la lampara
};


//glm::vec3 spotLightPositions2[] = { //colocacion del cubo
//	glm::vec3(0.4f,7.0f, -6.3f),
//	glm::vec3(0.4f,7.0f, -6.3f),
//	glm::vec3(0.4f,7.0f, -6.3f),
//	glm::vec3(0.4f,7.0f, -6.3f),
//};
//glm::vec3 spotLightDir2[] = {
//	glm::vec3(0.0f, 0.0f, 0.0f), //a donde apunta la luz de la lampara
//	glm::vec3(0.4f,7.0f, -6.3f),
//	glm::vec3(0.4f,7.0f, -6.3f),
//	glm::vec3(0.4f,7.0f, -6.3f),
//};

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	
	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "316156235_PROYECTO_GPO04", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");


	//BURO
	Model cuerpoBuro((char*)"Models/Buro/cuerpoBuro.obj");
	Model puertaDerBuro((char*)"Models/Buro/puertaDerBuro.obj");
	Model puertaIzqBuro((char*)"Models/Buro/puertaIzqBuro.obj");

	//BURO2
	Model cuerpoBuro2((char*)"Models/Buro2/cuerpoBuro2.obj");
	Model cajon((char*)"Models/Buro2/cajon.obj");

	//CASA
	Model casa((char*)"Models/Casa/casaCompleta.obj");
	Model puerta((char*)"Models/Casa/puerta.obj");
	Model vidrio((char*)"Models/Casa/vidrio.obj");

	//LAMPARA
	Model lampara((char*)"Models/Lampara/lampara.obj");
	Model foco((char*)"Models/Lampara/foco.obj");

	//MESA
	Model mesa((char*)"Models/Mesa/Mesa.obj");

	//PERCHERO
	Model perchero((char*)"Models/Perchero/percheroMaya.obj");

	//SILLAS
	Model silla((char*)"Models/Silla/silla.obj");
	Model silla2((char*)"Models/Silla/silla2.obj");

	//SILLON
	Model sillon((char*)"Models/Sillon/sillon.obj");
	
	//PAJARO
	Model cuerpoPajaro((char*)"Models/Pajarito/cuerpo.obj");
	Model colaPjaro((char*)"Models/Pajarito/cola.obj");
	
	//ARBOL
	Model arbol((char*)"Models/Arbol/arbol.obj");
	
	//GALLINA
	Model gallina((char*)"Models/Gallina/gallina.obj");
	//POLLO
	Model pollo((char*)"Models/Gallina/pollo.obj");

	//ALACENAS
	Model alacenaDer((char*)"Models/Alacena/alacenaDer.obj");
	Model alacenaIzq((char*)"Models/Alacena/alacenaIZq.obj");

	//BANCOTALLER
	Model bancoTaller((char*)"Models/BancoTaller/bancoSilla.obj");

	//FREGADERO
	Model fregadero((char*)"Models/Fregadero/fregadero.obj");

	//ESTUFA
	Model cuerpoEstufa((char*)"Models/Estufa/cuerpoEstufa.obj");
	Model vidrioEstufa((char*)"Models/Estufa/vidrioEstufa.obj");
	Model puertaEstufa((char*)"Models/Estufa/puertaEstufa.obj");

	//REFRIGERADOR
	Model cuerpoRefri((char*)"Models/Refrigerador/cuerpoRefri.obj");
	Model puertaRefriArriba((char*)"Models/Refrigerador/puertaRefriArriba.obj");
	Model puertaRefriAbajo((char*)"Models/Refrigerador/puertaRefriAbajo.obj");

	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};


	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};


	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
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


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	//SkyBox
	GLuint skyboxVBO, skyboxVAO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);
	
	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		animacion();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.4f, 0.4f, 0.4f);

		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"),0.032f);

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.1f, 0.1f, 0.1f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), spotLightPositions[0].x, spotLightPositions[0].y, spotLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), spotLightDir[0].x, spotLightDir[0].y, spotLightDir[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f,1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.22f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(20.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(35.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 20.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glm::mat4 tmp = glm::mat4(1.0f); //Temp

		glm::mat4 model(1);
		view = camera.GetViewMatrix();

		//Carga de modelo 

		//BURO
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(4.1f, 1.3f, -10.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoBuro.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.26f, 1.3f, -9.82f));
		model = glm::rotate(model, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaDerBuro.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(5.91f, 1.3f, -9.82f));
		model = glm::rotate(model, glm::radians(rot2), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaIzqBuro.Draw(lightingShader);

		//BURO2
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-5.67f, 1.8f, -4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoBuro2.Draw(lightingShader);
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, PosIni + glm::vec3(movKitX, 0, movKitZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cajon.Draw(lightingShader);

		//CASA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		casa.Draw(lightingShader);
		//PUERTA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(6.6f, 3.68f, 2.0f));
		model = glm::rotate(model, glm::radians(rot3), glm::vec3(0.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puerta.Draw(lightingShader);
		//VIDRIO
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.85);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		vidrio.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glBindVertexArray(0);
	

		//LAMPARA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lampara.Draw(lightingShader);
		//FOCO
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.75);
		foco.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glBindVertexArray(0);

		//MESA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mesa.Draw(lightingShader);

		//PERCHERO
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		perchero.Draw(lightingShader);

		//SILLA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-3.3f, 2.0f, -6.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		silla.Draw(lightingShader);

		//SILLA2
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(3.5f, 2.0f, -6.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		silla2.Draw(lightingShader);

		//SILLON
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sillon.Draw(lightingShader);

		//PAJARO
		model = glm::mat4(1);
		//model = glm::translate(model, glm::vec3(5.0f, 16.5f, -6.4f));
		model = glm::translate(model, PosIni2 + glm::vec3(movKitX2, movKitY2, movKitZ2));
		model = glm::rotate(model, glm::radians(rotKit2), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoPajaro.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, PosIni2 + glm::vec3(movKitX2, movKitY2, movKitZ2));
		model = glm::rotate(model, glm::radians(rotKit2), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::translate(model, glm::vec3(-0.5f, -0.6f, -0.04f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
		model = glm::rotate(model, glm::radians(rot4), glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(5.0f, 15.9f, -6.95f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		colaPjaro.Draw(lightingShader);

		//ARBOL
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.0f, 0.0f, 17.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbol.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(13.0f, 0.0f, -17.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbol.Draw(lightingShader);

	    //POLLO
		model = glm::mat4(1);
		model = glm::translate(model, PosIni3 + glm::vec3(movKitX3, 0, movKitZ3));
		model = glm::rotate(model, glm::radians(rotKit3), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pollo.Draw(lightingShader);

		//ALACENA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		alacenaDer.Draw(lightingShader);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		alacenaIzq.Draw(lightingShader);

		//BANCOTALLER
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		bancoTaller.Draw(lightingShader);

		//FREGADERO
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		fregadero.Draw(lightingShader);

		//CUERPOESTUFA
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoEstufa.Draw(lightingShader);
		//VIDRIOESTUFA
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "activaTransparencia"), 0);
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 0.85);
		model = glm::rotate(model, glm::radians(rot4), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		vidrioEstufa.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlpha"), 1.0, 1.0, 1.0, 1.0);
		glBindVertexArray(0);
		//PUERTAESTUFA
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-9.649f, 0.825f, -8.71f));
		model = glm::rotate(model, glm::radians(rot4), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaEstufa.Draw(lightingShader);

		//REFRI
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		cuerpoRefri.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-11.1f, 2.2f, -0.12f));
		model = glm::rotate(model, glm::radians(rot6), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaRefriAbajo.Draw(lightingShader);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-11.1f, 5.5f, -0.12f));
		model = glm::rotate(model, glm::radians(rot7), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		puertaRefriArriba.Draw(lightingShader);

		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices (para hacer los cubos)
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		//for (GLuint i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1);
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		//glBindVertexArray(0);


		//spothlight
		//for (GLuint i = 0; i < 4; i++)
		//{
		//	model = glm::mat4(1);
		//	model = glm::translate(model, spotLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.16f)); // Make it a smaller cube
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glBindVertexArray(VAO);
		//	glDrawArrays(GL_TRIANGLES, 0, 36);
		//}
		//glBindVertexArray(0);


		// Draw skybox as last
		glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
		SkyBoxshader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Set depth function back to default

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	//if (keys[GLFW_KEY_T])
	//{
	//	pointLightPositions[0].x += 0.01f;
	//	pointLightPositions[1].x += 0.01f;
	//	pointLightPositions[2].x += 0.01f;
	//	pointLightPositions[3].x += 0.01f;
	//}
	//if (keys[GLFW_KEY_G])
	//{
	//	pointLightPositions[0].x -= 0.01f;
	//	pointLightPositions[1].x -= 0.01f;
	//	pointLightPositions[2].x -= 0.01f;
	//	pointLightPositions[3].x -= 0.01f;
	//}

	//if (keys[GLFW_KEY_Y])
	//{
	//	pointLightPositions[0].y += 0.01f;
	//	pointLightPositions[1].y += 0.01f;
	//	pointLightPositions[2].y += 0.01f;
	//	pointLightPositions[3].y += 0.01f;
	//}

	//if (keys[GLFW_KEY_H])
	//{
	//	pointLightPositions[0].y -= 0.01f;
	//	pointLightPositions[1].y -= 0.01f;
	//	pointLightPositions[2].y -= 0.01f;
	//	pointLightPositions[3].y -= 0.01f;
	//}
	//if (keys[GLFW_KEY_U])
	//{
	//	pointLightPositions[0].z += 0.01f;
	//	pointLightPositions[1].z += 0.01f;
	//	pointLightPositions[2].z += 0.01f;
	//	pointLightPositions[3].z += 0.01f;
	//}
	//if (keys[GLFW_KEY_J])
	//{
	//	pointLightPositions[0].z -= 0.01f;
	//	pointLightPositions[1].z -= 0.01f;
	//	pointLightPositions[2].z -= 0.01f;
	//	pointLightPositions[3].z -= 0.01f;
	//}

	////POSICION
	//if (keys[GLFW_KEY_O])
	//{
	//	spotLightPositions[0].x += 0.01f;
	//}
	//if (keys[GLFW_KEY_L])
	//{
	//	spotLightPositions[0].x -= 0.01f;
	//}

	//if (keys[GLFW_KEY_I])
	//{
	//	spotLightPositions[0].y += 0.01f;
	//}

	//if (keys[GLFW_KEY_K])
	//{
	//	spotLightPositions[0].y -= 0.01f;
	//}
	//if (keys[GLFW_KEY_N])
	//{
	//	spotLightPositions[0].z += 0.01f;
	//}
	//if (keys[GLFW_KEY_M])
	//{
	//	spotLightPositions[0].z -= 0.01f;
	//}

	////DIRECCION
	//if (keys[GLFW_KEY_1])
	//{
	//	spotLightDir[0].x += 0.01f;
	//}
	//if (keys[GLFW_KEY_2])
	//{
	//	spotLightDir[0].x -= 0.01f;
	//}

	//if (keys[GLFW_KEY_3])
	//{
	//	spotLightDir[0].y += 0.01f;
	//}

	//if (keys[GLFW_KEY_4])
	//{
	//	spotLightDir[0].y -= 0.01f;
	//}
	//if (keys[GLFW_KEY_5])
	//{
	//	spotLightDir[0].z += 0.01f;
	//}
	//if (keys[GLFW_KEY_6])
	//{
	//	spotLightDir[0].z -= 0.01f;
	//}
    
	if (keys[GLFW_KEY_U])// abrir cajon
	{
		recorrido = true;
	}

	if (keys[GLFW_KEY_I])//detener cajon
	{
		recorrido = false;
	}

	if (keys[GLFW_KEY_O])// volar Pajaro
	{
		recorrido3 = true;
	}

	if (keys[GLFW_KEY_P])//detener pajaro
	{
		recorrido3 = false;
	}

	if (keys[GLFW_KEY_F])// caminar pollo
	{
		recorrido9 = true;
	}

	if (keys[GLFW_KEY_G])//detener pollo
	{
		recorrido9 = false;
	}



}

void animacion()
{
	//Movimiento cajon
	if (recorrido)
	{
		if (recorrido1)
		{
			movKitX += 0.001f;
			if (movKitX > 0.9)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		if (recorrido2)
		{
			movKitX -= 0.001f;
			if (movKitX < 0.0)
			{
				recorrido2 = false;
				recorrido1 = true;
			}
		}
	}

	//Movimiento pajaro
	if (recorrido3)
	{
		if (recorrido4)
		{
			movKitX2 += 0.05f;
			if (movKitX2 > 10.0)
			{
				recorrido4 = false;
				recorrido5 = true;
			}
		}
		if (recorrido5)
		{
			rotKit2 = 270;
			movKitZ2 += 0.08f;
			movKitY2 -= 0.08f;
			if (movKitZ2 > 10.0)
			{
				recorrido5 = false;
				recorrido6 = true;
			}
		}
		if (recorrido6)
		{
			movKitZ2 += 0.08f;
			movKitY2 += 0.08f;
			if (movKitZ2 > 20.0)
			{
				recorrido6 = false;
				recorrido7 = true;
			}
		}
		if (recorrido7)
		{
			rotKit2 = 135;
			movKitZ2 -= 0.08f;
			movKitY2 += 0.0006f;
			movKitX2 -= 0.04f;
			if (movKitZ2 < 0.0)
			{
				recorrido7 = false;
				recorrido8 = true;
			}
		}
		if (recorrido8)
		{
			rotKit2 = 0;
			{
				recorrido8 = false;
				recorrido4 = true;
			}
		}
	}

	//Movimiento POLLO
	if (recorrido9)
	{
		if (recorrido10)
		{
			movKitZ3 -= 0.02f;
			if (movKitZ3 < -5.0)
			{
				recorrido10 = false;
				recorrido11 = true;
			}
		}if (recorrido11)
		{
			rotKit3 = -45;
			movKitZ3 -= 0.02f;
			movKitX3 += 0.03f;
			if (movKitZ3 < -10.0)
			{
				recorrido11 = false;
				recorrido12 = true;
			}
		}
		if (recorrido12)
		{
			rotKit3 =45;
			movKitZ3 -= 0.02f;
			movKitX3 -= 0.03f;
			if (movKitZ3 < -15.0)
			{
				recorrido12 = false;
				recorrido13 = true;
			}
		}
		if (recorrido13)
		{
			rotKit3 = -45;
			movKitZ3 -= 0.02f;
			movKitX3 += 0.03f;
			if (movKitZ3 < -20.0)
			{
				recorrido13 = false;
				recorrido14 = true;
			}
		}
		if (recorrido14)
		{
			rotKit3 = 45;
			movKitZ3 -= 0.02f;
			movKitX3 -= 0.03f;
			if (movKitZ3 < -25.0)
			{
				recorrido14 = false;
				recorrido15 = true;
			}
		}

		if (recorrido15)
		{
			rotKit3 = 0;
			rotKit3 = 180;
			movKitZ3 += 0.03f;
			if (movKitZ3 > 0)
			{
				recorrido15 = false;
				recorrido16 = true;
			}
		}
		if (recorrido16)
		{
			rotKit3 = 0;
			{
				recorrido16 = false;
				recorrido10 = true;
			}
		}
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	if (keys[GLFW_KEY_E]) //animacion puerta buro
	{
		anim = !anim;
		if (anim)
		{
			rot = -90.0f;
		}
		else
		{
			rot = 0.0f;
		}
	}
	if (keys[GLFW_KEY_R]) //animacion puerta buro
	{
		anim2 = !anim2;
		if (anim2)
		{
			rot2 = -90.0f;
		}
		else
		{
			rot2 = 0.0f;
		}
	}
	if (keys[GLFW_KEY_T]) //animacion puerta casa
	{
		anim3 = !anim3;
		if (anim3)
		{
			rot3 = 90.0f;

		}
		else
		{
			rot3 = 0.0f;
		}
	}

	if (keys[GLFW_KEY_Y])
	{
		anim4 = !anim4;
		if (anim4)
		{
			spotLightDir[0].y = (-1.0f, -5.0f, -1.0f); //prender luz lampara
		}
		else
		{
			spotLightDir[0].y = (0.0f, 0.0f, 0.0f); //apagar luz lampara
		}
	}

	if (keys[GLFW_KEY_H]) //animacion puerta estufa
	{
		anim5 = !anim5;
		if (anim5)
		{
			rot4 = 90.0f;

		}
		else
		{
			rot4 = 0.0f;
		}
	}

	if (keys[GLFW_KEY_J]) //animacion puerta refri arriba
	{
		anim6 = !anim6;
		if (anim6)
		{
			rot6 = -90.0f;
		}
		else
		{
			rot6 = 0.0f;
		}
	}
	if (keys[GLFW_KEY_K]) //animacion puerta refri arbajo
	{
		anim7 = !anim7;
		if (anim7)
		{
			rot7 = -90.0f;
		}
		else
		{
			rot7 = 0.0f;
		}
	}
}


void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}


