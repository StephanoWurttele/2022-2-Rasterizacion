#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include <learnopengl/filesystem.h>
#include "../LearnOpenGL/shader_m.h"
#include "../LearnOpenGL/camera.h"

#include <iostream>
#include "Universo.h"
#include <stdlib.h>
#include <time.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// pyramid models
int npiramides = 10;
std::vector<glm::mat4> models(npiramides);

// spheres
int nesferas = 1;
std::vector<glm::mat4> sphereModels(nesferas);
Esfera esfera(vec3(0),2., 100, 100);
Universo universo;
Shader *lightingShader;
Shader *lightCubeShader;

void drawPyramid(Shader &lightingShader, unsigned int pyramidVAO, glm::mat4& model){
    lightingShader.setMat4("model", model);

    // render the cube
    glBindVertexArray(pyramidVAO);
    glDrawArrays(GL_TRIANGLES, 0, 12);
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------


    lightingShader = new Shader ("../2.2.basic_lighting.vs", "../2.2.basic_lighting.fs");
    lightCubeShader = new Shader ("../2.2.light_cube.vs", "../2.2.light_cube.fs");
    // set up esfera texture and coordinates and indexes
    esfera.vao = esfera.setup();

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

            0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f,
            1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f,
            0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.5f,

            0.5f, 0.5f, 1.0f, 1.0f, 0.5f, 0.25f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.25f,
            0.5f,  1.0f, 0.0f, 1.0f, 0.5f, 0.25f,

            0.0f, 0.0f, 0.0f, -1.0f, 0.5f, 0.25f,
            0.5f,  1.0f, 0.0f, -1.0f, 0.5f, 0.25f,
            0.5f, 0.5f, 1.0f, -1.0f, 0.5f, 0.25f,
    };
    // first, configure the cube's VAO (Vertex Array Object) (and VBO - Vertex Buffer Object)
    unsigned int VBO, pyramidVAO;
    glGenVertexArrays(1, &pyramidVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(pyramidVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which
    // is also a 3D cube)
    unsigned int lightPyramidVAO;
    glGenVertexArrays(1, &lightPyramidVAO);
    glBindVertexArray(lightPyramidVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // render loop
    // -----------
    srand(0);

    for(int i = 0; i < npiramides; ++i){
        models[i] = glm::mat4(1.0f);
        models[i] = glm::translate(models[i], glm::vec3(rand()%10, rand()%10, rand()%10));
    }

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects

        lightingShader->use();
        lightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader->setVec3("lightPos", lightPos);
        lightingShader->setVec3("viewPos", camera.Position);

        // render spheres
        universo.processUniverse();
        universo.displayUniverse();


        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader->setMat4("projection", projection);
        lightingShader->setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader->setMat4("model", model);

        // render the cube
        glBindVertexArray(pyramidVAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);

        for(int i = 0; i < npiramides; i++) {
            drawPyramid(*lightingShader, pyramidVAO, models[i]);
        }


        // also draw the lamp object
        lightCubeShader->use();
        lightCubeShader->setMat4("projection", projection);
        lightCubeShader->setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader->setMat4("model", model);

        glBindVertexArray(lightPyramidVAO);
        glDrawArrays(GL_TRIANGLES, 0, 12);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

     // optional: de-allocate all resources once they've outlived their purpose:
     // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &pyramidVAO);
    glDeleteVertexArrays(1, &lightPyramidVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        npiramides += 1;
        models.push_back(glm::mat4(1.0f));
        models[npiramides-1]=glm::translate(models[npiramides-1], glm::vec3(rand()%10, rand()%10, rand()%10));
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        universo.nuevaEntidad(&esfera, lightingShader);
}