// graph.h

#ifndef INC_2HC2022_GRAPH_H
#define INC_2HC2022_GRAPH_H


#include <bits/stdc++.h>
#include <cassert>

#include "utils.h"


typedef struct {
    sint to;    // [0, 2000)  11 bit
    sint dist;  // [1, 128]   7 bit
} Edge;

typedef std::vector<std::vector<Edge>> Graph;

inline Edge comp_edge(sint to, sint dist) {
    return {to, dist};
}

inline Edge null_edge() {
    return comp_edge(-1, -1);
}

inline bool is_null_edge(Edge edge) {
    return edge.to == -1;
}

inline sint get_to(Edge edge) {
    return edge.to;
}

inline sint get_dist(Edge edge) {
    return edge.dist;
}

inline void input_graph(Graph &graph) {
    sint n_vertex, n_edge;
    std::cin >> n_vertex >> n_edge;
    graph.resize(n_vertex);

    for (int i = 0; i < n_edge; i++) {
        sint from, to, dist;
        std::cin >> from >> to >> dist;
        from--;
        to--;
        graph[from].push_back(comp_edge(to, dist));
        graph[to].push_back(comp_edge(from, dist));
    }
}

inline std::pair<std::vector<sint>, std::vector<Edge>> bfs(Graph &graph, sint start) {
    sint n_vertex = graph.size();
    std::vector<sint> dist(n_vertex, sint_INF);
    std::vector<Edge> next(n_vertex);

    std::queue<sint> que;
    que.push(start);
    dist[start] = 0;

    while (!que.empty()) {
        sint v = que.front();
        que.pop();
        for (auto edge : graph[v]) {
            sint to = get_to(edge);
            sint d = get_dist(edge);
            if (dist[to] == sint_INF) {
                dist[to] = dist[v] + d;
                if (v == start) {
                    next[to] = edge;
                } else {
                    next[to] = next[v];
                }
                que.push(to);
            }
        }
    }

    return std::make_pair(dist, next);
}

inline std::pair<std::vector<std::vector<sint>>, std::vector<std::vector<Edge>>>
all_bfs(Graph &graph) {
    sint n_vertex = graph.size();
    std::vector<std::vector<sint>> dist(n_vertex, std::vector<sint>(n_vertex, sint_INF));
    std::vector<std::vector<Edge>> next(n_vertex, std::vector<Edge>(n_vertex));

    for (int i = 0; i < n_vertex; i++) {
        auto res = bfs(graph, i);
        dist[i] = res.first;
        next[i] = res.second;
    }

    return std::make_pair(dist, next);
}

struct MPos {
    sint pos;           // [0, 2000)  11 bit
    Edge moving_edge;   // nullable   32 bit
    sint moving_dist;   // [0, 128)   7 bit
};

inline MPos comp_mpos(sint pos) {
    return MPos{pos, null_edge(), 0};
}

inline sint get_pos(MPos mpos) {
    return mpos.pos;
}

inline void set_pos(MPos &mpos, sint pos) {
    mpos.pos = pos;
}

inline Edge get_moving_edge(MPos mpos) {
    return mpos.moving_edge;
}

inline void set_moving_edge(MPos &mpos, Edge moving_edge) {
    mpos.moving_edge = moving_edge;
}

inline sint get_moving_dist(MPos mpos) {
    return mpos.moving_dist;
}

inline void set_moving_dist(MPos &mpos, sint moving_dist) {
    mpos.moving_dist = moving_dist;
}

inline void inc_moving_dist(MPos &mpos) {
    mpos.moving_dist++;
}

inline void mpos_move(MPos &mpos, Edge moving_edge) {
    if (is_null_edge(get_moving_edge(mpos))) {
        assert(get_pos(mpos) != get_to(moving_edge));
        set_moving_edge(mpos, moving_edge);
        set_moving_dist(mpos, 0);
    } else {
                if (!(get_moving_dist(mpos) < get_dist(moving_edge))) {
            std::cout << get_moving_dist(mpos) << " " << get_dist(moving_edge) << std::endl;
        }
        assert(get_moving_dist(mpos) < get_dist(moving_edge));
    }

    inc_moving_dist(mpos);

    if (get_moving_dist(mpos) == get_dist(moving_edge)) {
        set_pos(mpos, get_to(moving_edge));
        set_moving_edge(mpos, null_edge());
        set_moving_dist(mpos, 0);
    } else {
        if (!(get_moving_dist(mpos) < get_dist(moving_edge))) {
            std::cout << get_moving_dist(mpos) << " " << get_dist(moving_edge) << std::endl;
        }
    }
}


#endif //INC_2HC2022_GRAPH_H
