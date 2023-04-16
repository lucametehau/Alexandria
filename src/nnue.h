#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <immintrin.h>

#if defined(__AVX512F__)
#define reg_type    __m512i
#define reg_add16   _mm512_add_epi16
#define reg_sub16   _mm512_sub_epi16
#define reg_max16   _mm512_max_epi16
#define reg_min16   _mm512_min_epi16
#define reg_add32   _mm512_add_epi32
#define reg_madd16  _mm512_madd_epi16
#define reg_madd16  _mm512_madd_epi16
#define reg_load    _mm512_load_si512
#define reg_save    _mm512_store_si512
#define ALIGN       64
#elif defined(__AVX2__) || defined(__AVX__)
#define reg_type    __m256i
#define reg_add16   _mm256_add_epi16
#define reg_sub16   _mm256_sub_epi16
#define reg_max16   _mm256_max_epi16
#define reg_min16   _mm256_min_epi16
#define reg_add32   _mm256_add_epi32
#define reg_madd16  _mm256_madd_epi16
#define reg_load    _mm256_load_si256
#define reg_save    _mm256_store_si256
#define ALIGN       32
#elif defined(__SSE2__)
#define reg_type    __m128i
#define reg_add16   _mm_add_epi16
#define reg_sub16   _mm_sub_epi16
#define reg_max16   _mm_max_epi16
#define reg_min16   _mm_min_epi16
#define reg_add32   _mm_add_epi32
#define reg_madd16  _mm_madd_epi16
#define reg_madd16  _mm_madd_epi16
#define reg_load    _mm_load_si128
#define reg_save    _mm_store_si128
#define ALIGN       16
#endif

constexpr int INPUT_WEIGHTS = 768;
constexpr int HIDDEN_SIZE = 512;
constexpr int NUM_REGS = HIDDEN_SIZE / (sizeof(reg_type) / sizeof(int16_t));

class NNUE {
public:
 using accumulator = std::array<std::array<int16_t, HIDDEN_SIZE>, 2>;

 void init(const char* nn);
 void add(NNUE::accumulator& board_accumulator, int piece, int to);
 void clear(NNUE::accumulator& board_accumulator, int piece, int from);
 void move(NNUE::accumulator& board_accumulator, int piece, int from, int to);
 int32_t SCReLU(int16_t x);
 int32_t output(const NNUE::accumulator& board_accumulator, bool stm);
 void Clear(NNUE::accumulator& board_accumulator);
 std::pair<std::size_t, std::size_t> GetIndex(int piece, int square);

 int16_t featureWeights[INPUT_WEIGHTS * HIDDEN_SIZE] __attribute__((aligned(ALIGN)));
 int16_t featureBias[HIDDEN_SIZE] __attribute__((aligned(ALIGN)));
 int16_t outputWeights[HIDDEN_SIZE * 2] __attribute__((aligned(ALIGN)));
 int16_t outputBias;
};