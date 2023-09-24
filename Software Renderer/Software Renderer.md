# Software Renderer

👀软光栅项目：用于深入理解图形api、GPU硬件以及图形渲染管线～

#### 0.参考资料

- ssloy - tinyrender：300行代码实现基础软光栅

  - > https://github.com/ssloy/tinyrenderer/wiki
  
  - 图片格式：.tga；模型数据：.obj

#### 1.画线

给定起点终点，画一条线段，**<font color='red'>~~线段跨过的像素会被着色~~（这个理解是错误的🙅）</font>**

=> 我们以下图为例分析：这张图是我们实际光栅化得到的结果【**Bresenham画线算法**】

分析特征可以发现：它一定在某一个方向上扫描过去只有一个点，比如下图每个x值只对应一个y

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309231853060.png" alt="截屏2023-09-23 18.52.14" style="zoom:40%;" />

如果每个被跨过的像素都被着色，那么结果是：明显是不对的

<img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309231859775.png" alt="截屏2023-09-23 18.58.50" style="zoom:50%;" />

##### <font color='purple'>Bresenham画线算法</font>

画线算法的核心思想：以x为基准，每次将x递增，同时根据斜率计算y的值，且完全使用整数计算

```cpp
// version 1
for(int x = x0; x <= x1; x++)
{
		float t = (x - x0) / float(x1 - x0);
		int y = y0 * (1.0 - t) + y1 * t; 
		image.set(x, y, color);
}
```

Version 1代码有一些问题：（1）没有考虑x0与x1相等的情况，也就是斜率不存在（2）循环默认了x0必须小于x1（3）没有考虑四舍五入

改进的Bresenham算法的步骤：

- 【**确定方向为基准迭代**】确定x/y哪个方向横跨长度更大，我们以这个为基准进行迭代递增 => 为什么？实践发现，如果选择横跨长度小的方向，图像是断开的，如下👇：因为横跨长度越大，该方向的变化速率越大，假如k<sub>y</sub><k<sub>x</sub>，选择y作为迭代对线，就是让Δy=1，那么Δx>1，就会有可能断开
  - 这样做的好处，可以避免出现x0=x1或者y0=y1造成除法错误
  - <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309231918824.png" alt="截屏2023-09-23 19.18.24" style="zoom:70%;" />
  
- 【**以绝对值较小的作为起点**】便于for循环的书写

- 【**四舍五入误差机制**】如果用float值，然后用round对其四舍五入，可能会因为浮点数的精度问题产生误差 => 改进的Bresenham算法，**完全使用整数计算，避免了误差** 

  - 我们来研究一下这个误差机制：

    最初版本，我们通过浮点数来研究，x方向每递进循环一次，|y|其实会增加Δx·|dy/dx|，我们可以单独拿一个初始值为0.0的变量error来记录y的小数部分，每次循环error+=|dy/dx|，当error大于0.5时，我们可以四舍五入认为y可以+1了，最后我们将error-=1.0

    ```cpp
    // version 1
    ...
    int dx = x1-x0; 
    int dy = y1-y0; 
    float derror = std::abs(dy/float(dx)); 
    float error = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error += derror; // 这个版本跟round()思路一致
        if (error>.5) { 
            y += (y1>y0?1:-1); 
            error -= 1.; 
        } 
    } 
    ```

    所以我们观察y或者error这个变量，起初值是0.0，当它第一大于0.5时，他就进入了一个循环，如下图👇

    <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309232215822.JPG" alt="IMG_5521" style="zoom:20%;" />

    那么我们能用整数实现这个思路吗，避免了因浮点数精度问题导致的误差？首先相关系数整体乘dx，再整体成2：

    ```cpp
    // final version
    ...
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror = std::abs(dy) * 2; 
    float error = 0; 
    int y = y0; 
    for (int x = x0; x <= x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error += derror; 
        if (error > dx) { 
            y += (y1 > y0 ? 1 : -1); 
            error -= 2 * dx; 
        } 
    } 
    ```

  - => 这个相当影响最终效果，我们可以画一个三角形，看线段收尾是否连接丝滑，没有超出或断开

    - 比如误差机制错误的情况：

      <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309232154676.png" alt="截屏2023-09-23 21.52.16" style="zoom:30%;" />

      <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309232200694.png" alt="截屏2023-09-23 21.56.19" style="zoom:35%;" />

    - 正确计算的情况：

      <img src="https://cdn.jsdelivr.net/gh/shuaigougou5545/blog-image/img/202309232200319.png" alt="截屏2023-09-23 21.57.46" style="zoom:35%;" />


代码如下：

```cpp
// final version
void line(int x0, int y0, int x1, int y1, TGAImage& image, TGAColor color)
{
  bool steep = false;
  if(abs(x0 - x1) < abs(y0 - y1))
  {
    swap(x0, y0);
    swap(x1, y1);
    steep = true;
  }

  if(x0 > x1)
  {
    swap(x0, x1);
    swap(y0, y1);
  }

  int dx = x1 - x0;
  int dy = y1 - y0;
  int derror2 = std::abs(dy) * 2; 
  int error2 = 0; 
  int y = y0;
  for(int x = x0; x <= x1; x++)
  {
    if(steep)
      image.set(y, x, color);
    else
      image.set(x, y, color);

    error2 += derror2; 
    if (error2 > dx) { 
      y += (y1 > y0 ? 1 : -1);
      error2 -= dx * 2; 
    }
  }
}
```

#### 2.光栅化

任何多边形可以被拆分为多个三角形（硬件可以为我们轻松做到），这里就不仔细研究了，这里我们研究三角形的光栅化。三角形的光栅化沿用上面的画线算法，在三角形内填充像素

如何进行光栅化，一般进行水平扫描（迭代y）【为了防止三角形边畸形，建议还是和画线算法一样判断xy的跨度，选择跨度大的方向进行迭代】，所以我们得知道左右边界 => 我们可以把点按照y的大小排成p0、p1、p2，那么p0～p2就是左边轮廓，p0～p1、p1～p2就是右轮廓，但是现在右轮廓是两段线段，影响代码的优美性，我们可以将三角形从中间劈开，劈成两个三角形，然后分别绘制上下三角形

```cpp
// version 1
void triangle(Vec2i t0, Vec2i t1, Vec2i t2, TGAImage &image, TGAColor color) {
    if (t0.y==t1.y && t0.y==t2.y) return; // i dont care about degenerate triangles
    if (t0.y>t1.y) std::swap(t0, t1);
    if (t0.y>t2.y) std::swap(t0, t2);
    if (t1.y>t2.y) std::swap(t1, t2);
    int total_height = t2.y-t0.y;
    for (int i=0; i<total_height; i++) {
        bool second_half = i>t1.y-t0.y || t1.y==t0.y;
        int segment_height = second_half ? t2.y-t1.y : t1.y-t0.y;
        float alpha = (float)i/total_height;
        float beta  = (float)(i-(second_half ? t1.y-t0.y : 0))/segment_height; // be careful: with above conditions no division by zero here
        Vec2i A =               t0 + (t2-t0)*alpha;
        Vec2i B = second_half ? t1 + (t2-t1)*beta : t0 + (t1-t0)*beta;
        if (A.x>B.x) std::swap(A, B);
        for (int j=A.x; j<=B.x; j++) {
            image.set(j, t0.y+i, color); // attention, due to int casts t0.y+i != A.y
        }
    }
}
```

这里可以优化的点：（1）舍弃浮点数，用整数表达（2）x、y方向应该根据跨度进行修改





