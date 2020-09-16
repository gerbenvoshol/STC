
#include <stdio.h>
#include <time.h>
#include <stc/cvec.h>
#include <stc/cpqueue.h>
#include <stc/cmap.h>
#include <stc/crandom.h>

typedef_cvec(i, int64_t);
typedef_cpqueue(i, cvec_i, >); // min-heap (increasing values)

int main() {
    size_t N = 10000000;
    crand_rng64_t pcg = crand_rng64_init(time(NULL));
    crand_uniform_i64_t dist = crand_uniform_i64_init(0, N * 10);
    cpqueue_i heap = cpqueue_i_init();

    // Push ten million random numbers to priority queue
    for (int i=0; i<N; ++i)
        cpqueue_i_push(&heap, crand_uniform_i64(&pcg, &dist));

    // push some negative numbers too.
    c_push_items(&heap, cpqueue_i, {-231, -32, -873, -4, -343});

    for (int i=0; i<N; ++i)
        cpqueue_i_push(&heap, crand_uniform_i64(&pcg, &dist));


    // Extract the hundred smallest.
    for (int i=0; i<100; ++i) {
        printf("%zd ", *cpqueue_i_top(&heap));
        cpqueue_i_pop(&heap);
    }
    cpqueue_i_destroy(&heap);
}
