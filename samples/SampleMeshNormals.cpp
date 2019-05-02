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

arepa::Program::Ptr program;
arepa::IndexBuffer::Ptr ibo;
arepa::VertexBuffer::Ptr pos_vbo;
arepa::VertexBuffer::Ptr nor_vbo;
arepa::Meshf::Ptr mesh;

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const arepa::Attribute pos_attr("in_pos", arepa::Attribute::Type::Float, 3,
                                    sizeof(float) * 3, 0);
    const arepa::Attribute nor_attr("in_nor", arepa::Attribute::Type::Float, 3,
                                    sizeof(float) * 3, 0);

    program->bind();
    program->set_attribute(pos_attr, pos_vbo);
    program->set_attribute(nor_attr, nor_vbo);

    float view_matrix[16], projection_matrix[16];
    arepa::Transformation::view(arepa::Vec3f(0.0f, 0.15f, 1.0f),
                                arepa::Vec3f(0.0f, 0.15f, 0.0f),
                                arepa::Vec3f(0.0f, 1.0f, 0.0f), view_matrix);
    arepa::Transformation::orthographic(
        arepa::Vec2f(-0.12f, 0.12f), arepa::Vec2f(-0.12f, 0.12f),
        arepa::Vec2f(0.0f, 2.0f), projection_matrix);

    program->set_uniform_matrix_4f("u_vmatrix", view_matrix);
    program->set_uniform_matrix_4f("u_pmatrix", projection_matrix);

    glEnable(GL_DEPTH_TEST);

    program->draw(arepa::Program::Mode::Triangles, ibo);
    program->unbind();

    glDisable(GL_DEPTH_TEST);

    glutSwapBuffers();
}

void init_shaders() {
    std::string vs_src =
        arepa::FileReader::read_text_file("../shaders/normals_vs.glsl");
    std::string fs_src =
        arepa::FileReader::read_text_file("../shaders/color_fs.glsl");

    arepa::Shader::Ptr vs =
        arepa::ShaderFactory::create<arepa::VertexShader>(vs_src);
    arepa::Shader::Ptr fs =
        arepa::ShaderFactory::create<arepa::FragmentShader>(fs_src);

    AREPA_ASSERT(vs->is_valid());
    AREPA_ASSERT(fs->is_valid());

    program = arepa::Program::create({vs, fs});

    AREPA_ASSERT(program->is_valid());
}

void init_buffers() {
    arepa::BufferBuilder buffer_builder{mesh};

    ibo = buffer_builder.build_index_buffer();
    pos_vbo = buffer_builder.build_position_buffer();
    nor_vbo = buffer_builder.build_normal_buffer();
}

void init_mesh() {
    mesh = arepa::OBJMeshLoader("../assets/happy_buddha.obj").load();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 100);
    glutCreateWindow("Visualize Normals");

    glewInit();

    glutDisplayFunc(display);

    init_shaders();
    init_mesh();
    init_buffers();

    glutMainLoop();
}
