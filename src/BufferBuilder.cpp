#include <arepa/BufferBuilder.h>

VertexBuffer::Ptr BufferBuilder::build_position_buffer() const {
    VertexBuffer::Ptr vbo = VertexBuffer::create();

    std::vector<float> data;
    const auto &poss = m_mesh->get_positions();

    for(const auto &idx : m_mesh->get_positions_index()) {
	const auto &pos0 = poss[idx.x()];
	const auto &pos1 = poss[idx.y()];
	const auto &pos2 = poss[idx.z()];
	data.emplace_back(pos0.x());
	data.emplace_back(pos0.y());
	data.emplace_back(pos0.z());
	data.emplace_back(pos1.x());
	data.emplace_back(pos1.y());
	data.emplace_back(pos1.z());
	data.emplace_back(pos2.x());
	data.emplace_back(pos2.y());
	data.emplace_back(pos2.z());
    }

    vbo->set_data(data);

    return vbo;
}

VertexBuffer::Ptr BufferBuilder::build_normal_buffer() const {
    VertexBuffer::Ptr vbo = VertexBuffer::create();

    std::vector<float> data;
    const auto &nors = m_mesh->get_normals();

    for(const auto &idx : m_mesh->get_normals_index()) {
	const auto &nor0 = nors[idx.x()];
	const auto &nor1 = nors[idx.y()];
	const auto &nor2 = nors[idx.z()];
	data.emplace_back(nor0.x());
	data.emplace_back(nor0.y());
	data.emplace_back(nor0.z());
	data.emplace_back(nor1.x());
	data.emplace_back(nor1.y());
	data.emplace_back(nor1.z());
	data.emplace_back(nor2.x());
	data.emplace_back(nor2.y());
	data.emplace_back(nor2.z());
    }

    vbo->set_data(data);

    return vbo;
}

VertexBuffer::Ptr BufferBuilder::build_uv_buffer() const {
    VertexBuffer::Ptr vbo = VertexBuffer::create();

    std::vector<float> data;
    const auto &uvs = m_mesh->get_uvs();

    for(const auto &idx : m_mesh->get_uvs_index()) {
	const auto &uv0 = uvs[idx.x()];
	const auto &uv1 = uvs[idx.y()];
	const auto &uv2 = uvs[idx.z()];
	data.emplace_back(uv0.x());
	data.emplace_back(uv0.y());
	data.emplace_back(uv1.x());
	data.emplace_back(uv1.y());
	data.emplace_back(uv2.x());
	data.emplace_back(uv2.y());
    }

    vbo->set_data(data);

    return vbo;
}

IndexBuffer::Ptr BufferBuilder::build_index_buffer() const {
    IndexBuffer::Ptr ibo = IndexBuffer::create();

    std::vector<std::uint32_t> index;
    std::uint32_t i = 0;

    while(i < m_mesh->num_triangles()) {
	index.emplace_back(3 * i);
	index.emplace_back(3 * i + 1);
	index.emplace_back(3 * i + 2);
	i++;
    }

    ibo->set_data(index);

    return ibo;
}
