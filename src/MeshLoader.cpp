#include <fstream>
#include <sstream>
#include <string>

#include <arepa/MeshLoader.h>

namespace arepa {

namespace {
const std::string V_TOK{"v"};
const std::string VN_TOK{"vn"};
const std::string VT_TOK{"vt"};
const std::string F_TOK{"f"};
const std::string MTLLIB_TOK{"mtllib"};
const std::string USEMTL_TOK{"usemtl"};

const std::string NEWMTL_TOK{"newmtl"};
const std::string MAP_KD{"map_Kd"};
const std::string KA_TOK{"Ka"};
const std::string KD_TOK{"Kd"};
const std::string KS_TOK{"Ks"};
const std::string NS_TOK{"Ns"};
const std::string TR_TOK{"Tr"};
const std::string ILLUM_TOK{"Illum"};
} // namespace

template <class T> std::vector<T> split(std::string str, char separator) {
    std::vector<T> tokens;
    T token;
    unsigned int initial = 0, end;

    while (initial < str.size()) {
        std::stringstream sstr;
        std::string strtoken;

        end = str.find(separator, initial);

        if (int(end) == -1)
            end = str.size();

        strtoken = str.substr(initial, end - initial);

        if (strtoken.size()) {
            sstr << str.substr(initial, end - initial);
            sstr >> token;
        } else {
            token = 0;
        }

        tokens.push_back(token);
        initial = end + 1;
    }

    return tokens;
}

OBJMeshLoader::OBJMeshLoader(const std::string &filename) {
    init(filename);
}

void OBJMeshLoader::init(const std::string &filename) {
    std::ifstream input(filename);
    AREPA_ASSERT(input.is_open());

    float x, y, z;
    std::string command;

    int xo = 0;

    while (!input.eof() && input.good()) {
        command = ""; // Clean command in case there are empty lines
        input >> command;

        // Parse vertex coordinates v
        if (command == V_TOK) {
            input >> x >> y >> z;
            m_positions.push_back(Vec3f(x, y, z));
        }
        // Parse normal vector
        else if (command == VN_TOK) {
            input >> x >> y >> z;
            m_normals.push_back(Vec3f(x, y, z));
        }
        // Parse vertex texture coordinates
        // In the OBJ format the third coordinate is optional
        else if (command == VT_TOK) {
            input >> x >> y;
            m_uvs.push_back(Vec2f(x, y));
        }
        // Parse face f vi/ti/ni vi/ti/ni vi/ti/ni
        // TODO: right now it only works for triangular faces
        else if (command == F_TOK) {
            std::string v;
            std::vector<int> vv;
            Vec3i positions_index_entry;
            Vec3i normals_index_entry;
            Vec3i uvs_index_entry;
            int i = 0;

            // Get position, normal and texture coordinate for each vertex
            while (i < 3) {
                // Get stuff for one vertex
                input >> v;

                vv = split<int>(v, '/');

                // If not all vertex attributes were specified in the
                // obj file just fill with zeroes
                while (vv.size() < 3)
                    vv.push_back(0);

                positions_index_entry[i] = vv[0] - 1;
                uvs_index_entry[i] = vv[1] - 1;
                normals_index_entry[i] = vv[2] - 1;
                i++;
            }

            m_positions_index.push_back(positions_index_entry);
            m_uvs_index.push_back(uvs_index_entry);
            m_normals_index.push_back(normals_index_entry);
        }

        // This is to get everything remaining in the line
        // like newlines or whatever
        std::string remain;
        getline(input, remain);
    }
}

Meshf::Ptr OBJMeshLoader::load() {
    Meshf::Ptr mesh = std::make_shared<Meshf>();

    mesh->set_positions_index(m_positions_index);
    mesh->set_uvs_index(m_uvs_index);
    mesh->set_normals_index(m_normals_index);
    mesh->set_positions(m_positions);
    mesh->set_uvs(m_uvs);
    mesh->set_normals(m_normals);

    return mesh;
}

} // namespace arepa
