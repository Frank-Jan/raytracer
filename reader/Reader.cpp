#include "constants.h"
#include "Reader.h"
#include "WorldFactory.h"
#include "Triangle.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "UniformRandom.h"
#include "constants.h"

using std::cout, std::cerr, std::endl, std::ifstream, std::string, std::vector;

std::string print(const Vector3D& v) {
    return "{" + std::to_string(v.x()), ", ", std::to_string(v.y()), ", " + std::to_string(v.z()) + "}";
}

struct V {
    FLOAT x;
    FLOAT y;
    FLOAT z;
};

struct Face {
    int v0, v1, v2;
    string print() {
        string str = "{";
        str += std::to_string(v0);
        str += ", ";
        str += std::to_string(v1);
        str += ", ";
        str += std::to_string(v2);
        str += "}";
        return str;
    }
};

vector<string> tokenise(const std::string &str, string del = " ")
{
    vector<string> tokens;
    int start = 0;
    int end = str.find(del);;

    while(end != -1)
    {
        tokens.push_back(str.substr(start, end-start));
        start = end + del.size();
        end = str.find(del, start);
    }
    tokens.push_back(str.substr(start, end-start));
    return tokens;
}

Face get_face(const vector<string>& tokens, int line)
{
    Face face;
    std::vector<string> tok;
    tok = tokenise(tokens[1], "/");
    if(tok.size() != 3) {
        cerr << "Error: failed to tokenize face at line " << line << endl;
    }
    face.v0 = atoi(tok[0].c_str());

    tok = tokenise(tokens[2], "/");
    if(tok.size() != 3) {
        cerr << "Error: failed to tokenize face at line " << line << endl;
    }
    face.v1 = atoi(tok[0].c_str());

    tok = tokenise(tokens[3], "/");
    if(tok.size() != 3) {
        cerr << "Error: failed to tokenize face at line " << line << endl;
    }
    face.v2 = atoi(tok[0].c_str());

    return face;
}

int readFile(const std::string& filename, WorldFactory& wf, World*& w)
{
    delete w;
    w = nullptr;
    cout << "Loading file: " << filename << endl;
    ifstream file;
    file.open(filename);

    if(not file.is_open()) {
        cerr << "Error: unable to load file" << endl;
        file.close();
        return 0;
    }

    string buff;

    std::vector<Vector3D> vertices;
    std::vector<Face> faces;
    vector<string> tok;
    Face face;
    int line{0};
    while(!file.eof())
    {
        vector<string> tokens;
        getline(file, buff);
        tokens = tokenise(buff);
        if(tokens.size() == 0)
            continue;
        if(tokens[0] == "v") {
            if(tokens.size() != 4) {
                cerr << "Error: failed to tokenize vertex at line " << line << endl;
                return 0;
            }
            vertices.push_back(Vector3D(atof(tokens[1].c_str()),
                                       atof(tokens[2].c_str()),
                                       atof(tokens[3].c_str())));
        }
        else if(tokens[0] == "vt") {

        }
        else if(tokens[0] == "vn") {

        }
        else if(tokens[0] == "f") {
            if(tokens.size() != 4) {
                cerr << "Error: failed to tokenize face at line " << line << endl;
                return 0;
            }
            faces.push_back(get_face(tokens, line));
        }
        line++;
    }
    file.close();


    if(CONSOLE_OUTPUT) {
//        cout << "Vertices found: " << endl;
//        int i{0};
//        for (Vector3D &p : vertices) {
//            cout << i++ << " " << print(p) << endl;
//        }
//
//        cout << "Faces found: " << endl;
//        i = 0;
//        for (Face &f : faces) {
//            cout << i++ << " " << f.print() << endl;
//        }
    }

    for(Face& f : faces) {
        if(f.v0 < 1 || f.v0 > vertices.size() ||
            f.v1 < 1 || f.v1 > vertices.size() ||
            f.v2 < 1 || f.v2 > vertices.size()) {
            cerr << "Error: Face has an non-existing vertex" << endl;
            return 0;
        }
    }

    vector<Triangle> triangles;
    auto random = UniformRandom(0.5,1.0);
    for(int i = 0; i < faces.size(); i++)
    {
        triangles.emplace_back(vertices[faces[i].v0-1], vertices[faces[i].v1-1], vertices[faces[i].v2-1]);
        triangles.back().c = Color(random.sample(),random.sample(),random.sample());
    }
    w = wf.get(triangles);
    return 1;
}