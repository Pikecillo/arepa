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

Program::Ptr offscreen_program;
IndexBuffer::Ptr offscreen_ibo;
VertexBuffer::Ptr offscreen_pos_vbo;
VertexBuffer::Ptr offscreen_nor_vbo;
Texture::Ptr color_texture, depth_texture, pos_texture, nor_texture;
Framebuffer::Ptr fbo;

Program::Ptr onscreen_program;
IndexBuffer::Ptr onscreen_ibo;
VertexBuffer::Ptr onscreen_pos_vbo;
VertexBuffer::Ptr onscreen_tex_vbo;

Mesh::Ptr mesh;

void draw_offscreen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Attribute pos_attr("in_pos", Attribute::Type::Float, 3,
			     sizeof(float) * 3, 0);
    const Attribute nor_attr("in_nor", Attribute::Type::Float, 3,
			     sizeof(float) * 3, 0);

    offscreen_program->bind();
    offscreen_program->set_attribute(pos_attr, offscreen_pos_vbo);
    offscreen_program->set_attribute(nor_attr, offscreen_nor_vbo);

    const float albedo[] = {1.0f, 1.0f, 1.0f};
    float view_matrix[16], projection_matrix[16];
    Transformation::view(Vec3f(0.0f, 0.15f, 1.0f),
			 Vec3f(0.0f, 0.15f, 0.0f),
			 Vec3f(0.0f, 1.0f, 0.0f),
			 view_matrix);
    Transformation::orthographic(Vec2f(-0.12f, 0.12f),
				 Vec2f(-0.12f, 0.12f),
				 Vec2f( 0.0f, 2.0f),
				 projection_matrix);

    offscreen_program->set_uniform_matrix_4f("u_vmatrix", view_matrix);
    offscreen_program->set_uniform_matrix_4f("u_pmatrix", projection_matrix);
    offscreen_program->set_uniform_3f("u_albedo", albedo);

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, 512, 512);

    fbo->bind();

    offscreen_program->draw(Program::Mode::Triangles, offscreen_ibo);
    offscreen_program->unbind();

    fbo->unbind();

    glDisable(GL_DEPTH_TEST);
}

void draw_onscreen() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Attribute pos_attr("in_pos", Attribute::Type::Float, 3,
			     sizeof(float) * 3, 0);
    const Attribute tex_attr("in_tex", Attribute::Type::Float, 2,
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

    onscreen_program->draw(Program::Mode::Triangles, onscreen_ibo);
    onscreen_program->unbind();
}

void display() {
    draw_offscreen();
    draw_onscreen();

    glutSwapBuffers();
}

void init_framebuffer() {
    depth_texture = Texture::create();
    depth_texture->init(512, 512,
			Texture::InternalFormat::Depth,
			Texture::Format::Depth, Texture::Type::Float);

    color_texture = Texture::create();
    color_texture->init(512, 512,
			Texture::InternalFormat::RGBA,
			Texture::Format::RGBA, Texture::Type::UByte);

    pos_texture = Texture::create();
    pos_texture->init(512, 512,
		      Texture::InternalFormat::RGB16F,
		      Texture::Format::RGB, Texture::Type::Float);

    nor_texture = Texture::create();
    nor_texture->init(512, 512,
		      Texture::InternalFormat::RGB16F,
		      Texture::Format::RGB, Texture::Type::Float);

    fbo = Framebuffer::create();
    fbo->attach_color(color_texture, 0);
    fbo->attach_color(pos_texture, 1);
    fbo->attach_color(nor_texture, 2);
    fbo->attach_depth(depth_texture);

    fbo->bind();
    GLuint attachments[3] = { GL_COLOR_ATTACHMENT0,
			      GL_COLOR_ATTACHMENT1,
			      GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    assert(fbo->is_valid());
}

void init_shaders() {
    std::string vs_src =
	FileReader::read_text_file("../shaders/depth_vs.glsl");
    std::string fs_src =
	FileReader::read_text_file("../shaders/depth_fs.glsl");

    Shader::Ptr vs = ShaderFactory::create<VertexShader>(vs_src);
    Shader::Ptr fs = ShaderFactory::create<FragmentShader>(fs_src);

    assert(vs->is_valid());
    assert(fs->is_valid());

    offscreen_program = Program::create({vs, fs});

    assert(offscreen_program->is_valid());

    vs_src =
	FileReader::read_text_file("../shaders/screen_vs.glsl");
    fs_src =
	FileReader::read_text_file("../shaders/screen_fs.glsl");

    vs = ShaderFactory::create<VertexShader>(vs_src);
    fs = ShaderFactory::create<FragmentShader>(fs_src);

    assert(vs->is_valid());
    assert(fs->is_valid());

    onscreen_program = Program::create({vs, fs});

    assert(onscreen_program->is_valid());
}

void init_buffers() {
    BufferBuilder buffer_builder{mesh};

    offscreen_ibo = buffer_builder.build_index_buffer();
    offscreen_pos_vbo = buffer_builder.build_position_buffer();
    offscreen_nor_vbo = buffer_builder.build_normal_buffer();

    onscreen_ibo = IndexBuffer::create();
    onscreen_pos_vbo = VertexBuffer::create();
    onscreen_tex_vbo = VertexBuffer::create();

    onscreen_ibo->set_data({0, 1, 2, 0, 2, 3});
    onscreen_pos_vbo->set_data({-1.0f, -1.0f, 0.0f,
		                -1.0f,  1.0f, 0.0f,
		                 1.0f,  1.0f, 0.0f,
		                 1.0f, -1.0f, 0.0f});
    onscreen_tex_vbo->set_data({0.0f, 0.0f,
		                0.0f, 1.0f,
		                1.0f, 1.0f,
		                1.0f, 0.0f});
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
    init_framebuffer();

    glutMainLoop();
}
