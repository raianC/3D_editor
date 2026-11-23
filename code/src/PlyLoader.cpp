// PlyLoader.cpp

#include "PlyLoader.hpp"

PlyLoader::PlyLoader() : Error(false) {}

int PlyLoader::TypeSize(const std::string& t) {
    if (t == "char"   || t == "uchar"  || t == "int8"  || t == "uint8")   return 1;
    if (t == "short"  || t == "ushort" || t == "int16" || t == "uint16")  return 2;
    if (t == "int"    || t == "uint"   || t == "float" || t == "int32"
                      || t == "uint32" || t == "float32")                 return 4;
    if (t == "double" || t == "float64")                                  return 8;
    return 0;
}


void PlyLoader::LoadFile(std::string filePath) {
    // Open in binary mode to prevent newline translations in binary PLY formats
    std::ifstream File3D(filePath, std::ios::binary);
    tabPoint.clear();
    tabFace.clear();
    vertexProps.clear();
    faceProps.clear();
    format.clear();
    nbVertices = nbFaces = 0;
    Error = false;

    if (!File3D.is_open()) {
        std::cout << "Error: failed to open file " << filePath << std::endl;
        exit(1);
    }

    


    HeaderReader(File3D);
    
    if (Error==true) {
        std::cout << "Error: An error occurred during the loading process." << std::endl;
        return;
    }

    tabPoint.reserve(nbVertices);
    tabFace.reserve(nbFaces);

    if (format == "format ascii 1.0") {
        AsciiLoader(File3D);
        std::cout << "ASCII PLY loaded successfully." << std::endl;
    }
    else if (format == "format binary_little_endian 1.0") {
        BinaryLoader(File3D);
        std::cout << "Binary little-endian PLY loaded successfully." << std::endl;
    }
    else if (format == "format binary_big_endian 1.0") {
        std::cout << "Error: binary big-endian PLY is not supported." << std::endl;
        Error = true;
        return;
    }
    else {  
        std::cout << "Unknown PLY format: " << format << std::endl;
        Error = true;
    }
    if (Error==true) {
        std::cout << "Error: An error occurred during the loading process." << std::endl;
        return;
    }
}


