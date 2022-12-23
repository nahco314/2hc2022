// worker.h

#ifndef INC_2HC2022_WORKER_H
#define INC_2HC2022_WORKER_H


#include <bits/stdc++.h>

#include "utils.h"
#include "graph.h"

typedef struct {
    MPos mpos;         //            50 bit
    sint task_limit;   // [0, 100)   7 bit
    bool can_jobs[3];  //            3 bit
} Worker;

inline MPos get_mpos(Worker worker) {
    return worker.mpos;
}

inline void set_mpos(Worker &worker, MPos mpos) {
    worker.mpos = mpos;
}

inline sint get_pos(Worker worker) {
    return get_pos(get_mpos(worker));
}

inline sint get_task_limit(Worker worker) {
    return worker.task_limit;
}

inline void _set_task_limit(Worker &worker, sint task_limit) {
    worker.task_limit = task_limit;
}

inline bool get_can_job(Worker worker, sint job_type) {
    return worker.can_jobs[job_type];
}

inline void _set_can_job(Worker &worker, sint job_type, bool can_job) {
    worker.can_jobs[job_type] = can_job;
}

inline void input_worker(Worker &worker) {
    sint pos, task_limit;
    std::cin >> pos >> task_limit;
    pos--;
    MPos mpos = comp_mpos(pos);
    set_mpos(worker, mpos);
    _set_task_limit(worker, task_limit);

    sint n_job;
    std::cin >> n_job;
    for (int i = 0; i < n_job; i++) {
        sint job;
        std::cin >> job;
        job--;
        _set_can_job(worker, job, true);
    }
}

inline void move(Worker &worker, Edge edge) {
    mpos_move(worker.mpos, edge);
}


#endif //INC_2HC2022_WORKER_H
