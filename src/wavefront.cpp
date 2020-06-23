#include "wavefront.h"
#include <fstream>
#include "triangle.h"

void WaveFront::parseObjFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        return;
    }
    defaultGroup = std::make_shared<Group>();
    defaultGroup->name = "default";
    currentGroup = defaultGroup.get();

    std::string line;

    while (std::getline(file, line))
    {
        std::vector<std::string> command;
        split(line, command, ' ');

        if ((int)command.size() > 0)
        {
            if (command[0] == "v")
            {
                vertices.push_back(Tuple::Point(std::stof(command[1]), std::stof(command[2]), std::stof(command[3])));
            }
            else if (command[0] == "f")
            {
                std::vector<int> fParts;

                for (int i = 1; i < (int)command.size(); i++)
                {
                    std::vector<std::string> fStr;
                    split(command[i], fStr, '/');

                    if(!fStr.empty() && fStr[0] != "")
                    fParts.push_back(std::stoi(fStr[0]));

                }


                if ((int)fParts.size() == 3)
                {
                    faces.push_back(Face(fParts[0], fParts[1], fParts[2], currentGroup));
                }
                else if ((int)fParts.size() > 3)
                {
                    std::vector<int> v;

                    for (int i = 0; i < (int)fParts.size(); i++)
                    {
                        v.push_back(fParts[i]);
                    }

                    auto f = fanTriangulation(v);
                    for (auto j : f)
                    {
                        j.group = currentGroup;
                        faces.push_back(j);
                    }

                }
                
            }
            else if (command[0] == "g")
            {
                auto g = std::make_unique<Group>();
                g->name = command[1];
                groups.push_back(std::move(g));
                currentGroup = groups.back().get();
            }
        }
    }

    for (const auto& f : faces)
    {
        auto tri = std::make_shared<Triangle>(vertices[(long long)f.v1 - 1], vertices[(long long)f.v2 - 1], vertices[(long long)f.v3 - 1]);
        f.group->addChild(tri);
    }

    for (auto& g : groups)
    {
        defaultGroup->addChild(std::move(g));
    }

    file.close();
}

void WaveFront::split(const std::string& str, std::vector<std::string>& parts, char del)
{
    size_t pos = str.find(del);
    size_t initialPos = 0;
    parts.clear();

    while (pos != std::string::npos)
    {
        auto s = str.substr(initialPos, pos - initialPos);
        if (s == " " || s == "")
        {
            initialPos = pos + 1;
            pos = str.find(del, initialPos);
            continue;
        }

        parts.push_back(s);
        initialPos = pos + 1;

        pos = str.find(del, initialPos);
    }

    parts.push_back(str.substr(initialPos, std::min(pos, str.size()) - initialPos + 1));
}

std::vector<Face> WaveFront::fanTriangulation(std::vector<int>& vertices) const
{
    std::vector<Face> triangles;

    for (int i = 1; i < (int)vertices.size()-1; i++)
    {
        auto tri = Face(vertices[0],vertices[i], vertices[i+1]);
        triangles.push_back(tri);
    }

    return triangles;
}