void PlyLoader::HeaderReader(std::ifstream& File3D) {
    std::string currentElement;
    std::string line;
    while (std::getline(File3D, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();

        std::istringstream ss(line);
        std::string keyword;
        ss >> keyword;

        if (keyword == "format") {
            format = line;
        }
        else if (keyword == "element") {
            int count;
            ss >> currentElement >> count;
            if (currentElement == "vertex") nbVertices = count;
            else if (currentElement == "face") nbFaces = count;
        }
        else if (keyword == "property") {
            std::string type;
            ss >> type;
            if (type == "list") {
                std::string countType, indexType, name;
                ss >> countType >> indexType >> name;
                if (TypeSize(countType) == 0 || TypeSize(indexType) == 0) { Error = true; return; }
                if (currentElement == "face")
                    faceProps.push_back(Property{name, indexType, TypeSize(indexType), true, countType});
            } else {
                std::string name;
                ss >> name;
                Property p{name, type, TypeSize(type)};
                if (p.size == 0) {
                    std::cout << "Error: Unknown property type '" << type << "'." << std::endl;
                    Error = true;
                    return;
                }
                if (currentElement == "vertex") vertexProps.push_back(p);
                else if (currentElement == "face") faceProps.push_back(p);
            }
        }
        else if (keyword == "end_header") {
            break;
        }
    }
}




void PlyLoader::AsciiLoader(std::ifstream& File3D) {
// ASCII Reading
    std::string line;
    int ix = -1, iy = -1, iz = -1;
    for (size_t i = 0; i < vertexProps.size(); ++i) {
        if (vertexProps[i].name == "x") ix = i;
        else if (vertexProps[i].name == "y") iy = i;
        else if (vertexProps[i].name == "z") iz = i;
    }
    if (ix < 0 || iy < 0 || iz < 0) { std::cout << "Error: vertex properties x, y, z not found." << std::endl; Error = true; return; }
    
    std::vector<double> values(vertexProps.size());

    for (int i = 0; i < nbVertices; ++i) {
        std::getline(File3D, line);
        std::istringstream vs(line);
        for (double& v : values) vs >> v;
        tabPoint.emplace_back(values[ix], values[iy], values[iz]);
    }

    for (int i = 0; i < nbFaces; ++i) {
        std::istringstream fs(line);
        int idx[3] = {0, 0, 0}, n = 0;
        for (const Property& p : faceProps) {
            if (p.isList) {
                int count; fs >> count;
                bool isIndices = (p.name == "vertex_indices" || p.name == "vertex_index");
                for (int k = 0; k < count; ++k) { int v; fs >> v; if (isIndices && k < 3) idx[k] = v; }
                if (isIndices) n = count;
            } else {
                double dummy; fs >> dummy;
            }
        }
        if (n != 3) continue;
        tabFace.push_back({idx[0], idx[1], idx[2]});
    }
}

void PlyLoader::BinaryLoader(std::ifstream& File3D) {
    // Binary Little Endian Reading
    int ix = -1, iy = -1, iz = -1;
    for (size_t i = 0; i < vertexProps.size(); ++i) {
        if (vertexProps[i].name == "x") ix = i;
        else if (vertexProps[i].name == "y") iy = i;
        else if (vertexProps[i].name == "z") iz = i;
    }
    if (ix < 0 || iy < 0 || iz < 0) { std::cout << "Error: vertex properties x, y, z not found." << std::endl; Error = true; return; }

    for (int i = 0; i < nbVertices; ++i) {
        double x = 0, y = 0, z = 0;
        for (size_t p = 0; p < vertexProps.size(); ++p) {
            double v = ReadScalar(File3D, vertexProps[p].type);
            if (p == ix) x = v;
            else if (p == iy) y = v;
            else if (p == iz) z = v;
        }
        if (!File3D) {std::cout << "Error: face truncated file." << std::endl; Error = true; return; }   // truncated file
        tabPoint.emplace_back(x, y, z);
    }
    int faceExtraBytes = 0;
    for (const Property& p : faceProps) faceExtraBytes += p.size;
    for (int i = 0; i < nbFaces; ++i) {
        int idx[3] = {0, 0, 0};
        int n = 0;
        for (const Property& p : faceProps) {
            if (p.isList) {
                int count = static_cast<int>(ReadScalar(File3D, p.countType));
                bool isIndices = (p.name == "vertex_indices" || p.name == "vertex_index");
                for (int k = 0; k < count; ++k) {
                    int v = static_cast<int>(ReadScalar(File3D, p.type));
                    if (isIndices && k < 3) idx[k] = v;
                }
                if (isIndices) n = count;
            } else {
            ReadScalar(File3D, p.type);   // color etc., read and discard
            }
        }
        if (!File3D) { Error = true; return; }
        if (n != 3) continue;
        tabFace.push_back({idx[0], idx[1], idx[2]});
    }
}

double PlyLoader::ReadScalar(std::ifstream& f, const std::string& type) {
    auto rd = [&](auto v) {
        f.read(reinterpret_cast<char*>(&v), sizeof(v));
        return static_cast<double>(v);
    };
    if (type == "char"   || type == "int8")    return rd(int8_t{});
    if (type == "uchar"  || type == "uint8")   return rd(uint8_t{});
    if (type == "short"  || type == "int16")   return rd(int16_t{});
    if (type == "ushort" || type == "uint16")  return rd(uint16_t{});
    if (type == "int"    || type == "int32")   return rd(int32_t{});
    if (type == "uint"   || type == "uint32")  return rd(uint32_t{});
    if (type == "float"  || type == "float32") return rd(float{});
    if (type == "double" || type == "float64") return rd(double{});
    Error = true;
    return 0;
}