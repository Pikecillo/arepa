#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <arepa/Buffer.h>
#include <arepa/BufferBuilder.h>
#include <arepa/FileReader.h>
#include <arepa/Framebuffer.h>
#include <arepa/Mesh.h>
#include <arepa/MeshLoader.h>
#include <arepa/Program.h>
#include <arepa/ShaderFactory.h>
#include <arepa/Texture.h>
#include <arepa/Timer.h>
#include <arepa/Transformation.h>

arepa::Program::Ptr offscreen_program;
arepa::IndexBuffer::Ptr offscreen_ibo;
arepa::VertexBuffer::Ptr offscreen_pos_vbo;
arepa::VertexBuffer::Ptr offscreen_nor_vbo;
arepa::Texture::Ptr color_texture, depth_texture, pos_texture, nor_texture;
arepa::Framebuffer::Ptr fbo;

arepa::Program::Ptr onscreen_program;
arepa::IndexBuffer::Ptr onscreen_ibo;
arepa::VertexBuffer::Ptr onscreen_pos_vbo;
arepa::VertexBuffer::Ptr onscreen_tex_vbo;

arepa::Meshf::Ptr mesh;

void draw_offscreen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const arepa::Attribute pos_attr("in_pos", arepa::Attribute::Type::Float, 3,
                                    sizeof(float) * 3, 0);
    const arepa::Attribute nor_attr("in_nor", arepa::Attribute::Type::Float, 3,
                                    sizeof(float) * 3, 0);

    offscreen_program->bind();
    offscreen_program->set_attribute(pos_attr, offscreen_pos_vbo);
    offscreen_program->set_attribute(nor_attr, offscreen_nor_vbo);

    const float albedo[] = {1.0f, 1.0f, 1.0f};
    float view_matrix[16], projection_matrix[16];
    arepa::Transformation::view(arepa::Vec3f(0.0f, 0.15f, 1.0f),
                                arepa::Vec3f(0.0f, 0.15f, 0.0f),
                                arepa::Vec3f(0.0f, 1.0f, 0.0f), view_matrix);
    arepa::Transformation::orthographic(
        arepa::Vec2f(-0.12f, 0.12f), arepa::Vec2f(-0.12f, 0.12f),
        arepa::Vec2f(0.0f, 2.0f), projection_matrix);

    offscreen_program->set_uniform_matrix_4f("u_vmatrix", view_matrix);
    offscreen_program->set_uniform_matrix_4f("u_pmatrix", projection_matrix);
    offscreen_program->set_uniform_3f("u_albedo", albedo);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 512, 512);

    fbo->bind();

    offscreen_program->draw(arepa::Program::Mode::Triangles, offscreen_ibo);
    offscreen_program->unbind();

    fbo->unbind();

    glDisable(GL_DEPTH_TEST);
}

void draw_onscreen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const arepa::Attribute pos_attr("in_pos", arepa::Attribute::Type::Float, 3,
                                    sizeof(float) * 3, 0);
    const arepa::Attribute tex_attr("in_tex", arepa::Attribute::Type::Float, 2,
                                    sizeof(float) * 2, 0);

    onscreen_program->bind();
    onscreen_program->set_attribute(pos_attr, onscreen_pos_vbo);
    onscreen_program->set_attribute(tex_attr, onscreen_tex_vbo);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, color_texture->handle());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, nor_texture->handle());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, pos_texture->handle());

    const float light[] = {0.5f, 0.5f, 0.5f};
    onscreen_program->set_uniform_3f("u_light", light);
    onscreen_program->set_uniform_1i("u_albedo_texture", 0);
    onscreen_program->set_uniform_1i("u_nor_texture", 1);
    onscreen_program->set_uniform_1i("u_pos_texture", 2);

    onscreen_program->draw(arepa::Program::Mode::Triangles, onscreen_ibo);
    onscreen_program->unbind();
}

void display() {
    draw_offscreen();
    draw_onscreen();

    glutSwapBuffers();
}

void init_framebuffer() {
    depth_texture = arepa::Texture::create();
    depth_texture->init(512, 512, arepa::Texture::InternalFormat::Depth,
                        arepa::Texture::Format::Depth,
                        arepa::Texture::Type::Float);

    color_texture = arepa::Texture::create();
    color_texture->init(512, 512, arepa::Texture::InternalFormat::RGBA,
                        arepa::Texture::Format::RGBA,
                        arepa::Texture::Type::UByte);

    pos_texture = arepa::Texture::create();
    pos_texture->init(512, 512, arepa::Texture::InternalFormat::RGB16F,
                      arepa::Texture::Format::RGB, arepa::Texture::Type::Float);

    nor_texture = arepa::Texture::create();
    nor_texture->init(512, 512, arepa::Texture::InternalFormat::RGB16F,
                      arepa::Texture::Format::RGB, arepa::Texture::Type::Float);

    fbo = arepa::Framebuffer::create();
    fbo->attach_color(color_texture, 0);
    fbo->attach_color(pos_texture, 1);
    fbo->attach_color(nor_texture, 2);
    fbo->attach_depth(depth_texture);

    fbo->bind();
    GLuint attachments[3] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                             GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, attachments);

    AREPA_ASSERT(fbo->is_valid());
}

void init_shaders() {
    std::string vs_src =
        arepa::FileReader::read_text_file("../shaders/gbuffer_vs.glsl");
    std::string fs_src =
        arepa::FileReader::read_text_file("../shaders/gbuffer_fs.glsl");

    arepa::Shader::Ptr vs =
        arepa::ShaderFactory::create<arepa::VertexShader>(vs_src);
    arepa::Shader::Ptr fs =
        arepa::ShaderFactory::create<arepa::FragmentShader>(fs_src);

    AREPA_ASSERT(vs->is_valid());
    AREPA_ASSERT(fs->is_valid());

    offscreen_program = arepa::Program::create({vs, fs});

    AREPA_ASSERT(offscreen_program->is_valid());

    vs_src = arepa::FileReader::read_text_file("../shaders/screen_vs.glsl");
    fs_src = arepa::FileReader::read_text_file("../shaders/screen_fs.glsl");

    vs = arepa::ShaderFactory::create<arepa::VertexShader>(vs_src);
    fs = arepa::ShaderFactory::create<arepa::FragmentShader>(fs_src);

    AREPA_ASSERT(vs->is_valid());
    AREPA_ASSERT(fs->is_valid());

    onscreen_program = arepa::Program::create({vs, fs});

    AREPA_ASSERT(onscreen_program->is_valid());
}

void init_buffers() {
    arepa::BufferBuilder buffer_builder{mesh};

    offscreen_ibo = buffer_builder.build_index_buffer();
    offscreen_pos_vbo = buffer_builder.build_position_buffer();
    offscreen_nor_vbo = buffer_builder.build_normal_buffer();

    onscreen_ibo = arepa::IndexBuffer::create();
    onscreen_pos_vbo = arepa::VertexBuffer::create();
    onscreen_tex_vbo = arepa::VertexBuffer::create();

    onscreen_ibo->set_data({0, 1, 2, 0, 2, 3});
    onscreen_pos_vbo->set_data({-1.0f, -1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f,
                                1.0f, 0.0f, 1.0f, -1.0f, 0.0f});
    onscreen_tex_vbo->set_data(
        {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f});
}

void init_mesh() {
    mesh = arepa::OBJMeshLoader("../assets/happy_buddha.obj").load();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(0, 100);
    glutCreateWindow("G-Buffer");

    glewInit();

    glutDisplayFunc(display);

    init_shaders();
    init_mesh();
    init_buffers();
    init_framebuffer();

    glutMainLoop();
}
