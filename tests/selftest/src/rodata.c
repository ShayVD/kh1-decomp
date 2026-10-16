/* Exercises per-function rodata placement (switch table, string literals). */
int Kind(int x)
{
    switch (x) {
    case 0: return 5;
    case 1: return 9;
    case 2: return 13;
    case 3: return 1;
    case 4: return 77;
    case 5: return 3;
    }
    return 0;
}

const char *Name(int i)
{
    if (i == 1)
        return "alpha";
    if (i == 2)
        return "beta";
    return "gamma";
}
