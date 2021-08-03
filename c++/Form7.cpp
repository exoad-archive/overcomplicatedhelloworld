//source: https://ideone.com/uVDbva

/* Hello, World!
     * My most useless program ever.
     * Try to figure out how it works.
     * Jeff
     */
#include <iostream>

using namespace std;

int main()
{
  double y[] = {222,
                -304,
                -516.3, 707.3,
                373.5, -546.14,
                -137.7, 219.066,
                27.549, -47.629,
                -2.8528, 5.3268, 24.1,
                443.74};
  double *r = y;
  double m = 0;
  float s = m;
  do
    s += 100 * *r++;
  while (s > 1666 || s < -166);
  int i = -1, j, k, q, z = s, p = -i[--r], x = m;
  do
  {
    if ((i = x++) > z / p)
    {
      q = i = m + z / p - i % (z / p + 1);
      s = m;
      for (j = 1; j < z; j += p, i *= q, m = 0)
      {
        for (k = j - 1; k >= 0; --k)
          m += k[y];
        s += -(y[j] + m) * i;
      }
      i = q;
      s = (int)s;
    }
    else
    {
      s = z * p * p * p / 3;
      q = i = z / p - i;
    }
    for (j = m; j < z; j += p, i *= q, m = 0)
    {
      for (k = j - p / 2; k >= 0; --k)
        m += y[k];
      s += (m - j[y]) * i;
    }
    s += (x > y[z * 3 / p]) ? x / q[y] + m : m;
    cout << (char)s;
  } while ((short)s != m);
  cout << endl;
  return s;
}
