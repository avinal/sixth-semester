/**
 * /mnt/z/my_git/sixth-semester/computer_networks/lab/lab4/BitStuffing.cpp
 * @file BitStuffing.cpp
 * @author Avinal Kumar
 * @since February 17, 2021
 *
 * Bit Stuffing Implementation in CPP
 */

#include <algorithm>
#include <iostream>

std::string bit_stuff(std::string const data) {
  std::string stuffed = "";
  size_t last_pos = 0;
  while (true) {
    size_t one = data.find("11111", last_pos);
    if (one != std::string::npos) {
      stuffed += data.substr(last_pos, one - last_pos + 5);
      stuffed += '0';
      last_pos = one + 5;
    } else {
      break;
    }
  }
  stuffed += data.substr(last_pos);
  return stuffed;
}

std::string bit_unstuff(std::string const data) {
  std::string unstuff = "";
  size_t last_pos = 0;
  while (true) {
    size_t one = data.find("11111", last_pos);
    if (one != std::string::npos) {
      unstuff += data.substr(last_pos, one - last_pos + 5);
      last_pos = one + 6;
    } else {
      break;
    }
  }
  unstuff += data.substr(last_pos);
  return unstuff;
}

int main(int argc, char const *argv[]) {
  std::string data = "";
  std::cout << "Enter data stream consisting of 0 and 1 only:" << std::endl;
  std::cin >> data;
  std::string stuff = bit_stuff(data);
  std::cout << "Data after stuffing bits: " << stuff << std::endl;
  std::cout << "Data after unstuffing: " << bit_unstuff(stuff) << std::endl;
  std::cout << std::endl;
  return 0;
}
