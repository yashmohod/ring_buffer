#include "../includes/ring_buffer.hpp"
#include <iostream>
#include <string>
int tests_run = 0;
int tests_passed =0;


void check(bool condition, const std::string& test_name) {
    tests_run++;
    if (condition) {
        tests_passed++;
        std::cout << "  PASS  " << test_name << "\n";
    } else {
        std::cout << "  FAIL  " << test_name << "\n";
    }
}

bool approx(double a, double b, double eps = 1e-9) {
    return std::abs(a - b) < eps;
}


int main(){

  RingBuffer<double,10> double_buff;
  check(approx(double_buff.size(),0),"Push zero capacity (check size)");
  check(double_buff.full() == false,"Push zero capacity (check full)");
  check(approx(double_buff.mean(),0),"Push zero capacity (check mean)"); 

  for(double i = 0.0; i <= 5 ; i++)
    double_buff.push(i);
  
  check(approx(double_buff[0],0),"Push bellow capacity (check oldest)");
  check(approx(double_buff[5],5),"Push bellow capacity (check newest)");
  check(approx(double_buff.size(),6),"Push bellow capacity (check size)");
  check(double_buff.full() == false,"Push bellow capacity (check full)");
  check(approx(double_buff.mean(),15.0/6),"Push bellow capacity (check mean)");
  
  for(double i = 6.0; i <= 9 ; i++)
    double_buff.push(i);
  
  check(approx(double_buff[0],0),"Push till capacity (check oldest)");
  check(approx(double_buff[9],9),"Push till capacity (check newest)");
  check(approx(double_buff.size(),10),"Push till capacity (check size)");
  check(double_buff.full() == true,"Push till capacity (check full)");
  check(approx(double_buff.mean(),45.0/10),"Push till capacity (check mean)");
 
  for(double i = 6.0; i <= 9 ; i++)
    double_buff.push(i);
  
  check(approx(double_buff[0],4),"Push past capacity (check oldest)");
  check(approx(double_buff[9],9),"Push past capacity (check newest)");
  check(approx(double_buff.size(),10),"Push past capacity (check size)");
  check(double_buff.full() == true,"Push bellow past (check full)");
  check(approx(double_buff.mean(),69.0/10),"Push past capacity (check mean)");


  RingBuffer<std::string,10> string_buff;
  
  string_buff.push("hi");
  check(string_buff.size() == 1, "string buffer push works");


  std::cout << tests_passed << "/" << tests_run << " tests passed\n";
  
  return (tests_passed==tests_run) ? 0:1;

}
