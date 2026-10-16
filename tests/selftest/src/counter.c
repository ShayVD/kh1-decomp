extern int D_g_counter;
/* Deliberately wrong: the self-test checks that this is reported as nonmatching. */
int AddCounter(int v)
{
    D_g_counter += v;
    return v;
}
