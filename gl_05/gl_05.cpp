#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const GLuint WIDTH = 800, HEIGHT = 600;

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
    cout << key << endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname) {
    int width, height;
    unsigned char* image =
        SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
    if (image == nullptr) throw exception("Failed to load texture file");

    GLuint texture;
    glGenTextures(1, &texture);

    glActiveTexture(texId);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    return texture;
}

ostream& operator<<(ostream& os, const glm::mat4& mx) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) cout << mx[row][col] << ' ';
        cout << endl;
    }
    return os;
}

int main() {
    if (glfwInit() != GL_TRUE) {
        cout << "GLFW initialization failed" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    try {
        GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05",
                                              nullptr, nullptr);
        if (window == nullptr) throw exception("GLFW window not created");
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, key_callback);

        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
            throw exception("GLEW Initialization failed");

        glViewport(0, 0, WIDTH, HEIGHT);
        glEnable(GL_DEPTH_TEST);

        // Let's check what are maximum parameters counts
        GLint nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
        glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
        cout << "Max texture coords allowed: " << nrAttributes << std::endl;

        // Build, compile and link shader program
        ShaderProgram theProgram("gl_05.vert", "gl_05.frag");

        /* clang-format off */
		// Set up vertex data
		GLfloat vertices[] = {
            // coordinates			// color			// texture
			0.25f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//0
			-0.75f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//1
			-0.25f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//2
			0.75f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//3
			-0.25f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//4
			-0.75f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//5
			0.25f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//6
			0.75f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//7
			-0.25f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//8
			-0.25f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,	//9
			0.75f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f,	//10
			0.75f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//11
			-0.75f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,	//12
			-0.75f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//13
			0.25f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f,	//14
			0.25f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,	//15
			-0.25f, -0.5f,  -0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//16
			-0.75f,  0.5f,  -0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  1.0f,	//17
			-0.25f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//18
			-0.75f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f,  1.0f,	//19
			0.75f, -0.5f,  -0.5f,	1.0f, 0.0f, 1.0f,	1.0f,  0.0f,	//20
			0.75f, -0.5f,  0.5f,	1.0f, 0.0f, 1.0f,	0.0f,  0.0f,	//21
			0.25f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f,  1.0f,	//22
			0.25f,  0.5f,  -0.5f,	1.0f, 0.0f, 0.0f,	1.0f,  1.0f		//23
		};

		GLuint indices[] = {
            0, 1, 2,
			0, 2, 3,
			4, 5, 6,
			4, 6, 7,
			8, 9, 10,
			8, 10, 11,
			12, 13, 14,
			12, 14, 15,
			16, 17, 18,
			18, 17, 19,
			20, 21, 22,
			20, 22, 23
		};
        /* clang-format on */

        GLuint VBO, EBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // Bind the Vertex Array Object first, then bind and set vertex
        // buffer(s) and attribute pointer(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                     GL_STATIC_DRAW);

        // vertex geometry data
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                              (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // vertex color data
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                              (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        // vertex texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat),
                              (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindBuffer(
            GL_ARRAY_BUFFER,
            0);  // Note that this is allowed, the call to glVertexAttribPointer
                 // registered VBO as the currently bound vertex buffer object
                 // so afterwards we can safely unbind

        glBindVertexArray(0);  // Unbind VAO (it's always a good thing to unbind
                               // any buffer/array to prevent strange bugs)

        // Set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT);  // Set texture wrapping to GL_REPEAT
                                     // (usually basic wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // Set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // prepare textures
        GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "iipw.png");
        GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "weiti.png");

        // main event loop
        while (!glfwWindowShouldClose(window)) {
            // Check if any events have been activated (key pressed, mouse
            // moved etc.) and call corresponding response functions
            glfwPollEvents();

            // Clear the colorbuffer
            glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Bind Textures using texture units
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture0);
            glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture1"), 1);

            // Transformations
            glm::mat4 trans;
            static GLfloat rot_angle = 0.0f;
            trans = glm::rotate(trans, -glm::radians(rot_angle), glm::vec3(1.0, 0.0, 0.0));
            rot_angle += 2.0f;
            if (rot_angle >= 360.0f) rot_angle -= 360.0f;
            GLuint transformLoc = glGetUniformLocation(theProgram.get_programID(), "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

            glm::mat4 camRot;
            camRot = glm::rotate(camRot, glm::radians(rot_angle), glm::vec3(0.0, 1.0, 0.0));
            glm::vec3 camPos = glm::vec3(camRot * glm::vec4(0.0f, 0.0f, -3.0f, 1.0f));

            glm::mat4 view;
            view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            GLuint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
            GLuint projectionLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            // Draw our first triangle
            theProgram.Use();

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, _countof(indices), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            // Swap the screen buffers
            glfwSwapBuffers(window);
        }
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    } catch (exception ex) {
        cout << ex.what() << endl;
    }
    glfwTerminate();

    return 0;
}
