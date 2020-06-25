#include "camera.h"
#include <thread>
#include <iomanip>

Ray Camera::rayForPixel(const int x, const int y) const
{
    float xoffset = ((float)x + 0.5f) * pixelSize;
    float yoffset = ((float)y + 0.5f) * pixelSize;

    float worldX = halfWidth - xoffset;
    float worldY = halfHeight - yoffset;

    auto pixel = transform.inverse() * Tuple::Point(worldX, worldY, -1.0f);
    auto origin = transform.inverse() * Tuple::Point(0, 0, 0);

    return Ray(origin, (pixel - origin).normalize());
}

Canvas Camera::render(World& w)
{
    Canvas image = Canvas(hSize, vSize);

    const int threadCount = 16;
    std::vector<std::thread> threads(threadCount);

    int perThread = divRoundClosest(hSize, threadCount);

    for (int i = 0; i < threadCount; i++)
    {
        int s = i * perThread;
        int e = (i + 1) * perThread;

        threads[i] = std::thread([&, s, e]()
        {

            for (int y = 0; y < vSize; y++)
            {
                for (int x = s; x < e; x++)
                {
                    if (x >= hSize) continue;
                    Ray r = rayForPixel(x, y);
                    Color out = w.colorAt(r);
                    image.writePixel(x, y, out);
                }
            }

        });
    }

    std::cout << "0.00%" << std::flush;

    int n = 0;
    for (auto& t : threads)
    {
        t.join();
        n += 1;

        std::cout << "\r" << std::fixed << std::setprecision(2) << ((n / (float)threadCount) * 100.0f) << "%" << std::flush;
    }
    std::cout << "\r" << "100.00%\n\n" << std::flush;

    return image;
}

Canvas Camera::renderSingle(World& w)
{
        Canvas image = Canvas(hSize, vSize);

        for (int y = 0; y < vSize; y++)
        {
            for (int x = 0; x < hSize; x++)
            {
                Ray r = rayForPixel(x, y);
                Color out = w.colorAt(r);
                image.writePixel(x, y, out);
            }
        }

        return image;
}