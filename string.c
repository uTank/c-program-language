// TODO: 1、strlen
uint strlen(const char *s)
{
     const char *sc;
     for(sc = s; *sc != '\0'; sc++)
          ;
     return (sc - s);
}

// TODO: 2、strnlen
uint strnlen(const char *s, uint count)
{
     const char *sc;
     for(sc = s; count-- && *sc != '\0'; sc++)
          ;
     return (sc - s);
}

// TODO: 3、strcpy
char *strcpy(char *dest, const char *src)
{
     char *tmp = dest;
     while((*dest++ = *src++) != '\0')
          ;
     return tmp;
}

// TODO: 4、strncpy
char *strncpy(char *dest, const char *src, uint count)
{
     char *tmp = dest;
     while(count)
     {
          if((*tmp = *src) != '\0') /* src到尾巴后不再自加，之后一直填'\0' */
               src++;
          tmp++;
          count--;
     }
     return dest;
}

// TODO: 5、strcat
char *strcat(char *dest, const char *src)
{
     char *tmp = dest;
     while(*dest)
          dest++;
     while((*dest++ = *src++) != '\0')
          ;
     return tmp;
}

// TODO: 6、strncat
char *strncat(char *dest, const char *src, uint count)
{
     char *tmp = dest;
     if(count)
     {
          while(*dest)
               dest++;
          while((*dest++ = *src++) != '\0')
          {
               if(--count == 0)
               {
                    *dest = '\0';
                    break;
               }
          }
     }
     return tmp;
}

// TODO: 7、strcmp
int strcmp(const char *cs, const char *ct)
{
     unsigned char c1, c2;
     while(1)
     {
          c1 = *cs++;
          c2 = *ct++;
          if(c1 != c2)
               return (c1 < c2 ? -1 : 1);
          if(!c1)
               break;
     }
     return 0;
}

// TODO: 8、strncmp
int strncmp(const char *cs, const char *ct, uint count)
{
     unsigned char c1, c2;
     while(count)
     {
          c1 = *cs++;
          c2 = *ct++;
          if(c1 != c2)
               return (c1 < c2 ? -1 : 1);
          if(!c1)
               break;
          count--;
     }
     return 0;
}

// TODO: 9、strchr
char *strchr(const char *s, int c)
{
     for(; *s != (char)c; ++s)
          if(*s == '\0')
               return NULL;
     return (char *)s;
}

// TODO: 10、strnchr
char *strnchr(const char *s, size_t count, int c)
{
     for(; count-- && *s != '\0'; ++s)
          if(*s == (char)c)
               return (char *)s;
     return NULL;
}

// TODO: 11、memcmp
int memcpy(const void *cs, const void *ct, uint count)
{
     const unsigned char *su1, *su2;
     int res = 0;
     for(su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
     {
          if((res = *su1 - *su2) != 0)
               break;
     }
     return res;
}

// TODO: 12、memcpy
void *memcpy(void *dest, const void *src, uint count)
{
     char *tmp = dest;
     const char *s = src;
     while(count--)
          *tmp++ = *s++;
     return dest;
}

// TODO: 13、memmove
void *memmove(void *dest, count void *src, uint count)
{
     char *tmp;
     const char *s;
     if(dest <= src)
     {
          tmp = dest;
          s = src;
          while(count--)
               *tmp++ = *s++;
     }
     else
     {
          tmp = dest;
          tmp += count;
          s = src;
          s += count;
          while(count--）
               *--tmp = *--s;
     }
     return dest;
}

// TODO: 14、strstr
char *strstr(const char *s1, const char *s2)
{
     size_t l1, l2;

     l2 = strlen(s2);
     if (!l2)
          return (char *)s1;
     l1 = strlen(s1);
     while (l1 >= l2) {
          l1--;
          if (!memcmp(s1, s2, l2))
               return (char *)s1;
          s1++;
     }
     return NULL;
}

// TODO: 15、strnstr
char *strnstr(const char *s1, const char *s2, size_t len)
{
     size_t l2;

     l2 = strlen(s2);
     if (!l2)
          return (char *)s1;
     while (len >= l2) {
          len--;
          if (!memcmp(s1, s2, l2))
               return (char *)s1;
          s1++;
     }
     return NULL;
}
