
/* Linux源码中的代码，迭代实现，Greatest common divisor */
unsigned long gcd(unsigned long a, unsigned long b)
{
     unsigned long r;

     if (a < b)
          swap(a, b);
     while ((r = a % b) != 0) {
          a = b;
          b = r;
     }
     return b;
}

/* 递归实现 */
uint gcd(uint a, uint b)
{
     if(b == 0)
     {
          return a;
     } 
     else 
     {
          return gcd(b, a%b);
     }
}

uint gcd(uint a, uint b)
{
     return (b ? gcd(b, a%b) : a);
}
