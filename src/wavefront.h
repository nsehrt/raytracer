#pragma once

#include "group.h"

struct Face
{
    Face(int a, int b, int c) : v1(a), v2(b), v3(c), group(nullptr) { }
    Face(int a, int b, int c, Group* g) : v1(a), v2(b), v3(c), group(g) {}

    Face(int a, int b, int c, int l, int m, int n) : v1(a), v2(b), v3(c), n1(l), n2(m), n3(n), group(nullptr) {}
    Face(int a, int b, int c, int l, int m, int n, Group* g) : v1(a), v2(b), v3(c), n1(l), n2(m), n3(n), group(g) {}

    int v1;
    int v2;
    int v3;

    int n1 = 0;
    int n2 = 0;
    int n3 = 0;

    Group* group;
};

struct FaceData
{
    int v = 0;
    int n = 0;
};

class WaveFront
{
public:
    explicit WaveFront() = default;
    ~WaveFront() = default;

    void parseObjFile(const std::string& filename);

    std::shared_ptr<Group> defaultGroup;
    std::vector<Tuple> vertices;
    std::vector<Tuple> normals;
    std::vector<Face> faces;
    std::vector<std::unique_ptr<Group>> groups;

    Group* currentGroup = nullptr;

private:
    void split(const std::string& str, std::vector<std::string>& parts, char del);
    std::vector<Face> fanTriangulation(std::vector<FaceData>& data) const;
};