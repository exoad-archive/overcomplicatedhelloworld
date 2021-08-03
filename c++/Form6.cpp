//source: https://www.reddit.com/r/cpp/comments/3787nj/submit_the_most_complicated_way_that_you_can/croy5n2?utm_source=share&utm_medium=web2x&context=3https://www.reddit.com/r/cpp/comments/3787nj/submit_the_most_complicated_way_that_you_can/croy5n2?utm_source=share&utm_medium=web2x&context=3

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

int main()
{
  using namespace std;
  using namespace std::chrono;
  string str="Hello, world!";
  condition_variable v[str.length()];
  bool f[str.length()]={};
  vector<thread> t;
  mutex m;
  for(auto i:[=]()mutable{int x=0;transform(str.begin(),str.end(),str.begin(),[&](char c){return x++;});return str;}())
  {
    t.emplace_back(thread(bind([&](int y){unique_lock<mutex> ul(m);f[y]=true;v[y].wait(ul);cout<<str[y];f[y]=false;},i)));
  }
  int idx=0;
  for(auto& c:v)
  {
    unique_lock<mutex> ul(m);
    while(!f[idx])c.wait_for(ul,milliseconds(1));
    v[idx].notify_one();
    while(f[idx])c.wait_for(ul,milliseconds(1));
    ++idx;
  }
  for(auto& h:t)h.join();
  cout<<endl;
}
