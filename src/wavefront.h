#pragma once

#include "group.h"

struct Face
{
    Face(int a, int b, int c) : v1(a), v2(b), v3(c), group(nullptr) {}
    Face(int a, int b, int c, Group* g) : v1(a), v2(b), v3(c), group(g) {}

    int v1;
    int v2;
    int v3;

    Group* group;
};

class WaveFront
{
public:
    explicit WaveFront() = default;
    ~WaveFront() = default;

    void parseObjFile(const std::string& filename);

    std::shared_ptr<Group> defaultGroup;
    std::vector<Tuple> vertices;
    std::vector<Face> faces;
    std::vector<std::unique_ptr<Group>> groups;

    Group* currentGroup = nullptr;

private:
    void split(const std::string& str, std::vector<std::string>& parts, char del);
    std::vector<Face> fanTriangulation(std::vector<int>& vertices) const;
};