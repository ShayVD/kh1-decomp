/* Stand-in "original game" for tests/selftest.sh. Built into an ELF at the
 * PS2 load address so the whole pipeline can be exercised without the real
 * game. Not game code. */
typedef struct { int pad[3]; int hp; } Obj;

int g_counter;

int GetHp(Obj *o) { return o->hp; }

void Clear(char *p, int n) { while (n--) *p++ = 0; }

int AddCounter(int v)
{
    g_counter += v;
    return g_counter;
}

int Heal(Obj *o, int amount)
{
    int hp = GetHp(o) + amount;
    if (hp > 999)
        hp = 999;
    o->hp = hp;
    AddCounter(1);
    return hp;
}

/* Rodata cases: a jump table and string literals. */
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

void _start(void)
{
    static Obj o;
    Clear((char *)&o, sizeof(o));
    Heal(&o, 5);
    Kind(o.hp);
    Name(o.hp);
    for (;;) {}
}
