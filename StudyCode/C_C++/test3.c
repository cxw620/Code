#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
int main()
{
    char a[N]; //这里你想想可不可以整可变长的数组
    printf("input a:");
    scanf("%s", a);
    printf("\n");
    // 获取a并以数组的形式存起来
    // scanf最好限定数字位数，如“scanf("%4s",a)”表示把输入的位数限制为四，超过四的舍弃
    char b[N];
    printf("input b:");
    scanf("%s", b);
    printf("\n");

    int x = strlen(a);
    // can strlen be replaced by sizeof?(of course not)
    int p = x - 1;
    //数组从0开始算，这个坑死人
    int y = strlen(b);
    int q = y - 1;

    int l;

    if (x < y)
    {
        l = y - 1;
    }
    else
    {
        l = x - 1;
    }
    // l是干什么的呢，想一想
    // 揭晓答案：可能a，b字符串长度不一样。取最长那个作为存结果的e的长度

    int c[x], d[y];

    for (int i = 0; i < x; i++)
    {
        c[i] = (a[p] - '0');
        --p;
    }
    // 把a里面的字符串数字翻转过来存到c里面
    // 这个'0'用来替代48，也是把字符串类型的数字变成整型，-48不严谨

    for (int i = 0; i < y; i++)
    {
        d[i] = (b[q] - '0');
        --q;
        //TMD改代码忘了加上这个--q，搞得一旦a<=b就出问题QwQ
        // 所以细心很重要QwQ
    }

    int e[l + 2];
    // 想想为什么要设定储存最后结果的e的长度是a，b中最长的那个的长度加1
    // l是长度减一嘛，也就是l+2了
    // 答案是：例如999+999需要向千位进位，如果e的长度只有三就list out of range了

    for (int i = 0; i < l + 2; i++)
    {
        e[i] = 0;
    }
    // 这个for是提前给e存进去整型数字，否则后果如终端最后一次计算所示
    // 原理我也不知道。如果什么都不存，就int e[l + 2],数组里面默认有啥数据呢
    // 这是你没注意到的

    for (int i = 0; i < l + 1; i++)
    {
        if (l == x - 1)
        {
            if (i > y - 1)
            {
                e[i] = e[i] + c[i];
            }
            else
            {
                e[i] = e[i] + (c[i] + d[i]);
            }
        }
        else
        {
            if (i > x - 1)
            {
                e[i] = e[i] + d[i];
            }
            else
            {
                e[i] = e[i] + (c[i] + d[i]);
            }
        }
        // 这个for if组合想一想是为什么，不过思路应该很明显。
        // 揭晓答案：如果a，b字符串不一样长，例如1234+12345，1234加完千位后就不加了，否则你加个c[4]，就list out of range了，c长度为4，就c[0],c[1],c[2],c[3]四个嘛

        if (e[i] >= 10)
        {
            e[i + 1]++;
            e[i] = e[i] % 10;
        }
        // 这个就是进位了
    }

    if (e[l + 1] > 0)
    {
        printf("%d", e[l + 1]);
    }
    // 这个if想想有什么用。
    // 揭晓答案：这就是前面铺垫的向更高位进位，如999+999=1998，如果没有这个就是998了，甚至报错（以这个计算为例子，加百位的时候，e[3+1]++ -> e[4]++,问题是你上面也忘了把e的长度取长一位了，e的长度只有四，哪来的e[4]，就又list out of range，输出一串奇奇怪怪的数字了）

    for (int i = l; i >= 0; i--)
    {
        printf("%d", e[i]);
    }

    return 0;
}