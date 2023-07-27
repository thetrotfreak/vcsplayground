## Source Code
```c
#include <stdbool.h>
#include <stdio.h>

unsigned long long factorial(const unsigned int n) {
  if (n == 0 || n == 1)
    return 1;
  else
    return n * factorial(n - 1);
}

bool isspecial(const int n) {
  int sum = 0;
  int digit = 0;
  int copy_of_n = n;
  while (copy_of_n != 0) {
    digit = copy_of_n % 10;
    copy_of_n = copy_of_n / 10;
    sum += factorial(digit);
  }
  return sum == n ? true : false;
}

int main() {
  printf("Listing special numbers between 100 and 1000...\n");
  for (int i = 100; i <= 1000; i++) {
    if (isspecial(i) == true) {
      printf("%d\n", i);
    }
  }
  return 0;
}
```
## Token Table
Identifiers|
---|
factorial|
n|
bool|
isspecial|
sum|
digit|
copy_of_n|
true|
false|
main|
printf|
i|

Keywords|
---|
unsigned|
long|
const|
int|
if|
return|
else|
while|
for|

Constants|
---|
0|
1|
10|
100|
1000|

String Literals|
---|
"Listing special numbers between 100 and 1000...\n"|
"%d\n"|

Operators|
---|
<|
>|
==|
\|\||
*|
-|
=|
!=|
%|
/|
+=|
?|
<=|
++|

Special Symbols|
---|
\#|
(|
)|
{|
}|
;|
:|
,|

