#ifndef KMATCH_INCLUDED
#define KMATCH_INCLUDED 1
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <cstdlib>
#include "matchresult.h"

#define KMATCH_MAX_FREQ 4
#define KMATCH_NUC_A 0
#define KMATCH_NUC_C 1
#define KMATCH_NUC_G 2
#define KMATCH_NUC_T 3
#define KMATCH_NOKMER INT64_MIN
#define KMATCH_POSITION_CHR_CNST 10000000000L

typedef struct kmer_position_s {
  uint64_t kmer; //canonical kmer
  int64_t position; //sign indicates direction +FW -REV
  bool operator <(const kmer_position_s& rhs) const{
    return (kmer < rhs.kmer);
  }

} kmer_position_t;

typedef struct kmer_match_s {
  int64_t q_position;
  int64_t t_position;
  bool reverse;
  bool operator <(const kmer_match_s& rhs) const{
    return (q_position < rhs.q_position);
  }
} kmer_match_t; // if a kmer is High Frequency, then a (pos, -1) and a (-1, pos) are added. TODO: allow for HF in only one.

typedef struct multikmer_match_s {
  int64_t q_start;
  int64_t t_start;
  bool reverse;
  int64_t length;
} multikmer_match_t; 

typedef struct {
  std::string name;
  uint64_t length;
} seq_attributes_t;

inline int64_t str_to_kmer(const char * _str); //returns a canonical kmer with sign indicating position, KMATCH_NOKMER if invalid input

class KMatch {
  public:
    KMatch(char * _target_filename, char * _query_filename, uint8_t _K, int _max_freq, uint8_t N, uint8_t M);
    void load_query_positions();
    void load_target_positions();
    void merge_positions();
    void clear_positions();
    void dump_matching_blocks(char * out_filename, int min_length, int max_gap);
  private:
    uint8_t K,N,M;
    char * target_filename;
    char * query_filename;
    int max_freq;
    void kmer_array_from_fasta(char * filename, std::vector<kmer_position_t> & kposv, std::vector<seq_attributes_t> & seqnames);
    void insert_kmers_from_seq(std::vector<kmer_position_t> & kposv,const std::string & seq, const uint32_t seq_index);
    void insert_kmers_from_seq_N_out_of_M(std::vector<kmer_position_t> &kposv, const std::string & seq, const uint32_t seq_index, const char N, const char M);
    
    std::vector<seq_attributes_t> target_seqs, query_seqs;
    std::vector<kmer_position_t> target_positions, query_positions;
    std::vector<kmer_match_t> kmatches;
};

#endif //KMATCH_INCLUDED
