#include "simplify_contours.h"

#include <libbase/runtime_assert.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace {

double dist2_point_to_line(point2i p, point2i a, point2i b) {
    const long long vx = static_cast<long long>(b.x) - a.x;
    const long long vy = static_cast<long long>(b.y) - a.y;
    const long long wx = static_cast<long long>(p.x) - a.x;
    const long long wy = static_cast<long long>(p.y) - a.y;

    const long long vv = vx * vx + vy * vy;
    if (vv == 0) {
        return static_cast<double>(wx * wx + wy * wy);
    }

    const long long cross = vx * wy - vy * wx;
    const double cross2 = static_cast<double>(cross) * static_cast<double>(cross);
    return cross2 / static_cast<double>(vv);
}

struct HeapItem {
    double cost = 0.0;
    int idx = -1;
    std::size_t ver = 0;

    bool operator>(const HeapItem& o) const noexcept {
        if (cost != o.cost) return cost > o.cost;
        return idx > o.idx;
    }
};

} // namespace

std::vector<point2i> simplifyContour(const std::vector<point2i> &contour, size_t targetVertexSize) {
    const int n = contour.size();
    std::vector<point2i> result;

    // TODO 2 нам дан контур - это зацикленный обход границы объекта по пикселям
    // нам надо его упростить до targetVertexSize вершин (у нас это число будет всегда равно 4)
    // давайте сделаем так: пока у нас много вершин - пытаемся удалить какую-то одну
    // по какому критерию ее выбрать? какую вершину среди оставшихся стоило бы удалить?
    // мы хотим удалить ту что на стороне, ту что не является угловой
    // тогда давайте каждый раз среди всех оставшихся вершин посчитаем метрику "насколько эта вершина угловатая"
    // то есть насколько эта вершина далеко находится от прямой проведенной через предыдущую и следующую вершины в контуре
    // иначе говоря мы хотим удалять в первую очередь такие вершины, что они лежат на гладкой прямой стороне,
    // а значит эта вершина и соседние с ней - лежат на одной прямой
    // тогда в конечном итоге останутся вершины на углах

    // и удалите эту ошибку:
    throw std::runtime_error("Function simplifyContour() is not implemented!");

    rassert(result.size() == targetVertexSize, 321748219312);
    return result;
}

std::vector<std::vector<point2i>> splitContourByCorners(
    const std::vector<point2i> &contour,
    const std::vector<point2i> &corners)
{
    if (contour.empty()) return {};
    if (corners.empty()) return {contour};

    const int n = static_cast<int>(contour.size());

    std::vector<int> cornerIdx;
    cornerIdx.reserve(corners.size());

    for (const auto& c : corners) {
        int idx = -1;
        for (int i = 0; i < n; ++i) {
            if (contour[i] == c) { idx = i; break; }
        }
        rassert(idx >= 0, 918273650);
        cornerIdx.push_back(idx);
    }

    std::sort(cornerIdx.begin(), cornerIdx.end());
    cornerIdx.erase(std::unique(cornerIdx.begin(), cornerIdx.end()), cornerIdx.end());

    rassert(cornerIdx.size() >= 2, 918273651);

    const int m = static_cast<int>(cornerIdx.size());
    std::vector<std::vector<point2i>> parts;
    parts.reserve(static_cast<size_t>(m));

    for (int k = 0; k < m; ++k) {
        const int i = cornerIdx[k];
        const int j = cornerIdx[(k + 1) % m];

        std::vector<point2i> part;
        part.reserve(static_cast<size_t>(n / m + 4));

        part.push_back(contour[i]);

        if (i < j) {
            for (int t = i + 1; t <= j; ++t) part.push_back(contour[t]);
        } else {
            for (int t = i + 1; t < n; ++t) part.push_back(contour[t]);
            for (int t = 0; t <= j; ++t) part.push_back(contour[t]);
        }

        parts.push_back(std::move(part));
    }

    return parts;
}
