#include <bits/stdc++.h>

// ヘッダに実装を書くのは使い方を間違えているという説がある

#include "utils.h"
#include "graph.h"
#include "worker.h"
#include "job.h"

using namespace std;

#define CONTEXT sint time_cnt
#define CONTEXT_ARG time_it

inline void stay(CONTEXT, Worker worker) {
    cout << "stay" << endl;
}

inline void move(CONTEXT, Worker worker, sint pos) {
    cout << "move " << (pos + 1) << endl;
}

inline void execute(CONTEXT, Worker worker, sint job_id, sint task_cnt) {
    cout << "execute " << (job_id + 1) << " " << task_cnt << endl;
}

inline float calc_reward(vector<int> &table_t, vector<int> &table_y, sint t) {
    if (t < table_t[0]) {
        return (float)table_y[0];
    }
    if (t >= table_t[table_t.size() - 1]) {
        return (float)table_y[table_y.size() - 1];
    }

    sint pos = lower_bound(table_t.begin(), table_t.end(), t) - table_t.begin();
    return (float)(table_y[pos+1] - table_y[pos]) * (float)(t - table_t[pos])
    / (float)(table_t[pos+1] - table_t[pos]) + (float)table_y[pos];
}

int main() {
    sint t_max;
    cin >> t_max;

    Graph graph;
    input_graph(graph);

    sint n_worker;
    cin >> n_worker;
    vector<Worker> workers(n_worker);
    for (int i = 0; i < n_worker; i++) {
        input_worker(workers[i]);
    }

    sint n_job;
    cin >> n_job;
    Job jobs[n_job];
    vector<vector<int>> reward_table_t(n_job);
    vector<vector<int>> reward_table_y(n_job);
    Dependency dependency;
    init_dependency(dependency, n_job);
    for (int i = 0; i < n_job; i++) {
        input_job(jobs[i]);
        int n_reward;
        cin >> n_reward;
        reward_table_t[i].resize(n_reward);
        reward_table_y[i].resize(n_reward);
        for (int j = 0; j < n_reward; j++) {
            int t, y;
            cin >> t >> y;
            reward_table_t[i][j] = t - 1;
            reward_table_y[i][j] = y;
        }
        int n_dependency;
        cin >> n_dependency;
        for (int j = 0; j < n_dependency; j++) {
            int from;
            cin >> from;
            from--;
            add_dependency(dependency, from, i);
            inc_rem_dep(jobs[i]);
        }
    }

    auto _ = all_bfs(graph);
    auto dist = _.first;
    auto next = _.second;

    Job executing_job[n_worker];
    for (int i = 0; i < n_worker; i++) {
        executing_job[i] = null_job();
    }

    for (sint time_it = 0; time_it < t_max; time_it++) {
        for (sint worker_i = 0; worker_i < n_worker; worker_i++) {
            Worker &worker = workers[worker_i];
            if (!is_null_edge(get_moving_edge(get_mpos(worker)))) {
                assert(get_to(get_moving_edge(get_mpos(worker))) != get_pos(worker));
                move(time_it, worker, get_to(get_moving_edge(get_mpos(worker))));
                move(worker, get_moving_edge(get_mpos(worker)));
                continue;
            }

            Job *exec_job = nullptr;

            if (!is_null_job(executing_job[worker_i])) {
                sint id = get_job_id(executing_job[worker_i]);
                if (get_task_cnt(executing_job[worker_i]) > 0 && calc_reward(reward_table_t[id], reward_table_y[id], time_it) > 0){
                    exec_job = &executing_job[worker_i];
                } else {
                    executing_job[worker_i] = null_job();
                }
            }

            if (exec_job == nullptr) {
                for (auto &job : jobs) {
                    if (get_can_job(worker, get_job_type(job)) && get_task_cnt(job) > 0 &&
                        get_rem_dep(job) == 0 &&
                        calc_reward(reward_table_t[get_job_id(job)], reward_table_y[get_job_id(job)], time_it) > 0) {
                        exec_job = &job;
                        break;
                    }
                }
            }

            if (exec_job == nullptr) {
                stay(time_it, worker);
                continue;
            }

            if (get_pos(worker) != get_pos(*exec_job)) {
                assert(is_null_edge(get_moving_edge(get_mpos(worker))));
                Edge next_e = next[get_pos(worker)][get_pos(*exec_job)];
                move(time_it, worker, get_to(next_e));
                move(worker, next_e);
                continue;
            }

            assert(get_task_cnt(*exec_job) > 0);

            execute(time_it, worker, get_job_id(*exec_job), min(get_task_limit(worker), get_task_cnt(*exec_job)));
            add_task_cnt(*exec_job, -min(get_task_limit(worker), get_task_cnt(*exec_job)));

            if (get_task_cnt(*exec_job) == 0) {
                for (auto job_id : *it_dependency(dependency, get_job_id(*exec_job))) {
                    dec_rem_dep(jobs[job_id]);
                }
                executing_job[worker_i] = null_job();
            }
        }
    }
}
