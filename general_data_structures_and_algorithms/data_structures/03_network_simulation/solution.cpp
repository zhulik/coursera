#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Request {
public:
  Request(int arrival_time, int process_time)
      : m_arrival_time(arrival_time), m_process_time(process_time) {}

  int arrival_time() const { return m_arrival_time; }
  int process_time() const { return m_process_time; }

private:
  int m_arrival_time;
  int m_process_time;
};

class Response {
public:
  Response(bool dropped, int start_time)
      : m_dropped(dropped), m_start_time(start_time) {}

  bool is_dropped() const { return m_dropped; }
  int start_time() const { return m_start_time; }

private:
  bool m_dropped;
  int m_start_time;
};

class Buffer {
public:
  Buffer(int size) : m_size(size) {}

  Response Process(const Request &request) {
    while (!m_finish_time.empty() &&
           m_finish_time.front() <= request.arrival_time()) {
      m_finish_time.pop();
    }
    if (m_finish_time.size() == m_size) {
      return Response(true, -1);
    }
    int current_start_time = m_finish_time.empty()
                                 ? request.arrival_time()
                                 : m_finish_time.back();
    m_finish_time.push(current_start_time + request.process_time());
    return Response(false, current_start_time);
  }

private:
  int m_size;
  queue<int> m_finish_time;
};

vector<Request> ReadRequests() {
  vector<Request> requests;
  int count;
  cin >> count;
  for (int i = 0; i < count; ++i) {
    int arrival_time, process_time;
    cin >> arrival_time >> process_time;
    requests.push_back(Request(arrival_time, process_time));
  }
  return requests;
}

vector<Response> ProcessRequests(const vector<Request> &requests,
                                 Buffer &buffer) {
  vector<Response> responses;
  for (auto r : requests)
    responses.push_back(buffer.Process(r));
  return responses;
}

void PrintResponses(const vector<Response> &responses) {
  for (auto r : responses)
    cout << (r.is_dropped() ? -1 : r.start_time()) << endl;
}

int main() {
  int size;
  cin >> size;
  vector<Request> requests = ReadRequests();

  Buffer buffer(size);
  vector<Response> responses = ProcessRequests(requests, buffer);

  PrintResponses(responses);
  return 0;
}
