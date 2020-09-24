#include <stdio.h>
#include <time.h>
#include <stc/clist.h>
#include <stc/crandom.h>
using_clist(fx, double);

int main() {
    int k;
    const int n = 2000000;

    clist_fx list = clist_INIT;
    crand_rng64_t eng = crand_rng64_init(1234);
    crand_uniform_f64_t dist = crand_uniform_f64_init(100.0f, n);
    int m = 0;
    c_forrange (i, int, n)
        clist_fx_push_back(&list, crand_uniform_f64(&eng, &dist)), ++m;
    double sum = 0.0;
    printf("sumarize %d:\n", m);
    c_foreach (i, clist_fx, list)
        sum += *i.val;
    printf("sum %f\n\n", sum);

    k = 0;
    c_foreach (i, clist_fx, list)
        if (++k <= 10) printf("%8d: %10f\n", k, *i.val); else break;
    puts("sort");
    clist_fx_sort(&list); // mergesort O(n*log n)
    puts("sorted");

    k = 0;
    c_foreach (i, clist_fx, list)
        if (++k <= 10) printf("%8d: %10f\n", k, *i.val); else break;
    puts("");

    clist_fx_clear(&list);
    c_push_items(&list, clist_fx, {10, 20, 30, 40, 30, 50});
    c_foreach (i, clist_fx, list) printf(" %g", *i.val);
    puts("");

    int removed = clist_fx_remove(&list, 30);
    clist_fx_insert_after(&list, clist_fx_before_begin(&list), 5); // same as push_front()
    clist_fx_push_back(&list, 500);
    clist_fx_push_front(&list, 1964);
    clist_fx_iter_t it = clist_fx_before_begin(&list);
    printf("Full: ");
    c_foreach (i, clist_fx, list)
        printf(" %g", *i.val);
    for (int i=0; i<4; ++i) clist_fx_next(&it);
    printf("\nSubs: ");
    c_foreach (i, clist_fx, it, clist_fx_end(&list))
        printf(" %g", *i.val);
    puts("");
    clist_fx_del(&list);
}