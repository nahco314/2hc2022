// job.h

#ifndef INC_2HC2022_JOB_H
#define INC_2HC2022_JOB_H


#include <bits/stdc++.h>

#include "utils.h"

typedef struct {
    sint id;        // [0, 1000)  10 bit
    sint type;      // [0, 3)     2 bit
    sint task_cnt;  // [0, 1500)  11 bit
    sint pos;       // [0, 2000)  11 bit
    sint rem_dep;   // [0, 10)    4 bit
} Job;

inline Job null_job() {
    return {-1, -1, -1, -1, -1};
}

inline bool is_null_job(Job job) {
    return job.id == -1;
}

inline sint get_job_id(Job job) {
    return job.id;
}

inline void _set_id(Job &job, sint id) {
    job.id = id;
}

inline sint get_job_type(Job job) {
    return job.type;
}

inline void _set_job_type(Job &job, sint job_type) {
    job.type = job_type;
}

inline sint get_task_cnt(Job job) {
    return job.task_cnt;
}

inline void _set_task_cnt(Job &job, sint task_cnt) {
    job.task_cnt = task_cnt;
}

inline void add_task_cnt(Job &job, sint n) {
    job.task_cnt += n;
}

inline sint get_pos(Job job) {
    return job.pos;
}

inline void set_pos(Job &job, sint pos) {
    job.pos = pos;
}

inline sint get_rem_dep(Job job) {
    return job.rem_dep;
}

inline void set_rem_dep(Job &job, sint rem_dep) {
    job.rem_dep = rem_dep;
}

inline void inc_rem_dep(Job &job) {
    job.rem_dep++;
}

inline void dec_rem_dep(Job &job) {
    job.rem_dep--;
}


inline void input_job(Job &job) {
    sint id, type, task_cnt, pos;
    std::cin >> id >> type >> task_cnt >> pos;
    id--;
    type--;
    pos--;
    _set_id(job, id);
    _set_job_type(job, type);
    _set_task_cnt(job, task_cnt);
    set_pos(job, pos);
}


typedef std::vector<std::vector<int>> Dependency;

inline void init_dependency(Dependency &dependency, sint n_job) {
    dependency.resize(n_job);
    for (int i = 0; i < n_job; i++) {
        dependency[i].resize(0);
    }
}

inline void add_dependency(Dependency &dependency, sint from, sint to) {
    dependency[from].push_back(to);
}

inline std::vector<int> *it_dependency(Dependency &dependency, sint from) {
    return &dependency[from];
}


#endif //INC_2HC2022_JOB_H
