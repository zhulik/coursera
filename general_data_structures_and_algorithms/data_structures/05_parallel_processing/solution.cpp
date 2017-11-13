#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Worker {
public:
  Worker(int id) : m_id(id) {}
  void set_next_free_time(long long t) { m_next_free_time = t; }

  long long id() const { return m_id; }

  long long next_free_time() const { return m_next_free_time; }

  bool operator<(const Worker &other) const {
    if (m_next_free_time == other.m_next_free_time) {
      return m_id > other.m_id;
    } else {
      return m_next_free_time > other.m_next_free_time;
    }
  }

private:
  long long m_id;
  long long m_next_free_time = 0;
};

class JobQueue {
public:
  void Solve() {
    ReadData();
    AssignJobs();
    // WriteResponse();
  }

private:
  vector<int> m_jobs;

  priority_queue<Worker> m_queue;

  void ReadData() {
    int n, m;
    cin >> n >> m;
    m_jobs.resize(m);
    for (int i = 0; i < m; ++i)
      cin >> m_jobs[i];

    for (int i = 0; i < n; i++) {
      m_queue.push(Worker(i));
    }
  }

  void AssignJobs() {
    for (int i = 0; i < m_jobs.size(); ++i) {
      int duration = m_jobs[i];
      auto next_worker = m_queue.top();
      m_queue.pop();

      cout << next_worker.id() << " " << next_worker.next_free_time() << endl;
      next_worker.set_next_free_time(next_worker.next_free_time() + duration);
      m_queue.push(next_worker);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
