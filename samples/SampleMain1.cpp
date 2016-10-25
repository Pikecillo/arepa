#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <arepa/Buffer.h>
#include <arepa/BufferBuilder.h>
#include <arepa/FileReader.h>
#include <arepa/Mesh.h>
#include <arepa/MeshLoader.h>
#include <arepa/Program.h>
#include <arepa/ShaderFactory.h>
#include <arepa/Timer.h>
#include <arepa/Transformation.h>

Program::Ptr program;
IndexBuffer::Ptr ibo;
VertexBuffer::Ptr pos_vbo;
VertexBuffer::Ptr nor_vbo;
Mesh::Ptr mesh;

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Attribute pos_attr("in_pos", Attribute::Type::Float, 3,
			     sizeof(float) * 3, 0);
    const Attribute nor_attr("in_nor", Attribute::Type::Float, 3,
			     sizeof(float) * 3, 0);

    program->bind();
    program->set_attribute(pos_attr, pos_vbo);
    program->set_attribute(nor_attr, nor_vbo);

    float view_matrix[16], projection_matrix[16];
    Transformation::view(Vec3f(0.0f, 0.15f, 1.0f),
			 Vec3f(0.0f, 0.15f, 0.0f),
			 Vec3f(0.0f, 1.0f, 0.0f),
			 view_matrix);
    Transformation::orthographic(Vec2f(-0.12f, 0.12f),
				 Vec2f(-0.12f, 0.12f),
				 Vec2f( 0.0f, 2.0f),
				 projection_matrix);

    program->set_uniform_matrix_4f("u_vmatrix", view_matrix);
    program->set_uniform_matrix_4f("u_pmatrix", projection_matrix);

    glEnable(GL_DEPTH_TEST);

    program->draw(Program::Mode::Triangles, ibo);
    program->unbind();

    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void init_shaders() {
    std::string vs_src = FileReader::read_text_file("../shaders/vs.glsl");
    std::string fs_src = FileReader::read_text_file("../shaders/fs.glsl");

    Shader::Ptr vs = ShaderFactory::create<VertexShader>(vs_src);
    Shader::Ptr fs = ShaderFactory::create<FragmentShader>(fs_src);

    assert(vs->is_valid());
    assert(fs->is_valid());

    program = Program::create({vs, fs});

    assert(program->is_valid());
}

void init_buffers() {
    BufferBuilder buffer_builder{mesh};

    ibo = buffer_builder.build_index_buffer();
    pos_vbo = buffer_builder.build_position_buffer();
    nor_vbo = buffer_builder.build_normal_buffer();
}

void init_mesh() {
    mesh = OBJMeshLoader("../assets/happy_buddha.obj").load();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 100);
    glutCreateWindow("My Shading System");
    
    glewInit();
    
    glutDisplayFunc(display);

    init_shaders();
    init_mesh();
    init_buffers();

    glutMainLoop();
}
