typedef struct { int pad[3]; int hp; } Obj;

extern int func_00100000(Obj *o);   /* GetHp, still asm */
extern int AddCounter(int v);       /* named in functions.tsv */

int Heal(Obj *o, int amount)
{
    int hp = func_00100000(o) + amount;
    if (hp > 999)
        hp = 999;
    o->hp = hp;
    AddCounter(1);
    return hp;
}

void Clear(char *p, int n) { while (n--) *p++ = 0; }
