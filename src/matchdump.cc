#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <cstdlib>
#include "matchresult.h"

#include "KMatch.h"
#include <sys/time.h>
#include <thread>
#include <functional>

int main(int argc, char ** argv){

  if (argc!=3) {
    std::cout<<"Usage: "<<argv[0]<<" kmatch_output_file match_files_prefix"<<std::endl;
    return -1;
  }

  std::ifstream result_file(argv[1]);
  std::ofstream lst_file(std::string(argv[2])+".lst");
  std::ofstream coord_file(std::string(argv[2])+".csv");
  t_result r;
  uint64_t mid=0;
  coord_file<<"name, seq1, seq2"<<std::endl;
  while (!result_file.read((char *) &r,sizeof(r)).eof()){
    lst_file<<r.query_id<<" "<<r.target_id<<" "<<r.query_size<<" "<<r.qstart<<" "<<r.tstart<<" "<<r.len<<" "<<r.reverse<<" "<<r.prob<<" "<<r.ident<<std::endl;
    for(auto offset=0;offset<r.len;offset+=1000){
      coord_file<<"M"<<mid++<<","<<r.qstart+offset<<","<<r.tstart+(r.reverse ? -offset:offset)<<std::endl;
    }

  }
  result_file.close();
}
