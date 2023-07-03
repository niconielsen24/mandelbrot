#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

void shader_from_file(char * path, char * shader)
{
    FILE * file = fopen(path,"r");
    unsigned i = 0;

    while (fscanf(file,"%c",&shader[i]) != EOF)
    {
        i++;
    }
}

unsigned compile_shader(unsigned type,const char * source)
{
    unsigned id;
    id = glCreateShader(type);
    glShaderSource(id,1,&source,NULL);
    glCompileShader(id);
    return id;
}

unsigned create_shader(const char * vs_s,const char * fs_s)
{
    unsigned vs = compile_shader(GL_VERTEX_SHADER,vs_s);
    unsigned fs = compile_shader(GL_FRAGMENT_SHADER,fs_s);

    unsigned prog = glCreateProgram();
    glAttachShader(prog,vs);
    glAttachShader(prog,fs);
    glLinkProgram(prog);
    
    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

int main()
{
    glfwInit();
    int width = 1920,height = 1080;


    GLFWwindow * window = glfwCreateWindow(width,height,"Mandelbrot",NULL,NULL);
    glfwMakeContextCurrent(window);

    glewInit();

    char fragment_shader[1024];
    shader_from_file("shader/mandelbrot.glsl", fragment_shader);

    char* vertex_shader =
                        "#version 410\n"
                        "in vec3 vp;\n"
                        "void main () {\n"
                        "  gl_Position = vec4 (vp, 1.0);\n"
                        "}\n";

    float points[] = {
	   -1.0f,  1.0f,  0.0f,
	   -1.0f,  -1.0f,  0.0f,
	   1.0f,  -1.0f,  0.0f,

	   1.0f,  1.0f,  0.0f,
	};

    unsigned indices[] = {
        0,1,2,
        2,3,0
    };

    unsigned prog = create_shader(vertex_shader, fragment_shader);

    GLuint vbo = 0;
	glGenBuffers (1, &vbo);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glBufferData (GL_ARRAY_BUFFER, 12 * sizeof (float), points, GL_STATIC_DRAW);

    GLuint vao = 0;
	glGenVertexArrays (1, &vao);
	glBindVertexArray (vao);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    GLuint ibo = 0;
    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6*sizeof(unsigned),indices,GL_STATIC_DRAW);

    glUniform2i(glGetUniformLocation(prog, "res"),width,height);

    while (!glfwWindowShouldClose(window))
    {
        glUseProgram(prog);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glDeleteProgram(prog);

    return 0;
}
